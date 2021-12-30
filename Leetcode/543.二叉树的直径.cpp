/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
 */

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
    int ans;
    // This is similar to 153.
    int dfs(TreeNode* root){
        if (root == nullptr)
            return 0;
        int ld = dfs(root->left);
        int rd = dfs(root->right);
        int closed = ld + 1 + rd;
        if (closed > ans)
            ans = closed;
        if (ld > rd) return ld + 1;
        return rd + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans - 1;
    }
};
// @lc code=end

