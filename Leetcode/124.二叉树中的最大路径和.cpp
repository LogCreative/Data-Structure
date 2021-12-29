/*
 * @lc app=leetcode.cn id=124 lang=cpp
 *
 * [124] 二叉树中的最大路径和
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
 */
class Solution {
    int closedmax;

    int dfs(TreeNode* root){
        if (root == nullptr) return 0;
        int curmax = root->val;
        if (closedmax < curmax){
            closedmax = curmax;
        }
        int leftmax = dfs(root->left);
        int rightmax = dfs(root->right);
        if (leftmax > 0)
            curmax = leftmax + root->val;
        if (rightmax + root->val > curmax)
            curmax = rightmax + root->val;
        int closedpath = leftmax + root->val + rightmax;    // curmax contributes here
        if (closedpath > closedmax){
            // will not update the curmax,
            // but update the closedmax
            closedmax = closedpath;
        }
        if (curmax < 0) return 0;   // will not be selected 
        return curmax;
    }

public:
    int maxPathSum(TreeNode* root) {
        closedmax = root->val; // just initialize it with an arbitraty node.
        dfs(root);
        return closedmax;
    }
};
// @lc code=end

