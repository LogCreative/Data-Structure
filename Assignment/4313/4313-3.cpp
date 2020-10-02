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
class seqStack:public stack<elemType>{
private:
    elemType *elem;
    int top_p;          //栈顶指针
    int maxSize;
    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2*maxSize];
        for(int i=0;i<maxSize;++i) elem[i]=tmp[i];
        maxSize *= 2;       //后赋值，因为没有currentLength
        delete[] tmp;
    }
public:
    
    seqStack(int initSize = 10){
        elem = new elemType[initSize];
        top_p = -1;
        maxSize = initSize;
    }

    seqStack(const seqStack<elemType> &s){
        maxSize = s.maxSize;
        elem = new elemType[maxSize];
        top_p = s.top_p;
        for(int i=0;i<=top_p;++i)
            elem[i] = s.elem[i];
    }

    ~seqStack() { delete[] elem; }

    bool isEmpty() const {return top_p==-1;}

    elemType pop() { return elem[top_p--]; }    //返回的是 top_p

    void push(const elemType &x){
        if(top_p == maxSize - 1)    doubleSpace();
        elem[++top_p] = x;
    }

    elemType top() const { return elem[top_p]; } 
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

// 0 号元素不存，最大化堆
template<class Type>
class priorityQueue_m: public queue<Type> {
private:
    int currentSize;                            // 队列长度
    Type *array;
    int maxSize;                                // 容量

    void doubleSpace() {
        Type *tmp = array;
        maxSize *= 2;
        array = new Type[maxSize];
        for (int i=0; i<=currentSize; ++i)
            array[i] = tmp[i];
        delete[] tmp;
    }

    void buildHeap(){
        for(int i=currentSize/2;i>0;--i)
            percolateDown(i);
    }

    void percolateDown(int hole){
        int child;
        Type tmp = array[hole];

        for(; hole*2<=currentSize; hole=child) {
            child = hole * 2;
            if (child != currentSize && array[child+1]>array[child])    // 较小的一个
                ++child;
            if (array[child]>tmp)
                array[hole] = array[child];                             // 换掉
            else break;
        }
        array[hole] = tmp;
    }

public:

    priorityQueue_m(int capacity=100){
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue_m(const Type item[], int size): 
        maxSize(size+10),currentSize(size) {
        array = new Type[maxSize];
        for(int i = 0; i<size; ++i)
            array[i+1] = item[i];
        buildHeap();
    }

    ~priorityQueue_m() { delete[] array; }

    bool isEmpty() const { return currentSize==0; }

    void enQueue(const Type &x) {
        if(currentSize==maxSize-1) doubleSpace();

        //向上过滤
        int hole = ++currentSize;
        for(; hole>1 && x>array[hole/2]; hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }

    Type deQueue() {
        Type minItem;
        minItem = array[1];
        array[1]=array[currentSize--];
        percolateDown(1);
        return minItem;
    }

    Type getHead() const { return array[1]; }
};

struct dicint {
    int data;
    int length;             //位数

    dicint():data(-1),length(-1) {}

    dicint(int d):data(d) {
        if(d==0) length=0;          //零只能放最后，实际上
        else{ 
            length = 0;
            while(d>0) {
                ++length;
                d/=10;
            }
        }
    }

    friend bool operator>(dicint di1,dicint di2) {
        if(di1.length==0) return false;
        if(di2.length==0) return true;
        //都不是0

        seqStack<int> s1, s2;
        int d1 = di1.data, d2 = di2.data;
        int base = 1;
        for(int i = 1;i<=di1.length;++i){
            s1.push(d1/base % 10);
            base*=10;
        }
        base = 1;
        for(int i = 1;i<=di2.length;++i){
            s2.push(d2/base % 10);
            base*=10;
        }
        
        seqStack<int> sb1 = s1, sb2 = s2;

        seqQueue<int> q1(di1.length + di2.length),
                    q2(di2.length + di1.length);

        // s1 + s2
        while(!s1.isEmpty())
            q1.enQueue(s1.pop());
        while(!s2.isEmpty())
            q1.enQueue(s2.pop());

        // s2 + s1
        while(!sb2.isEmpty())
            q2.enQueue(sb2.pop());
        while(!sb1.isEmpty())
            q2.enQueue(sb1.pop());

        while(!q1.isEmpty()){
            //逐个位置比较
            int digit1 = q1.deQueue(), digit2 = q2.deQueue();
            if(digit1>digit2) return true;
            else if(digit1<digit2) return false;
        }
        return false;
    }
};

int main(){
    int n;      //数据量
    cin >> n;

    priorityQueue_m<dicint> pq;
 
    for(int i = 0;i<n;++i){
        int data;
        cin >> data;
        dicint di(data);
        pq.enQueue(di);
    }
    
    while(!pq.isEmpty()){
        dicint dim = pq.deQueue();
        cout << dim.data;
    }
 
    cout << '\n';

    return 0;
}