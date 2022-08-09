/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] 重排链表
 */

#include<iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// @lc code=start
class Solution {
public:
    void reorderList(ListNode* head) {
        // O(1) 空间 - 19 真题

        if (!head -> next) return;

        ListNode* p = head;

        // could also use fast-slow pointer.
        int n;
        for (n = 0; p->next; p = p->next, ++n) {}
        // L0 -> L1 -> L2 -> L3  3/2 = 1
        // L0 -> L3 -> L1 -> L2
        
        //        p    q
        // L0 -> L1 -> L2  2/2 = 1
        // L0 -> L2 -> L1

        n /= 2; // spliting point
        p = head;
        for (int i = 0; i < n; p = p -> next, ++i) {}
        ListNode* q = p->next;
        p->next = nullptr;

        //        p    q   
        // L0 -> L1    L2
        
        // reverse q
        // p,q    r
        // L3 -> L4 -> L5
        // L3 <- L4 <- L5
        p = q; // As new head for the second part
        ListNode* r;
        while(q->next) {
            r = q->next;
            q->next = r->next;
            // ---------------
            // |             /
            // L3     L4  -> L5
            r->next = p;
            // ---------------
            // |             /
            // L3  <- L4    L5
            // q      p,r
            p = r;
        }

        // head,p1         q1 
        // L0 -> L1 -> L2  L5 -> L4 -> L3
        //       r1              s1

        // L0 -> L1 -> L2  L4 -> L3
        //             p1              q1
        ListNode* p1 = head, *q1 = p, *r1, *s1;
        while(p1 && q1) {
            r1 = p1->next;
            s1 = q1->next;
            p1->next = q1;
            q1->next = r1;
            p1 = r1;
            q1 = s1;
        }

    }
};
// @lc code=end

