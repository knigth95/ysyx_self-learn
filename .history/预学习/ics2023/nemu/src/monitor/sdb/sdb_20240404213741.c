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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

void print_watchpoint();
unsigned int vaddr_read(unsigned int addr, unsigned int len);
void create_watchpoint(char *args);
void delete_watchpoint(int NO);

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
  //改变函数执行次数
  char *arg=strtok(NULL,"");
  int step=0;
  if(arg==NULL){
    cpu_exec(1);
    return 0;
  }
  //sscanf(arg,"%d",&step);
  Assert(sscanf(arg, "%d", &step), "The input step num is not a number");
  if(step<-1){
    printf("error: N should be greater or equal to -1\n");
    return 0;
  }
  cpu_exec(step);
  return 0;
}

static int cmd_info(char *args){
  char *arg=strtok(NULL,"");
  if(strcmp(arg,"r")==0) isa_reg_display();
  else if(strcmp(arg,"w")==0) print_watchpoint();
  else printf("the command is r or w\n");
  return 0;
}

static int cmd_x(char *args){
  char *arg = strtok(NULL, " ");
  if (arg == NULL) {
    printf("cmd_x Usage: x N Expr\n");
    return 0;
  }
  int32_t N = strtol(arg, NULL, 10);
  char *expr = strtok(NULL, " ");
  if (expr == NULL) {
    printf("cmd_x Usage: x N Expr\n");
    return 0;
  }
  vaddr_t addr = strtol(expr, NULL, 16);
  printf(ANSI_FMT("[Memory status]", ANSI_BG_GREEN) "\n");
  printf("[ADDRESS] --> [VALUE]\n");
  for (int i = 0; i < N; i++) {
    uint32_t value=vaddr_read(addr+i*4, 4);
    printf("0x%08x : 0x%08x\n", addr, vaddr_read(addr, 4));
    printf("%*s : ", 10, "");
    for(int j = 0 ; j < 4 ; j++){
      printf("0x%02x ", value & 0xff);
      value = value >> 8;
    }
    printf("\n\n");
    addr += 4;
  }
  return 0;
} 

static int cmd_p(char* args){
    if(args == NULL){
        printf("No args\n");
        return 0;
    }
    //printf("args = %s\n", args);
    bool flag = false;
    expr
    // int value_reg;
    // value_reg=expr(args, &flag);
    // if(flag == false) 
    //     printf("Invalid Expression\n");
    // else 
    //     printf(">  %d\n", value_reg);
    return 0;
}



static int cmd_w(char* args){
  create_watchpoint(args);
  return 0;
}

static int cmd_d(char* args){
  if(args==NULL) printf("args is NULL\n");
  else delete_watchpoint(atoi(args));
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */
  { "si", "Let the programexcute N instuctions and then suspend the excution,while the N is not given,the default value is 1", cmd_si},
  {"info", "Show the status of program", cmd_info},
  {"x", "Show the memory of the program", cmd_x},
  
  {"w","Set the watchpoint N",cmd_w},
  {"d","Delete the watchpoint N",cmd_d},
  {"p","Evalute the expression",cmd_p},

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
