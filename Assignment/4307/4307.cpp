// 4311. 二叉树的倾斜度
#include<iostream>
#include<cmath>
using namespace std;

template<class elemType>
class stack{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~stack() { }
};

template<class elemType>
class linkStack:public stack<elemType>{
private:
    struct node
    {
        elemType data;
        node* next;
    
        node():next(NULL) {}
        node(const elemType &x,node *n = NULL):data(x),next(n) {}
        ~node() {}
    };
    node* top_p;

public:
    linkStack(int initSize = 10) {
        top_p = NULL;
    }

    ~linkStack(){
        node* tmp;
        while(top_p!=NULL){         //注意指标条件
            tmp = top_p;
            top_p = top_p->next;
            delete tmp;
        }
    }

    bool isEmpty() const { return top_p==NULL; }

    void push(const elemType &x){ top_p = new node(x,top_p); }

    elemType pop() {
        node *tmp = top_p;
        elemType x = tmp->data;
        top_p = top_p->next;
        delete tmp;
        return x;
    }

    elemType top() const { return top_p->data; }
};

template<class elemType>
class queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() { }
};

template<class elemType>
class linkQueue:public queue<elemType>{
private:
    struct node
    {
        elemType data;
        node *next;

        node():next(NULL) {}
        node(const elemType &x,node *n = NULL):data(x),next(n) {}
        ~node() {}    
    };

    node *front,*rear;
    
public:

    linkQueue() { front = rear = NULL; }

    ~linkQueue() {
        node*tmp;
        while(front!=NULL){
            tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    elemType deQueue() {
        node* tmp = front;
        elemType x = tmp->data;
        front = front->next;
        if (front==NULL) rear = NULL;
        delete tmp;
        return x;
    }

    void enQueue(const elemType &x){
        if(rear==NULL)
            front = rear = new node(x);
        else
            rear = rear->next = new node(x);     // rear->next 先被赋值，然后再赋给 rear 上
    }

    elemType getHead() const { return front->data; }

    bool isEmpty() const { return front==NULL; }        //注意不是两者相等

};

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    int sum = 0;            //子节点的和    倾斜度计算
    int degree = 0;         //该节点倾斜度  树的计算

    TreeNode():left(NULL),right(NULL) {}
    TreeNode(int v,TreeNode *l=NULL,TreeNode *r=NULL):val(v),left(l),right(r) {}
    ~TreeNode() {}
};

class bTree{
private:
    TreeNode* root;

    void clear(TreeNode *&t) {
        if (t==NULL) return ;
        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }

    int computeSum(TreeNode *&t){            //自底而上
        if(t==NULL) return 0;
        int leftSum = computeSum(t->left);
        int rightSum = computeSum(t->right);
        t->sum = leftSum + rightSum + t->val;
        return t->sum;
    }

    void computeDegree(TreeNode *&t){
        if(t==NULL) return ;
        int leftSum = (t->left==NULL)?0:t->left->sum;
        int rightSum = (t->right==NULL)?0:t->right->sum;
        t->degree = abs(leftSum - rightSum);
        computeDegree(t->left);
        computeDegree(t->right);
    }

    int getTreeDegree(TreeNode *t){    //前序遍历
        if(t==NULL) return 0;
        int leftDegree = getTreeDegree(t->left);
        int rightDegree = getTreeDegree(t->right);
        return leftDegree + rightDegree + t->degree;
    }

public:
    bTree(int n){   //至少有一个
        int tmp;
        linkQueue<TreeNode *> que;

        cin >> tmp;
        root = new TreeNode(tmp);
        que.enQueue(root);
        bool flag = false;          //判断左右子树

        for(int i = 1; i<n; ++i){
            cin >> tmp;
            
            TreeNode* tn = (tmp==-1)?NULL:new TreeNode(tmp);
            que.enQueue(tn);

            TreeNode* f = que.getHead();
            
            if(flag){               //右节点
                if(f!=NULL) que.deQueue()->right = tn;
                else que.deQueue(); 
            }
            else                 //左节点
                if(f!=NULL) que.getHead()->left = tn;
            
            flag = !flag;
        }
    }

    ~bTree() {clear(root);}

    int getTreeDegree(){
        computeSum(root);                   //刷新每个节点的和
        computeDegree(root);                //刷新每个节点的倾斜度
        return getTreeDegree(root);         //返回
    }

};

int main(){
    int n;
    cin >> n;

    if(n==0){
        cout<<0<<'\n'; return 0;
    }

    bTree bt(n);
    cout<<bt.getTreeDegree()<<'\n';

    return 0;
}
