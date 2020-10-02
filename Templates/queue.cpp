#include<iostream>
#include<vector>
using namespace std;

template<class elemType>
class queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() { }
};

// The number of Optimized Queue is not reasonable.
// Try seqList instead. Sometimes we don't need to 
// cut down the space complexity.
//
// front is a waste cell
template<class elemType>
class seqQueue:public queue<elemType>{
private:
    elemType *elem;
    int maxSize;
    int front, rear;
    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2*maxSize];
        for(int k=1;k<=maxSize;++k)             //front 不用
            elem[k]=tmp[(front + k) % maxSize];
        front = 0; rear = maxSize;              //刷新front 和 rear
        maxSize*=2;
        delete[] tmp;
    }
public:
    
    seqQueue(int initSize = 10){
        elem = new elemType[initSize];
        front = rear = 0;
        maxSize = initSize;
    }

    ~seqQueue() {
        delete[] elem;
    }

    void enQueue(const elemType &x){
        if((rear+1)%maxSize==front) doubleSpace();
        rear = (rear + 1) % maxSize;
        elem[rear] = x;
    }

    elemType deQueue(){
        front = (front + 1)%maxSize;        //真实标号
        return elem[front];
    }

    elemType getHead() const {
        return elem[(front+1)%maxSize];
    }

    bool isEmpty() const { return front==rear; }

};

// This is better.
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

void seqQueueTest() {
    seqQueue<int> sq;
    for(int i=0;i<15;++i)   sq.enQueue(i);
    sq.deQueue();
    sq.getHead();
    cout<<(sq.isEmpty()?"YES":"NO")<<'\n';
}

void linkQueueTest() {
    linkQueue<int> sq;
    for(int i=0;i<15;++i)   sq.enQueue(i);
    sq.deQueue();
    sq.getHead();
    cout<<(sq.isEmpty()?"YES":"NO")<<'\n';
}

class MyCircularQueue {
    int* data;
    int front, rear;
    int size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data = new int[k+1];
        front = rear = 0;
        size = k + 1;
    }

    ~MyCircularQueue() { delete[] data; }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()) return false;
        rear = (rear + 1) % size;
        data[rear] = value;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty()) return false;
        front = (front + 1) % size;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return data[(front + 1) % size];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return data[rear % size];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return front==rear;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return ((rear+1)%size==front);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */


int main() {

    // seqQueueTest();

    // linkQueueTest();
    

    return 0;
}

// 应用：
// 火车车厢
// 排队问题