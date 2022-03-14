/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
 */


#include<iostream>
#include<vector>
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 双指针
        // r->p  q
        ListNode *r = head, *p = head, *q = head;
        int dist = 0;
        bool flag = true;
        while(q!=nullptr){
            q = q->next;
            if (dist < n) ++dist;
            else {
                if (flag) flag = false;
                else r = r->next;
                p = p->next;
            }
        }
        if (p == head) head = p->next;
        else r->next = p->next;
        delete p;
        return head;
    }
};
// @lc code=end

