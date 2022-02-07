/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
 */

#include<iostream>
#include<vector>
#include<stack>
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
    vector<int> ans;
    void inorderRecursive(TreeNode* root){
        if (root == nullptr) return ;
        inorderRecursive(root->left);
        ans.push_back(root->val);
        inorderRecursive(root->right);
    }

    struct StNode{
        TreeNode* node;
        int timesPop;
        StNode(TreeNode* n): node(n), timesPop(0) {}
    };

    void inorderIterative(TreeNode* root){
        if (root == nullptr) return ;
        stack<StNode> visiting;
        visiting.push(StNode(root));
        while(!visiting.empty()){
            StNode top = visiting.top();
            visiting.pop();
            if (++top.timesPop == 2){
                ans.push_back(top.node->val);
                if (top.node->right != nullptr)
                    visiting.push(StNode(top.node->right));
            } else {
                visiting.push(top);
                if (top.node->left != nullptr)
                    visiting.push(StNode(top.node->left));
            }
        }
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // inorderRecursive(root);
        inorderIterative(root);
        return ans;
    }
};
// @lc code=end

