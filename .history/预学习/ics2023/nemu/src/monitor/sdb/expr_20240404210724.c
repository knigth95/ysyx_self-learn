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

#include <assert.h>
#include <isa.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <stdlib.h>
#include <string.h>

bool check_parentheses(int p, int q);
uint32_t eval(int p,int q);

enum {
	TK_NOTYPE = 256, TK_EQ,

	/* TODO: Add more token types */
    TK_LESSEQU,
	TK_GREATEREQU,
	TK_NUM,
	TK_HEX,
	TK_REG,
	TK_AND,
	TK_OR,
	TK_NEG, //negative
	TK_NOTEQ,
	TK_DEREF,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

	/* TODO: Add more rules.
	* Pay attention to the precedence level of different rules.
	*/
	//根据查询的优先级顺序填写。
  	//其实这里的顺序是识别顺序，如果某个规则是另一个规则的子集，则这个规则需要放在后位
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal

  {"\\0x[0-9a-fA-F]+",TK_HEX},     //十六进制数
  {"[0-9]+",TK_NUM},    //十进制数字
  {"\\$\\$*[a-z0-9]+",TK_REG},//reg
  //{" +", TK_NOTYPE},    // spaces
  //{"\\+",'+'},         // plus
  {"\\-",'-'},
  {"\\*",'*'},
  {"\\/",'/'},
  {"\\%",'%'},
  {"\\(",'('},
  {"\\)",')'},
  {"<=", TK_LESSEQU},
  {">=", TK_GREATEREQU},
  {">", '>'},
  {"<", '<'},
  {"\\&\\&", TK_AND},
  {"\\|\\|", TK_OR},
  {"!=",TK_NOTEQ},
  {"\\!", '!'},
  {"==", TK_EQ}
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};
bool match_flag=false;//用于记录表达式是否匹配正确，并最终传递到&success
/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    // 这个函数把指定的正则表达式rules[i].regex编译成一种特定的数据格式re[i]，
    // regexec这样可以使匹配更有效。执行成功返回０
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

static Token tokens[1024] __attribute__((used)) = {};//可以把tokens数组的大小变为65536防止溢出
static int nr_token __attribute__((used))  = 0;
int len=0;
bool division_zero=false;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        //  一旦用regcomp()成功地编译了正则表达式，接下来就可以调用regexec()完成模式匹配：
		char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
		//按顺序匹配
        switch (rules[i].token_type){
        case TK_NOTYPE:
          break;
        default:
          tokens[nr_token].type = rules[i].token_type;
          strncpy(tokens[nr_token].str,substr_start,substr_len);
          //printf("%s\n",tokens[nr_token].str);
          nr_token++;
        }
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
