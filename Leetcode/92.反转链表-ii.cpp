// @before-stub-for-debug-begin
#include <vector>
#include <string>

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // 1 -> 2 -> 3 -> 4 -> 5
        // ^p   ^q
        // ^prev^p,cur^q   ^tmp
        //      2 <- 3 <- 4
        // ^prev^cur      ^p   ^q

        // 1 -> 2 -> 3 -> 4
        // ^p   ^q
        
        ListNode* p = head, *q = p->next;
        ListNode* prev, *cur, *tmp;

        int n = 1;
        
        if (left == 1){
            prev = nullptr;
            cur = p;
        }
        if (right == left) return head;

        while(q!=nullptr){
            if (n <= left - 1){
                if (n == left - 1){
                    prev = p;
                    cur = q;
                }
                p = q;
                q = q->next;
            } else{
                tmp = q->next;
                q->next = p;
                p = q;
                q = tmp;
            }
            if(++n==right){
                if (prev) prev->next = p;
                else head = p;
                cur->next = q;
                break;
            }
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
    ListNode* head = s.reverseBetween(&p1, 2, 4);
    while(head!=nullptr){
        cout << head->val << " ";
        head = head->next;
    }
    return 0;
}