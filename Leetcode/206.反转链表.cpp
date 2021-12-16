/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
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
    ListNode* reverseListRecursive(ListNode* head) {
        // 1->2->3->4->5->null
        //             5
        //       3->4<-5
        //       3<->4<-5   // A loop may occur!
        if (head == nullptr || head->next == nullptr) 
            return head;
        ListNode* front = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = nullptr; // clear the previous chain.
        return front;
    }

    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* p = head, *q;
        while(p->next!=nullptr){
            q = p->next;
            p->next = q->next;
            q->next = head;
            head = q;
        }
        return q;
    }
};
// @lc code=end
