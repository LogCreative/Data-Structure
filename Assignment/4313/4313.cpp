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
        
        linkStack<int> s1, s2;
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

        while(!s1.isEmpty() && !s2.isEmpty()){
            int p1 = s1.pop();
            int p2 = s2.pop();
            if(p1>p2) return true;
            else if(p1<p2) return false;
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

//不通过：2 330 3