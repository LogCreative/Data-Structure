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
        node(const elemType &x,node *N=NULL):data(x),next(n) { }
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
    bool isEmpty() {return front == NULL;}
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
    elemType getHead() {return front->data;}
};