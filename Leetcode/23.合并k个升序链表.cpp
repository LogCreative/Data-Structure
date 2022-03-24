/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并K个升序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
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

    ListNode* merge(vector<ListNode*>& lists, int left, int right){
        if (left == right) return lists[left];
        if (left > right) return nullptr;
        int mid = left + (right - left) / 2;
        return mergeTwoLists(merge(lists, left, mid), merge(lists, mid+1, right));
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists){
        return merge(lists, 0, lists.size() - 1);
    }

    ListNode* mergeKListsBrutal(vector<ListNode*>& lists) {
        vector<int> pending(lists.size());
        int n = lists.size();
        for (int i = 0; i < n; ++i) pending[i] = i;
        ListNode dummyHead(-1);
        ListNode* prevNode = &dummyHead;

        // 穿针引线
        while(!pending.empty()){
            ListNode* minNode = nullptr;
            int minIndex = -1;
            for (auto it = pending.begin(); it != pending.end();){
                ListNode* curNode = lists[*it];
                if (curNode==nullptr) {
                    it = pending.erase(it);
                    continue;
                }
                if (minNode == nullptr || curNode->val < minNode->val) {
                    minNode = curNode;
                    minIndex = *it;
                }
                ++it;
            }
            if (minNode){
                prevNode->next = minNode;
                lists[minIndex] = minNode->next;
                prevNode = minNode;
            }
        }

        return dummyHead.next;
    }
};
// @lc code=end
