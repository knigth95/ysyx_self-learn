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

#include "sdb.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NR_WP 32


typedef struct watchpoint {
    int NO;
    struct watchpoint *next;

    /* TODO: Add more members if necessary */
    bool flag;
    char* expr;
    int expr_value;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
    int i;
    for (i = 0; i < NR_WP; i ++) {
        wp_pool[i].NO = i;
        wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
        wp_pool[i].expr_value=0;
    }
    wp_pool[NR_WP-1].next=NULL;

    head = NULL;
    free_ = wp_pool;
}


/* TODO: Implement the functionality of watchpoint */
void print_watchpoint(){
  bool flag = true;
    for(int i = 0 ; i < NR_WP ; i ++){
        if(wp_pool[i].flag){
            printf("Watchpoint.No: %d, expr = \"%s\", old_value = %d, new_value = %d\n",
                    wp_pool[i].NO, wp_pool[i].expr,wp_pool[i].old_value, wp_pool[i].new_value);
                flag = false;
        }
    }
    if(flag) printf("the watchpoint is NULL\n");
}

WP* new_wp(char *agrs,bool* flag){
    WP *p;//从free_释放的监视点
    if(free_==NULL){
        printf("watchpoint's count is already full\n");
        assert(0);
    }
    else if(head==NULL){
        p=free_;
        free_=free_->next;
        head=p;
        head->next=NULL;
        head->expr_value=expr(agrs, flag);
        strcpy(head->expr, agrs);
    }
    
    else{

    }
    
    printf("invalid point.\n");
    assert(0);
    return NULL;
}

void free_wp(WP *wp){
    if(head -> NO == wp -> NO){
        head -> flag = false;
        head = NULL;
        printf("Delete watchpoint  success.\n");
        return ;
    }
    for(WP* p = head ; p -> next != NULL ; p = p -> next){
        if(p -> next -> NO  == wp -> NO)
        {
            p -> next = p -> next -> next;
            p -> next -> flag = false; // 没有被使用
            printf("free succes.\n");
            return ;
        }
    }
}

void create_watchpoint(char* args){
    WP* p=new_wp();
    strcpy(p->expr,args);
    bool success=false;
    int tmp=expr(p->expr,&success);
    if(success) p->old_value=tmp;
    else printf("create watchpoint failed.\n");
    printf("create watchpoint No.%d success.\n",p->NO);
}

void delete_watchpoint(int no){
    int i;
    WP *p;//p是要释放的
    if(head==NULL){
        printf("watchpoint is empty\n");
        return;
    }
    else if(head->NO==no){
        p=head;
        head=head->next;
    }

    for(i=0;i<NR_WP;i++){
        if(wp_pool[i].NO ==no){
        free_wp(&wp_pool[i]);
        return;
        }
    }
}