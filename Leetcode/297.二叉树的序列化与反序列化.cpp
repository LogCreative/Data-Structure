/*
 * @lc app=leetcode.cn id=297 lang=cpp
 *
 * [297] 二叉树的序列化与反序列化
 */

#include<iostream>
#include<string>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // Layer Traverse.
        queue<TreeNode*> q;
        q.push(root);
        string ser = "[";
        while(!q.empty()){
            TreeNode* f = q.front();
            q.pop();
            if (f == nullptr){
                ser += "null";
            } else {
                ser += to_string(f->val);
                q.push(f->left);
                q.push(f->right);
            }
            if (!q.empty()) ser += ',';
        }
        ser += "]";
        // cout << ser << endl;
        return ser;
    }

    // Think about:
    // [1,2,3,null,null,4,5,6,7]
    //       1
    //      / \
    //     2   3
    //    n n / \
    //       4   5
    //      /\
    //     6  7

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int num;
        int sign;
        int state = -1;
        queue<TreeNode*> q;
        TreeNode* root = nullptr;
        bool flag = false;
        for (char c : data){
            if (c == '['){
                num = 0;
                sign = 1;
            } else if (c == ',' || c == ']'){
                TreeNode* head;
                if (flag) {head = nullptr;}
                else head = new TreeNode(sign * num);
                if (root == nullptr) root = head;
                if (head != nullptr) q.push(head);
                if (++state == 2){
                    state = 0;
                    if (q.front()!=nullptr){
                        q.front()->right = head;
                        // cout << q.front()->val << "r " << num << endl;
                    }
                    q.pop();
                } else if (state == 1){
                    if (q.front()!=nullptr) {
                        q.front()->left = head;
                        // cout << q.front()->val << "l " << num << endl;
                    }
                }
                num = 0;
                sign = 1;
                flag = false;   // always resign the flag.
                continue;
            } else if (c == '-'){
                sign = -1;
            } else if (c >= '0' && c <= '9'){
                num = num*10 + c - '0';
            } else {
                flag = true;        // null
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
// @lc code=end

