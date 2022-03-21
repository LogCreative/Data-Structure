/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* p = head, *q = p ->next, *r = head, *s = head;
        ListNode* tmp = head->next;
        bool flag = true;
        // HEAD
        // 1 -> 2 -> 3 -> 4    1
        // ^p,r ^q   ^tmp
        // 1 <- 2    3 -> 4    2
        // ^r   ^p   ^q
        // 1 <- 2 <- 3    4    3? -> 0
        // ^r        ^p   ^q,s
        // |--------------
        // ^r             ^p,s  ^q
        // 1 <- 2 <- 3    4
        //           ^ head
        // 1 <- 2 <- 3    4 <- 5 <- 6   7
        // ^r             ^s        ^p  ^q
        //                ^r            ^s,p  ^q
        // MID
        // 
        // TAIL
        // 5 -> 6
        // 5 <- 6 NULL
        // 5 -> 6 RECOVER

        // 1 -> 2 -> 3 -> 4 -> 5
        // 1 <- 2    3 <- 4

        int n = 0;
        while(q!=nullptr){
            if (++n < k){
                tmp = q->next;
                q->next = p;
                p = q;
                q = tmp;
            } else {
                n = 0;
                if (flag) {
                    head = p;
                    flag = false;
                } else {
                    r->next = p;
                    r = s;
                }
                s = q;
                p = q;
                q = q->next;
            }
        }

        if (n == k - 1){
            if (flag) head = p;
            r->next = p;
            s->next = nullptr;
        } else {
            // 5 <- 6 <- 7
            //           ^p  ^q
            //      ^q   ^p
            // ^tmp
            //      6 -> 7
            q = p->next;
            p->next = nullptr;
            while(--n > 0){
                tmp = q->next;
                q->next = p;
                p = q;
                q = tmp;
            }
            r->next = s;
        }

        return head;
    }
};
// @lc code=end

int main(){
    ListNode p1 = ListNode(1);
    ListNode p2 = ListNode(2);
    ListNode p3 = ListNode(3);
    ListNode p4 = ListNode(4);
    ListNode p5 = ListNode(5);
    p1.next = &p2;
    p2.next = &p3;
    p3.next = &p4;
    p4.next = &p5;
    Solution s;
    ListNode* head = s.reverseKGroup(&p1, 2);
    while(head!=nullptr){
        cout << head->val << " ";
        head = head->next;
    }
    return 0;
}