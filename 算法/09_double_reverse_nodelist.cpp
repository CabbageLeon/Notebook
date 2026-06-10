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
    ListNode* swapPairs(ListNode* head) {
        ListNode* cur;
        ListNode* temp0;
        ListNode* temp1;
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        cur = dummyHead;
        while(cur->next && cur->next->next)
        {
            temp0 = cur->next;
            temp1 = cur->next->next->next;
            cur->next = cur->next->next;
            cur->next->next = temp0;
            cur->next->next->next = temp1;
            cur = cur->next->next;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};
