// 输出表达式树的中缀表达式

#include<iostream>
using namespace std;

typedef struct node {
    char data[10];
    struct node *left, *right;
    // For convenience
    node() {};
    node(char c) {data[0] = c; data[1] = '\0';}
} STree;

void printInfixExpression(STree* root, int depth) {
    if (!root) return ;
    if (!root->left && !root->right) {
        cout << root->data;
        return ;
    }
    if (depth > 0) cout << '(';
    if (root->left) printInfixExpression(root->left, depth + 1);
    cout << root->data;
    if (root->right) printInfixExpression(root->right, depth + 1);
    if (depth > 0) cout << ')';
}

int main() {
    //     *
    //    / \ 
    //   +   *
    //  / \ / \ 
    // a  b c  -
    //          \ 
    //           d
    STree* root = new STree('*');
    STree* el1 = new STree('+'), *el2 = new STree('*'), *el3 = new STree('a'),
    *el4 = new STree('b'), *el5 = new STree('c'), *el6 = new STree('-'),
    *el7 = new STree('d');
    root->left = el1; root->right = el2;
    el1->left = el3; el1->right = el4;
    el2->left = el5; el2->right = el6;
    el6->right = el7;
    printInfixExpression(root, 0); cout << endl;
    printInfixExpression(el6, 0); cout << endl;     // no brackets
    return 0;
}