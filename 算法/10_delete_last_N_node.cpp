#include<iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead ->next = head;
        ListNode* del = dummyHead->next;
        ListNode* pre = dummyHead;
        ListNode* lat = dummyHead->next;
        for(int i = 1;i<n;i++)
        {
            if(lat->next) lat = lat->next;
        }
        if(lat->next)//这个时候说明下面三个指针动了，删除的不是头指针
        {
            while(lat->next)
            {
                lat = lat->next;
                pre = pre->next;
                del = del->next;
            }
            pre->next = pre->next->next;
            delete del;
            delete dummyHead;
            return head;
        }
        else //说明下面的节点没动，删除的是头节点
        {
            ListNode* result = head->next;
            delete del;
            delete dummyHead;
            return result;
        }
    }
};