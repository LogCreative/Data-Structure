// 1211.cpp
// 给出一棵二叉树的结构,判断这棵二叉树是不是完全二叉树。

#include<iostream>
using namespace std;

// 链接队列
template<class elemType>
class queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

template<class elemType>
class linkQueue: public queue<elemType>{
private:
    struct node {
        elemType data;
        node *next;
        node(const elemType &x,node *N=NULL):data(x),next(N) { }
        node():next(NULL) { }
        ~node() { }
    };

    node *front,*rear;
public:
    linkQueue() {front=rear=NULL;}
    ~linkQueue() {
        node *tmp;
        while(front!=NULL){
            tmp=front;
            front=front->next;
            delete tmp;
        }
    }
    bool isEmpty() const {return front == NULL;}
    void enQueue(const elemType &x) {
        if(rear==NULL)
            front=rear=new node(x);
        else
        {
            rear->next=new node(x);
            rear=rear->next;
        }
    }
    elemType deQueue() {    //空队不应出队
        node*tmp=front;
        elemType value=front->data;
        front=front->next;
        if(front==NULL) rear=NULL;
        delete tmp;
        return value;
    }
    elemType getHead() const {return front->data;}
};

// 不使用派生类了
// 整型二叉树 用于判定是不是完全二叉树
// 顺序实现 数组
class BinaryTree{
private:
    int *tree[2];
    int root;   //根节点编号
    int N;      //个数

    linkQueue<int> levelNum;  //层次遍历队列

public:
    BinaryTree(int n) {
        // 根据题意创建二叉树

        int i;
        N=n;

        // 初始化数组，第0行不用
        tree[0] = new int[N+1];     //该行存储左儿子
        tree[1] = new int[N+1];     //该行存储右儿子

        // 根节点将不会作为儿子出现
        // 使用一个数组存储儿子状态
        // 第 0 个不用
        bool *tmp = new bool[N+1];
        //全部初始化为false
        for(i=1;i<N+1;++i)
            tmp[i]=false;

        // 输入
        for(i=1;i<N+1;++i){
            int P,Q;
            cin>>P>>Q;
            tree[0][i] = P; tmp[P]=true;
            tree[1][i] = Q; tmp[Q]=true;
        }

        //寻找根节点
        for(i=1;i<N+1;++i)
            if(tmp[i]==false)
                {root = i; break;}

        delete[] tmp;
    }

    ~BinaryTree() { 
        delete[] tree[0];
        delete[] tree[1]; 
    }

    //层次遍历
    //判定是不是完全二叉树，反向判定，从小到大遍历节点
    //判据1：如果该节点只有右儿子，则不是
    //判据2：如果该节点没有右儿子，而比它大的编号有儿子，则不是。
    bool isCBT() {
        //只有左儿子的flag
        bool leftOnly = false;
        //根节点进队
        levelNum.enQueue(root);

        //层次遍历
        while(!levelNum.isEmpty()){
            int current = levelNum.deQueue();   //当前节点
            int lchild = tree[0][current];      //左儿子
            int rchild = tree[1][current];      //右儿子
            
            //非0进队
            if(lchild!=0)
                levelNum.enQueue(lchild);
            if(rchild!=0)
                levelNum.enQueue(rchild);

            //判定
            if(leftOnly && !(lchild==0 && rchild==0))
                return false;

            if(lchild==0 && rchild!=0)
                return false;
            
            if(rchild==0)
                leftOnly = true;

        }
        return true;
    }

};


int main() {

    int N;  // 节点总数
    cin>>N;

    BinaryTree tree(N);

    cout<<(tree.isCBT()?'Y':'N')<<'\n';

    return 0;
}
