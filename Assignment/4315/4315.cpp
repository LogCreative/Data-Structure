#include<iostream>
using namespace std;

//https://leetcode-cn.com/problems/invert-binary-tree/solution/fan-zhuan-er-cha-shu-by-leetcode/

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v, TreeNode* l = NULL, TreeNode* r = NULL): val(v), left(l), right(r) {}
    ~TreeNode() {}
};

TreeNode * Mirror(TreeNode *root){
    if(root==NULL) return NULL;
    TreeNode *right = Mirror(root->right);
    TreeNode *left = Mirror(root->left);
    root->left = right;
    root->right = left;
    return root;
}

void postOrder(TreeNode *root) {
    if(root==NULL) return ;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << ' ';
}

void clear(TreeNode *&root){
    if(root==NULL) return ;
    clear(root->left);
    clear(root->right);
    delete root;
    root = NULL;
}

int main(){
    int n;
    cin >> n;
    
    int count = 0;

    int A, B, C;
    cin >> A;

    // 假设是层序遍历

    linkQueue<TreeNode *> tq;
    TreeNode* root = new TreeNode(A);
    tq.enQueue(root);

    while(!tq.isEmpty() && count < n){

        TreeNode* cur = tq.deQueue();

        if(cur!=root)
            cin >> A >> B >> C;
        else 
            cin >> B >> C;
        ++count;

        if(B!=-1) tq.enQueue(cur->left = new TreeNode(B));
        if(C!=-1) tq.enQueue(cur->right = new TreeNode(C));

    }

    Mirror(root);

    //后序遍历
    postOrder(root);

    clear(root);

    return 0;
}