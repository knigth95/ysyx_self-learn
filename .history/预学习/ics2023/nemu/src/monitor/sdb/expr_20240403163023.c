/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

static bool check_parentheses(int p, int q);
static int find_main_op(int p, int q);
static bool surrounded_by_bracket(int x, int p, int q);
static int get_op_priority(int op);

enum {
  TK_NOTYPE = 256, TK_EQ,

  /* TODO: Add more token types */
    NUM = 1,
    RESGISTER = 2,
    HEX = 3,
    EQ = 4,
    NOTEQ = 5,
    OR = 6,
    AND = 7,
    ZUO = 8,
    YOU = 9,
    LEQ = 10,
    YINYONG = 11,
    POINT, NEG
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal

  {"\\-", '-'},         // sub
    {"\\*", '*'},         // mul
    {"\\/", '/'},         // div

    {"\\(", ZUO},
    {"\\)", YOU},
    /*
     * Inset the '(' and ')' on the [0-9] bottom case Bug.
     */

    {"\\<\\=", LEQ},            // TODO
    {"\\=\\=", EQ},        // equal
    {"\\!\\=", NOTEQ},

    {"\\|\\|", OR},       // Opetor
    {"\\&\\&", AND},
    {"\\!", '!'},

    //{"\\$[a-z]*", RESGISTER},
    {"\\$[a-zA-Z]*[0-9]*", RESGISTER},
    {"0[xX][0-9a-fA-F]+", HEX},
    {"[0-9]*", NUM},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0,len;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        Token tmp_token;
        switch (rules[i].token_type) {
            case '+':
                tmp_token.type = '+';
                tokens[nr_token ++] = tmp_token;
                break;
            case '-':
                tmp_token.type = '-';
                tokens[nr_token ++] = tmp_token;
                break;
            case '*':
                tmp_token.type = '*';
                tokens[nr_token ++] = tmp_token;
                break;
            case '/':
                tmp_token.type = '/';
                tokens[nr_token ++] = tmp_token;
                break;
            case 256:
                break;
            case '!':
                tmp_token.type = '!';
                tokens[nr_token ++] = tmp_token;
                break;
            case 9:
                tmp_token.type = ')';
                tokens[nr_token ++] = tmp_token;
                break;
            case 8:
                tmp_token.type = '(';
                tokens[nr_token ++] = tmp_token;
                break;

                // Special
            case 1: // num
                tokens[nr_token].type = 1;
                strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
                nr_token ++;
                break;
            case 2: // regex
                tokens[nr_token].type = 2;
                strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
                nr_token ++;
                break;
            case 3: // HEX
                tokens[nr_token].type = 3;
                strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
                nr_token ++;
                break;
            case 4:
                tokens[nr_token].type = 4;
                strcpy(tokens[nr_token].str, "==");
                nr_token++;
                break;
            case 5:
                tokens[nr_token].type = 5;
                strcpy(tokens[nr_token].str, "!=");
                nr_token++;case 6:
                tokens[nr_token].type = 6;
                strcpy(tokens[nr_token].str, "||");
                nr_token++;
                break;
            case 7:
                tokens[nr_token].type = 7;
                strcpy(tokens[nr_token].str, "&&");
                nr_token++;
                break;
            case 10:
                tokens[nr_token].type = 10;
                strcpy(tokens[nr_token].str, "<=");
                nr_token ++;
                break;
            default:
                printf("i = %d and No rules is com.\n", i);
                break;
        }
        len=nr_token;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  //nr_token--;
  return true;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

  return 0;
}

bool check_parentheses(int p, int q)
{
    if(tokens[p].type != '('  || tokens[q].type != ')')
        return false;
    int l = p , r = q;
    while(l < r)
    {
        if(tokens[l].type == '('){
            if(tokens[r].type == ')')
            {
                l ++ , r --;
                continue;
            }

            else
                r --;
        }
        else if(tokens[l].type == ')')
            return false;
        else l ++;
    }
    return true;
}


