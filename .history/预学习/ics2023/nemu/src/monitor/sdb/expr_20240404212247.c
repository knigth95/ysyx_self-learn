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

//设定优先级
int set_level(int i){
	switch(tokens[i].type){
		case TK_NEG:case TK_DEREF:return 2;
		case '*':case '/':return 3;
		case '+':case '-':return 4;
		case '>':case '<':case TK_GREATEREQU:case TK_LESSEQU:return 6;
		case TK_EQ:case TK_NOTEQ:return 7;
		case TK_AND:return 11;
	}

	return 0;
}

//括号匹配函数，判断一个字串是否被括号包裹
bool check_brackt(int p,int q){
	//前后是否都是括号
	if(tokens[p].type!='('||tokens[q].type!=')'){
		return false;
	}

	else{
		//从左至右遍历，同时记录括号的数量，如果在中途变为0则说明不匹配。
		int count=0;
		for(int i=p;i<=q;i++){
			if(count==0 && i!=p && i!=q) return false;
			if(tokens[i].type=='(') count++;
			else if(tokens[i].type==')') count--;
		}
		if(count==0)return true;
	}
	match_flag=false;//如果遍历完整个表达式都没有匹配到括号说明输入错误
	return false;
}

//寻找与右括号对应的左括号
int match_bracket(int p,int q){
  //输入非法
  if(tokens[q].type!=')'){
	printf("input error right\n");
    return -1;
  }
  int cnt=1;
  for(int i=q-1;i>=p;i--){
    if(tokens[i].type==')')cnt++;
    else if(tokens[i].type=='(')cnt--;
    if(cnt==0)return i;
  }
  //表达式不正确-->左括号error
  printf("input error left\n");
  return -1;
}

//寻找主运算符 从右至左优先级最高的符号
int find_main_poerator(int p,int q){
	int op_location=p;
	int op_level=0;
	for(int i=q;i>=p;i--){
		//括号内一定不是。
		if(tokens[i].type==')'){
		i=match_bracket(p,i);
		continue;
		}
		//数字一定不是
		else if(tokens[i].type==TK_NUM||tokens[i].type==TK_HEX||tokens[i].type==TK_REG)continue;
		else{
		if(set_level(i)>op_level){
			op_level=set_level(i);
			op_location=i;
		}
		}
	}
	//优先级为2的(单目运算符)结合性不同，所以需要从左至右重新扫描，返回第一个符号
	if(op_level==2){
		for(int i=p;i<=q;i++){
		if(set_level(i)==2){
			op_location=i;
			break;
		}
		}
	}
	return op_location;
}

int eval(int p,int q){
	int ans;
	if(p>q);//非法，不进行任何操作
	else if(p==q){//此时一定是元表达式（即数、十六进制数、寄存器）
		if(tokens[p].type==TK_NUM){
			sscanf(tokens[p].str,"%d",&ans);
			return ans;
		}
		else if(tokens[p].type==TK_HEX){
			sscanf(tokens[p].str,"0x%x",&ans);
			return ans;
		}
		else if(tokens[p].type==TK_REG){
			bool flag=true;
			ans=isa_reg_str2val(tokens[p].str+1,&flag);//这里的+1是为了滤去第一个$
		if(flag==true)return ans;
		printf("wrong reg!\n");
		return 0;
		}

	}
	//判断是否括号
	else if(check_p(p,q)){
		return eval(p+1,q-1);
	}
	//寻找主运算符并递归求解
	else{
		int i=find_main_poerator(p,q);
		//printf("%d\n",tokens[i].type);
		int ans=0;
		//使用switch不方便定义局部变量 考虑改为if-elseif...
		switch (tokens[i].type)
		{
		case TK_NEG:
			return (-1) * eval(p + 1, q);
		case TK_DEREF:
			ans=eval(p+1,q);
			
			if(ans<0x80000000){
			printf("wrong deref!\n");
			return 0;
			}
			
			return vaddr_read(ans,4);
		case '+':
			return eval(p, i - 1) + eval(i + 1, q);
		case '-':
			return eval(p, i - 1) - eval(i + 1, q);
		case '*':
			return eval(p, i - 1) * eval(i + 1, q);
		case '/':
			return eval(p, i - 1) / eval(i + 1, q);
		case TK_EQ:
			return eval(p, i - 1) == eval(i + 1, q);
		case TK_NOTEQ:
			return eval(p, i - 1) != eval(i + 1, q);
		case TK_AND:
			return eval(p, i - 1) && eval(i + 1, q);
		//default:
			//assert(0);
			//尽量避免assert(0);防止测试途中异常退出
		}
		}
		//没有匹配到主运算符的类型（实际上不会有这种情况）
	match_flag=true;
	return -1;
}

