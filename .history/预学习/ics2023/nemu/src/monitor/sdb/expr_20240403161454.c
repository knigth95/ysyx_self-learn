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

enum {
  TK_NOTYPE = 256, TK_EQ,
  
  TK_DEC,
  TK_NEQ,
  
  /* TODO: Add more token types */
    // NUM = 1,
    // RESGISTER = 2,
    // HEX = 3,
    // EQ = 4,
    // NOTEQ = 5,
    // OR = 6,
    // AND = 7,
    // ZUO = 8,
    // YOU = 9,
    // LEQ = 10,
    // YINYONG = 11,
    // POINT, NEG
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

  {"\\-", '-'},         // minus
  {"\\*", '*'},         // mutiply
  {"\\/", '/'},         // divide

  {"\\(", '('},         // left bracket
  {"\\)", ')'},         // right bracket

  {"[1-9]+[0-9]*", TK_DEC},  // decimal integer
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
static int nr_token __attribute__((used))  = 0;

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

        switch (rules[i].token_type) {
          case TK_NOTYPE:
              break;
          case '+':
              tokens[nr_token++].type = '+';
              break;
          case '-':
              tokens[nr_token++].type = '-';
              break;
          case '*':
              tokens[nr_token++].type = '*';
              break;
          case '/':
              tokens[nr_token++].type = '/';
              break;
          case '(':
              tokens[nr_token++].type = '(';
              break;
          case ')':
              tokens[nr_token++].type = ')';
              break;
          case TK_EQ:
              tokens[nr_token++].type = TK_EQ;
              break;
          case TK_NEQ:
              tokens[nr_token++].type = TK_NEQ;
              break;
          case TK_DEC:
              tokens[nr_token].type = TK_DEC; 
              Assert(substr_len < 32, "length of int is too long (> 31)");
              strncpy(tokens[nr_token].str, substr_start, substr_len);
              tokens[nr_token++].str[substr_len] = '\0';
              break;
          default:
              TODO();
              break;
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  nr_token--;
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

static bool check_parentheses(int p, int q) {
  // Step 1, check if the entire expr is surrounded by ()
  if (!(tokens[p].type == '(' && tokens[q].type == ')')) return false;
  // Step 2, check if the expr is closed by ()
  int diff = 0;
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == '(') diff++;
    if (tokens[i].type == ')') diff--;
    if (diff < 0) return false;
  }
  if (diff != 0) return false;
  return true;
}

static int get_op_priority(int op) {
  switch(op) {
    case TK_NEG:
    case TK_DEREF:
      return 2;
    case '*':
    case '/':
      return 3;
    case '+':
    case '-':
      return 4;
    case TK_EQ:
    case TK_NEQ:
      return 7;
    case TK_L_AND:
      return 11;
    case TK_L_OR:
      return 12;
    default:
      return 0;
  }
}

static bool surrounded_by_bracket(int x, int p, int q) {
  int left_bracket = 0;
  int right_bracket = 0;
  for (int i = x - 1; i >= p; i--) {
    if (tokens[i].type == '(') left_bracket++;
    if (tokens[i].type == ')') left_bracket--;
  }
  for (int i = x + 1; i <= q; i++) {
    if (tokens[i].type == ')') right_bracket++;
    if (tokens[i].type == '(') right_bracket--;
  }
  // Log("left_bracket = %d, right_bracket = %d\n", left_bracket, right_bracket);
  if (left_bracket == 0 && right_bracket == 0) return true;
  Assert(left_bracket == right_bracket, "The bracket is not closed!");
  return false;
}

static int find_main_op(int p, int q) {
  int op = -1;
  int last_priority = 0;
  for (int i = p; i <= q; i++) {
    int op_type = tokens[i].type;
    int op_priority = get_op_priority(op_type);
    // Log("[%d] Priority:%d", op_type, op_priority);
    // if the token is not op type, it can not be the main op 
    if (op_priority == 0) continue;
    // if the op is surrounded by bracket, it can not be the main op
    if (!surrounded_by_bracket(i, p, q)) continue;
    // Consider the op type priority and the sequence priority between this op and last op
    // in case the op priority is different, the low priority op will be the domain op
    if (op_priority > last_priority) {
      last_priority = op_priority;
      op = i;
    }
    // in case the priority is the same, the right one will be the domain op
    else if (op_priority == last_priority) {
      op = i;
    }
  }
  Assert(op >= 0, "Find No main op");
  return op;
}