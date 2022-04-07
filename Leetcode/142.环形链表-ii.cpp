/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* p = head, *q = head;
        // a = c + (n - 1)(b + c) !
        while(q!=NULL){
            p = p->next;
            if (q->next==NULL) return NULL;
            q = q->next->next;
            if (p == q) {
                ListNode* r = head;
                while(r!=p){
                    r = r->next;
                    p = p->next;
                }
                return r;
            }
        }
        return NULL;
    }
};
// @lc code=end

