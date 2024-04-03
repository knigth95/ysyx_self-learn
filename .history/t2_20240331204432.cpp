#include<iostream>
#include<vector>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};

bool isOrder(ListNode* head){
    ListNode* cur=head;
    while(cur && cur->next){
        if(cur->val >cur->next->val) return false;
        cur=cur->next;
    }
    return true;
}

vector<bool> canOrder(vector<vector<int>> & lists){
    vector<bool> results;
    for(const auto & listValues:lists){
        
    }
}