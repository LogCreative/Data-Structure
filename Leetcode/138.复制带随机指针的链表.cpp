/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 复制带随机指针的链表
 */

#include<iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) return NULL;

        Node* newhead = new Node(head->val);
        
        // a) copy next elements only.
        //        a1->a2->a3->
        //        b1  b2
        // newprev^   ^curptr
        int cnt = 1;
        Node* newprev = newhead;
        for(Node* oldptr = head->next;
            oldptr != NULL;
            oldptr = oldptr->next, ++cnt){
                Node* curptr = new Node(oldptr->val);
                newprev->next = curptr;
                newprev = curptr;
            }

        // b) allocate the index map.
        Node** indexhead = new Node*[cnt];
        Node* newptr = newhead;
        for (int i = 0; i < cnt; ++i){
            indexhead[i] = newptr;
            newptr = newptr->next;
        }

        // c) assign new random 
        //    based on searching of old delta of random
        //    using running at the same time
        //    and stop when one end finds the target.
        //         a1->a2->a3->a4->a5
        //  oldrand^       ^oldptr
        Node* oldptr = head;
        for (int i = 0; i < cnt; ++i){
            Node* oldrand = oldptr->random;

            if (oldrand == NULL)
                indexhead[i]->random = NULL;
            else{
                Node* oldrand_ = oldrand;
                Node* oldptr_ = oldptr;
                int dist = 0;
                for(; oldrand_ != oldptr && oldptr_ != oldrand; 
                    oldrand_ = oldrand_ == NULL ? NULL : oldrand_->next, 
                    oldptr_ = oldptr_ == NULL ? NULL : oldptr_->next, 
                    ++dist){}
                if (oldrand_ == oldptr) indexhead[i]->random = indexhead[i-dist];
                else indexhead[i]->random = indexhead[i+dist];
            }

            oldptr = oldptr->next;
        }

        delete[] indexhead;

        return newhead;
    }

    /*
        Should use spliting node method.
           _____________________
           |                    |rand
        oldnode    oldnode    oldnode
            \     /     \     /    \
            newnode     newnode     newnode
    */
};
// @lc code=end