word_t expr(char *e, bool *success) {
    if (!make_token(e)) {
        *success = false;
        return 0;
    }

    /* TODO: Insert codes to evaluate the expression. */
    // TODO();
    *success=true;
    
    int token_len=0;
    int i,j;
    for(i=0;i<30;i++){
        if(tokens[i].type ==0) break;
        token_len++;
    }
    for(i=0;i<token_len;i++){
        if(tokens[i].type==2){
            bool flag = true;
            int tmp=isa_reg_str2val(tokens[i].str, &flag);
            if(flag) 
                int_to_char(tmp, tokens[i].str);
            else{
                printf("transfrom error.\n");
                assert(0);
            }
        }
    }
    //init hex
    for(i=0;i<token_len;i++){
        if(tokens[i].type==3){
            //hex num
            int value=strtol(tokens[i].str,NULL, 16);
            int_to_char(value, tokens[i].str);
        }
    }
    printf("init hex\n");
    //init the tokens str 1 ==> -1.
    for(i=0;i<token_len;i++){
        if((tokens[i].type=='-' && i>0 && tokens[i-1].type != NUM && tokens[i+1].type == NUM)
            || (tokens[i].type=='-' && i==0)
        ){
            tokens[i].type=TK_NOTYPE;
            for(j=31;j>0;j--)
                tokens[i+1].str[j]=tokens[i+1].str[j-1];
            tokens[i+1].str[0]='-';
            for(j=0;j<token_len;j++){
                if(tokens[j].type==TK_NOTYPE){
                    for(int k=j+1;j<token_len;j++)
                        tokens[k-1]=tokens[k];
                    token_len--;
                }
            }
        }
    }
    printf("init 1==>-1\n");
    //init tokens
    for(i=0;i<token_len;i++){
        if(tokens[i].type=='!'){
            tokens[i].type=TK_NOTYPE;
            int tmp=char_to_int(tokens[i+1].str);
            if(tmp==0){
                memset(tokens[i+1].str,0,sizeof(tokens[i+1].str));
                tokens[i+1].str[0]='1';
            }
            else memset(tokens[i+1].str, 0, sizeof(tokens[i+1].str));
            for(j=0;j<token_len;j++){
                if(tokens[j].type==TK_NOTYPE){
                    for(int k=j+1;k<token_len;k++)
                        tokens[k-1]=tokens[k];
                    token_len--;
                }
            }
        }
    }
    
    for(i = 0 ; i < token_len ; i ++)
    {
        if(	(tokens[i].type == '*' && i > 0 
                && tokens[i-1].type != NUM 
                && tokens[i-1].type != HEX 
                && tokens[i-1].type != RESGISTER
                && tokens[i+1].type == NUM 
            )
            ||
            (tokens[i].type == '*' 
                && i > 0
                && tokens[i-1].type != NUM 
                && tokens[i-1].type != HEX 
                && tokens[i-1].type != RESGISTER
                && tokens[i+1].type == HEX
                )
            ||
            (tokens[i].type == '*' && i == 0)
            ){
            tokens[i].type = TK_NOTYPE;
            int tmp = char_to_int(tokens[i+1].str);
            uintptr_t a = (uintptr_t)tmp;
            int value = *((int*)a);
            int_to_char(value, tokens[i+1].str);	    
            for(j = 0 ; j < token_len ; j++){
                if(tokens[j].type == TK_NOTYPE)
                {
                    for(int k = j+1 ; k < token_len ; k++)
                        tokens[k - 1] = tokens[k];
                    token_len--;
                }
            }
        }
    }

    uint32_t expr_value=0;
    expr_value=eval(0,token_len-1);
    printf("test expr_value\n");
    if(division_zero==false)
        printf("the value %d\n",expr_value);
    else
        printf("input error\n");
    memset(tokens, 0, sizeof(tokens));

    return expr_value;
}




uint32_t eval(int p, int q) {
    printf("p=%d,q=%d\n",p,q);
    if (p > q) {
        /* Bad expression */
        assert(0);
        return -1;
    }
    else if (p == q) {
        /* Single token.
         * For now this token should be a number.
         * Return the value of the number.
         */
        return atoi(tokens[p].str);
    }
    else if (check_parentheses(p, q) == true) {
        /* The expression is surrounded by a matched pair of parentheses.
         * If that is the case, just throw away the parentheses.
         */
        // printf("check p = %d, q = %d\n",p + 1 , q - 1);
        return eval(p + 1, q - 1);
    }
    /* else if(check_parentheses(p, q) == false){
       printf("Unique\n");
       return -1;
       }
       */
    else {
        int op = -1; // op = the position of 主运算符 in the token expression;
        bool flag = false;
        for(int i = p ; i <= q ; i ++)
        {
            if(tokens[i].type == '(')
            {
                while(tokens[i].type != ')'){
                    i++;
                    printf(") error:%d\n",i); 
                }
                printf("( error\n");  
            }
            if(!flag && tokens[i].type == 6){
                flag = true;
                op = max(op,i);
            }

            if(!flag && tokens[i].type == 7 ){
				flag = true;
                op = max(op,i);
            }

            if(!flag && tokens[i].type == 5){
                flag = true;
                op = max(op,i);
            }

            if(!flag && tokens[i].type == 4){
                flag = true;
                op = max(op,i);
            }
            if(!flag && tokens[i].type == 10){
                flag = true;
                op = max(op, i);
            }
            if(!flag && (tokens[i].type == '+' || tokens[i].type == '-')){
                flag = true;
                op = max(op, i);
            }
            if(!flag && (tokens[i].type == '*' || tokens[i].type == '/') ){
                op = max(op, i);
            }
        }
        printf("op position is %d\n", op);
        // if register return $register
        int  op_type = tokens[op].type;

        // 递归处理剩余的部分
        uint32_t  val1 = eval(p, op - 1);
        printf("val1 = %d\n", val1);
        uint32_t  val2 = eval(op + 1, q);
        printf("val1 = %d, val2 = %d \n", val1, val2);
    
        switch (op_type) {
            case '+':
                return val1 + val2;
            case '-':
                return val1 - val2;
            case '*':
                return val1 * val2;
            case '/':
                if(val2 == 0){
                    //printf("division can't zero;\n");
                    division_zero = true;
                    return 0;
                }
                return val1 / val2;
            case 4:
                return val1 == val2;
            case 5:
                return val1 != val2;
            case 6:
                return val1 || val2;
            case 7:
                return val1 && val2;
            default:
                printf("No Op type.");
                assert(0);
        }
    }
}