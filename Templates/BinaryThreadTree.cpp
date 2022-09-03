// 中序线索二叉树

#include<iostream>
using namespace std;

template<class elemType>
struct ThreadNode {
    elemType data;
    ThreadNode *lchild, *rchild;
    int ltag, rtag; // 0 -- 孩子 1 -- 前驱
    ThreadNode() {}
    ThreadNode(char c): data(c) {}
};

template<class elemType>
void inThread(ThreadNode<elemType> *p, ThreadNode<elemType> *&pre) {
    if (p != NULL) {
        inThread(p->lchild, pre);
        if (p->lchild==NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        inThread(p->rchild, pre);
    }
}

template<class elemType>
void createInThread(ThreadNode<elemType> *T) {
    ThreadNode<elemType>* pre = NULL;
    if (T!=NULL) {
        inThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

template<class elemType>
ThreadNode<elemType>* firstNode(ThreadNode<elemType> *p) {
    while(p->ltag == 0) p = p->lchild;
    return p;
}

template<class elemType>
ThreadNode<elemType>* nextNode(ThreadNode<elemType> *p) {
    if (p->rtag == 0) return firstNode(p->rchild);
    return p->rchild;
}

template<class elemType>
ThreadNode<elemType>* lastNode(ThreadNode<elemType> *p) {
    while(p->rtag == 0) p = p->rchild;
    return p;
}

template<class elemType>
ThreadNode<elemType>* prevNode(ThreadNode<elemType> *p) {
    if (p->ltag == 0) return lastNode(p->lchild);
    return p->lchild;
}

template<class elemType>
void inOrder(ThreadNode<elemType>* T) {
    for (ThreadNode<elemType> *p=firstNode(T); p!=NULL; p = nextNode(p))
        cout << p->data << ' ';
    cout << endl;
}

int main() {
    //     A
    //    / \ 
    //   B   C
    //    \  /
    //    D E 
    ThreadNode<char> *root = new ThreadNode<char>('A');
    ThreadNode<char> *el2  = new ThreadNode<char>('B');
    ThreadNode<char> *el3  = new ThreadNode<char>('C');
    ThreadNode<char> *el4  = new ThreadNode<char>('D');
    ThreadNode<char> *el5  = new ThreadNode<char>('E');
    root->lchild = el2; root->ltag = 0;
    root->rchild = el3; root->rtag = 0;
    el2->rchild = el4; el2->rtag = 0;
    el3->lchild = el5; el3->ltag = 0;
    createInThread(root);
    inOrder(root);
    return 0;
}