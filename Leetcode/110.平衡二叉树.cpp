/*
 * @lc app=leetcode.cn id=110 lang=cpp
 *
 * [110] 平衡二叉树
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
    int getHeight(TreeNode* root){
        if (root == nullptr) return 0;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

    int Height(TreeNode* root){
        if (root == nullptr) return 0;
        int lheight = Height(root->left);
        int rheight = Height(root->right);
        if (lheight == -1 || rheight == -1 || abs(lheight - rheight) > 1)
            return -1;
        return 1 + max(lheight, rheight);
    }

public:
    bool isBalancedTopDown(TreeNode* root) {
        if (root == nullptr) return true;
        return abs(getHeight(root->left) - getHeight(root->right)) <= 1 &&
            isBalancedTopDown(root->left) && isBalancedTopDown(root->right);
    }
    bool isBalanced(TreeNode* root){
        return Height(root) >= 0;
    }
};

// The other solution is to use the poisonous height transaction.
// @lc code=end

