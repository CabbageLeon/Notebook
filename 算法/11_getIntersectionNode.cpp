#include<iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//暴力解法，能过
// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         ListNode* a = headA;
//         ListNode* b = headB;
//         while(a)
//         {
//             b = headB;
//             while(a!=b && b != nullptr)
//             {
//                 b = b->next;
//             }
//             if(a == b) return a;
//             else a = a->next;
//         }
//         return nullptr;
//     }
// };

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0;
        int lenB = 0;
        ListNode* a = headA;
        ListNode* b = headB;
        while(a != nullptr)
        {
            a = a->next;
            lenA++;
        }
        while (b!=nullptr)
        {
            b = b->next;
            lenB++;
        }
        a = headA;
        b = headB;
        if(lenA >lenB) for(int i = 0;i<lenA-lenB;i++) a = a->next;
        else for(int i=0;i<lenB-lenA;i++) b = b->next;

        while(a!=b)
        {
            a = a->next;
            b = b->next;
        }
        return a;
        
    }
};