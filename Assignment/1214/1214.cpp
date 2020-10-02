// 1214.cpp
// traverse 给出一棵孩子兄弟表示法下的树的结构以及各个结点的权值，要求按先序、后序、层次遍历二叉树并输出各个结点的权值。

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

template<class elemType>
class stack{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};

template<class elemType>
class linkStack: public stack<elemType>{
private:
    struct node{
      elemType data;
      node *next;
      node(const elemType &x,node *N=NULL)  {data =x;next=N;}
      node():next(NULL){}
      ~node(){}
    };
    node *top_p;
public:
    linkStack(){
        top_p=NULL;
    }
    ~linkStack(){
        node *tmp;
        while (top_p!=NULL){
            tmp=top_p;
            top_p=top_p->next;
            delete tmp;
        }
    }
    bool isEmpty() const {
        return top_p==NULL;
    }
    void push(const elemType &x){
        top_p=new node(x,top_p);    //四件事情
    }
    elemType pop(){
        node *tmp=top_p;
        elemType x= tmp->data;
        top_p=top_p->next;
        delete tmp;
        return x;
    }
    elemType top() const{
        return top_p->data;
    }
};

class BinaryTree {
private:
    struct Node {
        long data;
        Node* child,*cousin;
        int Num;    //编号，构建时使用
        Node():child(NULL),cousin(NULL),Num(0) { }
        Node(int Nu,long item, Node* Cd=NULL, Node* Cn=NULL):
            data(item),child(Cd),cousin(Cn),Num(Nu) { }
    };

    Node *root;
    int N;  //规模

    void preOrder(Node *t) const {
        if(t==NULL) return ;
        cout<<t->data<<' ';
        preOrder(t->child);
        preOrder(t->cousin);
    }

    void delOrder(Node *t) const {
        if(t==NULL) return ;
        delOrder(t->child);
        delOrder(t->cousin);
        delete t;
    }

public:
    BinaryTree(int** relation, long* weight, int n){
        
        N=n;
        int i;

        //先构建root
        // 根节点将不会作为儿子出现
        // 使用一个数组存储儿子状态
        // 第 0 个不用
        bool *tmp = new bool[N+1];
        //全部初始化为false
        for(i=1;i<N+1;++i)
            tmp[i]=false;
        for(int i=1;i<N+1;++i){
            tmp[relation[0][i]]=true;
            tmp[relation[1][i]]=true;
        }

        linkQueue<Node *> SQueue;   //存储队列

        for(int i=1;i<N+1;++i)
            if(tmp[i]==false)
                {
                    root = new Node(i,weight[i]);
                    SQueue.enQueue(root);      //根节点进队
                    break;
                }
        
        //再构建结构
        /*使用队列遍历，直到队列为空*/
        while(!SQueue.isEmpty()){

            Node* tmp = SQueue.deQueue();
            int tmpNum = tmp->Num;
            int child = relation[0][tmpNum];
            int cousin = relation[1][tmpNum];
            Node* childN, *cousinN;
            if(child!=0){
                childN = new Node(child,weight[child]);
                tmp->child = childN;
                SQueue.enQueue(childN);
            }
            if(cousin!=0){
                cousinN = new Node(cousin,weight[cousin]); 
                tmp->cousin=cousinN;
                SQueue.enQueue(cousinN);
            }
            
        }
        //此时队列为空

    }

    ~BinaryTree() {
        delOrder(root);
    }

    //前序
    void preOrder() const { 
        preOrder(root); 
        cout<<"\n";
    }

    //后序
    void postOrder() const {
        //存储是否被输出过的数组
        bool* isOutput=new bool[N+1];
        for(int i=1;i<N+1;++i)
            isOutput[i]=false;
        
        linkStack<Node *> ChildStack;

        ChildStack.push(root);

        //栈不为空
        while (!ChildStack.isEmpty())
        {   
            //出栈
            Node *tmp = ChildStack.top();

            Node *child=tmp->child;
            //有儿子且儿子没被输出过
            if(child!=NULL&&!isOutput[child->Num])
                ChildStack.push(child); //进栈
            else
            {
                //输出
                cout<<tmp->data<<' ';
                isOutput[tmp->Num]=true;
                ChildStack.pop();
                //有兄弟且兄弟没被输出过
                Node *cousin=tmp->cousin;
                if(cousin!=NULL&&!isOutput[cousin->Num])
                    ChildStack.push(cousin);
                    //兄弟进栈
            }   
        }

        delete[] isOutput;

        cout<<"\n";
    }

    //层次
    void levelOrder() const {
        linkQueue<Node *> ChildQueue;  //存储儿子队列
        ChildQueue.enQueue(root);
        while(!ChildQueue.isEmpty()){
            Node *tmp = ChildQueue.deQueue();
            cout<<tmp->data<<' ';
            if(tmp->child!=NULL)
                ChildQueue.enQueue(tmp->child); //儿子进队
            while(tmp->cousin!=NULL){   //该层遍历
                tmp=tmp->cousin;
                cout<<tmp->data<<' ';
                if(tmp->child!=NULL)
                    ChildQueue.enQueue(tmp->child); //儿子进队
            }
        }
        cout<<"\n";
    }

};

int main() {
    int N;
    cin>>N;

    int* input[2];
    input[0] = new int[N+1];        //存左儿子
    input[1] = new int[N+1];        //存右兄弟
    long* weight = new long[N+1];   //存权值
    for(int i=1;i<N+1;++i)
        cin>>input[0][i]>>input[1][i]>>weight[i];
    
    BinaryTree tree(input,weight,N);

    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();

    return 0;
}