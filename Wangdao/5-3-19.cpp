// 二叉树的带权路径长度（WPL）

#include<iostream>
#include<queue>
using namespace std;

struct TreeNode {
    int weight;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {}
    TreeNode(int w): weight(w) {}
};

int wpl(TreeNode* root) {
    int wpl = 0;
    if (!root) return wpl;
    queue<TreeNode*> q;
    q.push(root);
    int curLevel = -1;
    while(!q.empty()) {
        int curSize = q.size();
        ++curLevel;
        for (int i = 0; i < curSize; ++i) {
            TreeNode* r = q.front();q.pop();
            if (r->left) q.push(r->left);
            if (r->right) q.push(r->right);
            if (!r->left && !r->right){
                cout << r->weight << '*' << curLevel << endl;
                wpl += curLevel * r->weight;
            }
        }
    }
    return wpl;
}

int wplrec(TreeNode* root, int deep) {
    int wpl = 0;
    if (root) {
        if (!root->left && !root->right) wpl += deep * root->weight;
        wpl+= wplrec(root->left, deep+1);
        wpl+= wplrec(root->right, deep+1);
    }
    return wpl;
}


int main() {
    TreeNode* root = new TreeNode();
    TreeNode *el1 = new TreeNode(), *el2 = new TreeNode(2), *el3 = new TreeNode(4), *el4 = new TreeNode(), *el5 = new TreeNode(7), *el6 = new TreeNode(5);
    root->left = el1; root->right = el2;
    el1->left = el3; el1->right = el4;
    el4->left = el5; el4->right = el6;
    //    o
    //   / \ 
    //  o   2
    // /\ 
    // 4 o
    //  / \ 
    // 7   5
    cout << wpl(root) << endl;
    cout << wplrec(root, 0) << endl;
    return 0;
}