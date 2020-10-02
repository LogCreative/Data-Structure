#include<iostream>
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

// 树的抽象类
template<class T>
class tree {
public:
    virtual void clear() = 0;                           // 清空
    virtual bool isEmpty() const = 0;                   // 判空
    virtual T root(T flag) const = 0;                   // 找根节点 flag是空树特殊值
    virtual T parent(T x, T flag) const = 0;            // 找父节点 flag是不存在或根节点特殊值
    virtual T child(T x, int i, T flag) const = 0;      // 找第i个子节点 flag是不存在或儿子不存在
    virtual void remove(T x, int i) = 0;                // 剪枝-第i课子树
    virtual void traverse() const = 0;                  // 遍历
};

// 二叉树的抽象类
template<class T>
class bTree {
public:
    virtual void clear() = 0;                           // 清空
    virtual bool isEmpty() const = 0;                   // 判空
    virtual T Root(T flag) const = 0;                   // 找根节点 flag是空树特殊值
    virtual T parent(T x, T flag) const = 0;            // 找父节点 flag是不存在或根节点特殊值
    virtual T lchild(T x, T flag) const = 0;            // 找左孩子 flag是不存在特殊值
    virtual T rchild(T x, T flag) const = 0;            // 找右孩子 flag是不存在特殊值
    virtual void delLeft(T x) = 0;                      // 删除左子树
    virtual void delRight(T x) = 0;                     // 删除右子树
    virtual void preOrder() const = 0;                  // 前序遍历
    virtual void midOrder() const = 0;                  // 中序遍历
    virtual void postOrder() const = 0;                 // 后序遍历
    virtual void levelOrder() const = 0;                // 层次遍历
};

// 二叉链表类
template<class T>
class binaryTree : public bTree<T> {
    // 打印树，输出每个节点及其左右儿子，与层次遍历是不同的。
    friend void printTree(const binaryTree &t, T flag){
        linkQueue<T> q;
        q.enQueue(t.root->data);
        cout << '\n';
        while(!q.isEmpty()) {
            T p,l,r;
            p = q.deQueue();
            l = t.lchild(p, flag);                          //调用成员函数访问对象
            r = t.rchild(p, flag);
            cout << p << ' ' << l << ' ' << r << '\n';
            if(l != flag) q.enQueue(l);
            if(r != flag) q.enQueue(r);
        }
    }
private:
    struct Node {                                       // 二叉树的节点类
        T data;                                         // 节点的数据信息，先初始化
        Node *left, *right;                             // 节点的左、右儿子地址

        Node(): left(NULL),right(NULL) {}
        Node(T item, Node *L=NULL, Node *R=NULL): data(item),left(L),right(R) {}
        ~Node() {}
    };

    Node *root;                                         // 二叉树根节点

    //追求函数复用 就定义了一个新的节点 遍历用
    struct StNode {
        Node *node;
        int TimesPop;

        StNode(Node *N=NULL):node(N), TimesPop(0) {}
    };

    // 在子树t中寻找节点x并返回
    Node *find(T x, Node *t) const {
        Node *tmp;
        if (t==NULL) return NULL;
        if (t->data==x) return t;
        if ((tmp = find(x,t->left))!=NULL) return tmp;
        else return find(x,t->right);
    }                     
    
    //递归删除节点
    void clear(Node *&t) {
        if (t==NULL) return ;
        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }

    
    Node* buildTree(T* preOrder, T* inOrder, int pre_to, int in_from, int in_to){
        if(in_from>in_to) return NULL;
        
        T currentval = preOrder[pre_to];
        Node* currentnode = new Node(currentval);
        
        int i;
        for(i = in_from; i < in_to; ++i){
            if(inOrder[i]==currentval)
                break;
        }
        Node* left = buildTree(preOrder,inOrder,pre_to + 1, in_from, i - 1);
        Node* right = buildTree(preOrder,inOrder,pre_to + (i - in_from) + 1, i + 1, in_to);
        currentnode->left = left;
        currentnode->right = right;
        
        return currentnode;
    }

    void preOrder(Node *t) const;
    void midOrder(Node *t) const;
    void postOrder(Node *t) const;
public:
    binaryTree(): root(NULL) {}
    binaryTree(T x) { root = new Node(x); }
    binaryTree(int n,T* preOrder,T* inOrder){
        root = buildTree(preOrder,inOrder,0,0,n-1);
    }
    ~binaryTree() { clear(root); }
    void clear() { clear(root); }
    bool isEmpty() const { return root==NULL; }

    T Root(T flag) const {
        if (root==NULL) return flag;
        else return root->data;
    }

    T parent(T x, T flag) const { return flag; }

    T lchild(T x, T flag) const {
        Node *tmp = find(x,root);
        if (tmp==NULL||tmp->left==NULL) return flag;

        return tmp->left->data;
    }

    T rchild(T x, T flag) const {
        Node *tmp = find(x,root);
        if (tmp==NULL||tmp->right==NULL) return flag;

        return tmp->right->data;
    }

    void delLeft(T x) {
        Node *tmp = find(x,root);
        if (tmp==NULL) return ;
        clear(tmp->left);
    }

    void delRight(T x) {
        Node *tmp = find(x,root);
        if (tmp==NULL) return ;
        clear(tmp->right);
    }

    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    
};

// 递归地定义遍历
template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const {
    if (t==NULL) return ;
    cout << t->data << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const {
    if (t==NULL) return ;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const {
    if (t==NULL) return ;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template<class T>
void binaryTree<T>::preOrder() const {
    linkStack<Node *> s;
    Node *current;

    s.push(root);
    while(!s.isEmpty()) {
        current = s.pop();
        cout << current->data << ' ';
        if (current->right!=NULL) s.push(current->right);
        if (current->left!=NULL) s.push(current->left);
    }

    cout << '\n';
}

template<class T>
void binaryTree<T>::midOrder() const {
    linkStack<StNode> s;
    StNode current(root);

    s.push(current);
    while(!s.isEmpty()){
        current = s.pop();
        if (++current.TimesPop == 2){               //第二次
            cout << current.node->data << ' ';
            if(current.node->right!=NULL)
                s.push(StNode(current.node->right));
        }
        else {                                      //第一次
            s.push(current);
            if(current.node->left!=NULL)
                s.push(StNode(current.node->left));
        }
    }

    cout << '\n';
}

template<class T>
void binaryTree<T>::postOrder() const {
    linkStack<StNode> s;
    StNode current(root);

    s.push(current);
    while(!s.isEmpty()){
        current = s.pop();
        if (++current.TimesPop == 3) {              //第二次
            cout << current.node->data << ' ';
            continue;
        }
        s.push(current);
        if (current.TimesPop == 1) {
            if (current.node->left!=NULL)
                s.push(StNode(current.node->left));
        }
        else {                                      //第一次
            if(current.node->right!=NULL)
                s.push(StNode(current.node->right));
        }
    }

    cout << '\n';
}

template<class T>
void binaryTree<T>::levelOrder() const {
    linkQueue<Node *> que;
    Node *tmp;

    que.enQueue(root);

    while(!que.isEmpty()){
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}



int main(){
    int n;  //长度
    cin >> n;
    
    int *preOrder = new int[n];
    int *midOrder = new int[n];

    for(int i=0;i<n;++i){
        cin >> preOrder[i];
    }

    for(int i=0;i<n;++i){
        cin >> midOrder[i];
    }
    
    binaryTree<int> bt(n,preOrder,midOrder);

    bt.postOrder();

    return 0;

}