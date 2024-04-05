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
            printf("Watchpoint.No: %d, expr = \"%s\", expr_value = %d\n",
                    wp_pool[i].NO, wp_pool[i].expr,wp_pool[i].expr_value);
                flag = false;
        }
    }
    if(flag) printf("the watchpoint is NULL\n");
}

//创建并插入
WP* create_wp(char *agrs,bool* flag){
    WP *p;
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
        //p是从free_释放
        p=free_;
        free_=free_->next;
        p->next=NULL;
        p->expr_value=expr(agrs, flag);
        strcpy(p->expr, agrs);
        //q为head中最后一个
        WP *q=head;
        while(q->next!=NULL) q=q->next;
        q->next=p;
    }
    return p;
}

void delete_wp(int num){
    WP *p,*q;
    if(head==NULL){
        printf("the wps is empty\n");
        return;
    }
    else if(head->NO==num){
        p=head;
        head=head->next;
    }
    else{
        q=head;
        bool flag=false;
        while(q->next!=NULL){
            if(q->next->NO==num){
                p=q->next;
                q->next=p->next;
                flag=true;
                break;
            }
            q=q->next;
        }
    }
}