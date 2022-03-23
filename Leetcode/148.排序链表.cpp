/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
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
    int getLength(ListNode* head){
        int length = 0;
        while(head!=nullptr){
            ++length;
            head = head->next;
        }
        return length;
    }

    ListNode* mergeList(ListNode* list1, ListNode* list2){
        // 21. Merge Two Sorted Lists
        ListNode dummyNode(-1);
        ListNode* prev = &dummyNode;
        while(list1 != nullptr && list2 != nullptr){
            if(list1->val < list2->val){
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        
        prev->next = list1 == nullptr ? list2 : list1;

        return dummyNode.next;
    }

public:
    ListNode* sortList(ListNode* head) {
        // Bottom-Up Merge-Sort
        int length = getLength(head);

        ListNode dummyHead(0);
        dummyHead.next = head;

        for (int subl = 1; subl < length; subl *= 2){
            // 1 -> 2 -> 3 -> 4 -> 5
            ListNode* prev = &dummyHead;
            ListNode* cur = dummyHead.next;
            while(cur != nullptr){
                ListNode* list1 = cur;
                for (int i = 1; i < subl && cur->next!=nullptr; ++i)
                    cur = cur->next;
                
                ListNode* list2 = cur->next;
                cur->next = nullptr;
                cur = list2;
                for (int i = 1; i < subl && cur!=nullptr && cur->next!=nullptr; ++i)        // cur could be null
                    cur = cur->next;
                
                ListNode* next = nullptr;
                if (cur != nullptr){
                    next = cur->next;
                    cur->next = nullptr;
                }
                
                ListNode* merged = mergeList(list1, list2);

                prev->next = merged;
                while(prev->next != nullptr)
                    prev = prev->next;
                
                cur = next;
            }
        }

        return dummyHead.next;
    }
};
// @lc code=end

