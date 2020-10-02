// 1216 Heap

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

    void buildHeap(){
        for(int i=currentSize;i>=1;--i)
            percolateDown(i);
    }

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

    int find(const Type &x) const{
        int tmp=0;    //遍历
        for(int i=1;i<=currentSize;++i){
            if(x<array[i]){
                if(tmp==0)
                    tmp=i;
                else
                    if(array[i]<array[tmp])
                        tmp=i;  //更新tmp
            }
        }
                
        return tmp;
    }

    void decrease(int hole,const Type &x){
        array[hole]-=x;
        //重排
        buildHeap();
    }
    
    Type getHead() const { return array[1]; }

};

int main() {
    int M;  //总操作数
    cin>>M;

    char operation[9];
    int op,op2;
    int* find=new int[M];
    int findcount=0;

    priorityQueue<int> pqueue;

    for(int i=0;i<M;++i){
        cin>>operation;
        if(strcmp(operation,"insert")==0){
            cin>>op;
            pqueue.enQueue(op);
        }
        else if(strcmp(operation,"find")==0){
            cin>>op;
            find[findcount]=pqueue.find(op);
            findcount++;
        }
        else {   //decrease
            cin>>op>>op2;
            pqueue.decrease(op,op2);
        }
    }

    for(int i=0;i<findcount;++i)
        cout<<find[i]<<'\n';

    return 0;
}