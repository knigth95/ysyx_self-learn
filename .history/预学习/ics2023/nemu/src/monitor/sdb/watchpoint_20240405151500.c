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
    if(head==NULL){
        printf("the wp is empty\n");
        return;
    }
    while()
}

//创建并插入
void create_wp(char *agrs,bool* flag){
    WP *p;
    if(free_==NULL){
        printf("watchpoint's count is already full\n");
        assert(0);
    }
    else if(head==NULL){
        printf("head is NULL\n");
        p=free_;
        free_=free_->next;
        head=p;
        head->next=NULL;
        head->expr_value=expr(agrs, flag);
        head->expr=(char*)malloc(strlen(agrs)+1);
        strcpy(head->expr, agrs);
    }
    else{
        //p是从free_释放
        printf("p=free_\n");
        p=free_;
        free_=free_->next;
        p->next=NULL;
        p->expr_value=expr(agrs, flag);
        p->expr=(char*)malloc(strlen(agrs)+1);
        strcpy(p->expr, agrs);
        //q为head中最后一个
        WP *q=head;
        while(q->next!=NULL) q=q->next;
        q->next=p;
    }
    printf("wp.No: %d, expr = \"%s\", expr_value = %d\n",
                    p->NO, p->expr,p->expr_value);
}

void delete_wp(int num){
    WP *p;
    WP *q;
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
        if(!flag){
            printf("the wp is not exist\n");
            return;
        }
    }

    //将释放的添加入free_
    if(free_==NULL){
        free_=p;
        free_->next=NULL;
    }
    else{
        q=free_;
        p->next=q;
        free_=p;
    }
    return;
}