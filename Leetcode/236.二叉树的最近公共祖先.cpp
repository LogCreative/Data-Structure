/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

#include<iostream>
#include<vector>
#include<unordered_map>
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
class Solution {
    unordered_map<int, TreeNode*> father;

    void dfs(TreeNode* root){
        if (root->left != NULL) {
            father[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != NULL) {
            father[root->right->val] = root;
            dfs(root->right);
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root);
        int cur = p->val;
        vector<TreeNode*> fathersP = {p};
        while(cur != root->val){
            fathersP.push_back(father[cur]);
            cur = father[cur]->val;
        }
        cur = q->val;
        int n = fathersP.size();
        while(true){
            for (auto it = fathersP.begin(); it != fathersP.end(); ++it){
                if ((*it)->val == cur){
                    return *it;
                }
            }
            cur = father[cur]->val;
        }
    }
};
// @lc code=end

