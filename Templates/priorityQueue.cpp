#include<iostream>
using namespace std;

// For a Harvest Binary Tree with the height of h, 
// the total number of percorlating down can not 
// exceed the maximum of N-h.

template<class elemType>
class queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() { }
};

// 0 号元素不存，最小化堆
template<class Type>
class priorityQueue: public queue<Type> {
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
            if (child != currentSize && array[child+1]<array[child])    // 较小的一个
                ++child;
            if (array[child]<tmp)
                array[hole] = array[child];                             // 换掉
            else break;
        }
        array[hole] = tmp;
    }

public:

    priorityQueue(int capacity=100){
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue(const Type item[], int size): 
        maxSize(size+10),currentSize(size) {
        array = new Type[maxSize];
        for(int i = 0; i<size; ++i)
            array[i+1] = item[i];
        buildHeap();
    }

    ~priorityQueue() { delete[] array; }

    bool isEmpty() const { return currentSize==0; }

    void enQueue(const Type &x) {
        if(currentSize==maxSize-1) doubleSpace();

        //向上过滤
        int hole = ++currentSize;
        for(; hole>1 && x<array[hole/2]; hole/=2)
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

void pQueueTest() {
    priorityQueue<int> q;
    q.enQueue(10);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(0);
    while (!q.isEmpty())
    {
        cout<<q.deQueue()<<' ';
    }
}

int main(){
    pQueueTest();
    return 0;
}