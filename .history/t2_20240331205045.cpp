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
        ListNode* head=new ListNode(listValues[0]);
        ListNode* cur=head;
        for(size_t i=1;i<listValues.size();i++){
            cur->next=new ListNode(listValues[i]);
            cur=cur->next;
        }

        if(isOrder(head)){
            results.push_back(true);
            continue;
        }

        ListNode* slow=head;
        ListNode* fast=head->next;
        bool canBreak=false;
        while(fast && fast->next){
            if(slow->val > fast->val && fast->next-val > slow->next-val){
                canBreak=true;
                break;
            }
            slow=slow->next;
            fast=fast->next;
        }

        results.push_back(canBreak);

        while(head){
            ListNode* temp=head;
            head=head->next;
            delete temp;
        }
    }
}