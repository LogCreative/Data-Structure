/*
 * @lc app=leetcode.cn id=450 lang=cpp
 *
 * [450] 删除二叉搜索树中的节点
 */

#include<iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    // sperate to another function with different parameter settings.
    void remove(int x, TreeNode*&t){
        if (t==nullptr) return ;
        if (x<t->val) remove(x,t->left);
        else if (x>t->val) remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr){
            TreeNode* tmp = t->right;
            while(tmp->left!=nullptr) tmp = tmp->left;
            t->val = tmp->val;
            remove(t->val, t->right);
        } else {
            TreeNode* oldNode = t;
            t = (t->left!=nullptr)?t->left:t->right;
            delete oldNode;
        }
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        remove(key, root);
        return root;
    }
};
// @lc code=end

