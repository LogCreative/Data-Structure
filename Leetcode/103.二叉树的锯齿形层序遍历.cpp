/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
 */

#include<vector>
#include<stack>
#include<queue>
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
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == nullptr) return {};
        vector<vector<int>> res;
        bool flag = true;   // normal order
        queue<TreeNode*> prev;
        prev.push(root);
        while(!prev.empty()){
            stack<TreeNode*> layers;
            vector<int> layerel;
            while(!prev.empty()){
                TreeNode* el = prev.front();
                layerel.push_back(el->val);
                if (flag){
                    if (el->left!=nullptr) layers.push(el->left);
                    if (el->right!=nullptr) layers.push(el->right);
                } else {
                    if (el->right!=nullptr) layers.push(el->right);
                    if (el->left!=nullptr) layers.push(el->left);
                }
                prev.pop();
            }
            res.push_back(layerel);
            while(!layers.empty()){
                prev.push(layers.top());
                layers.pop();
            }
            flag =! flag;
        }
        return res;
    }
};
// @lc code=end

