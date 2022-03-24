/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // dum -> 1 -> 2 -> 3 -> 4 ->
        // ^r     ^p   ^q   ^tmp
        //          <-
        //        ^r

        if (head == nullptr) return head;

        ListNode dummyHead(-1);
        dummyHead.next = head;
        ListNode *p = head, *q = head->next, *r = &dummyHead;
        ListNode* tmp;
        while(q!=nullptr){
            tmp = q->next;
            q->next = p;
            r->next = q;
            r = p;
            p = tmp;
            q = tmp ? tmp->next : tmp;
        }
        r->next = p;

        return dummyHead.next;
    }
};
// @lc code=end
