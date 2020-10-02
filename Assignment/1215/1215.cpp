// 1215 bernoulli

#include<iostream>
#include<cstring>
using namespace std;

template<class elemType>
class queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

//最小堆优先级队列
template<class Type>
class priorityQueue: public queue<Type> {
private:
    int currentSize;
    Type* array;
    int maxSize;

    void doubleSpace(){
        Type *tmp = array;
        maxSize*=2;
        array=new Type[maxSize];
        for(int i=0;i<=currentSize;++i)     //0没了
            array[i]=tmp[i];
        delete[] tmp;
    }

    //void buildHeap();

    void percolateDown(int hole){
        int child;
        Type tmp = array[hole];

        for(;hole*2<=currentSize;hole=child){
            child=hole*2;
            if(child!=currentSize && array[child+1]<array[child])
                child++;
            if(array[child]<tmp)
                array[hole]=array[child];
            else
                break;
        }
        array[hole]=tmp;
    }
public:
    priorityQueue(int capacity=100){
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    ~priorityQueue(){ delete[] array; }

    bool isEmpty() const { return currentSize==0; }

    void enQueue(const Type &x){
        if(currentSize==maxSize-1) doubleSpace();

        //percolateUp
        //完全二叉树下一个
        int hole = ++currentSize;
        //比较并交换
        for(;hole>1 && x<array[hole/2];hole/=2)
            array[hole] = array[hole/2];
        array[hole]=x;  //填补空位

    }

    Type deQueue(){
        Type minItem;
        minItem = array[1];
        array[1]=array[currentSize--];  //覆盖原值
        percolateDown(1);
        return minItem;
    }

    Type getHead() const { return array[1]; }

};

int main() {
    int M;  //总操作数
    cin>>M;

    char operation[7];
    int op;
    int* min=new int[M];
    int mincount=0;

    priorityQueue<int> pqueue;

    for(int i=0;i<M;++i){
        cin>>operation;
        if(strcmp(operation,"insert")==0){
            cin>>op;
            pqueue.enQueue(op);
        }
        else if(strcmp(operation,"delete")==0)
            pqueue.deQueue();
        else{   //min
            min[mincount]=pqueue.getHead();
            mincount++;
        }
    }

    for(int i=0;i<mincount;++i)
        cout<<min[i]<<'\n';

    return 0;
}