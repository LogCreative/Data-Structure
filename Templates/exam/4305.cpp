//4305. 车站
#include<iostream>
using namespace std;

#define MAXLINE 100001

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
        front=front->next;
        elemType x = tmp->data;
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

    long getT(long index){
        node *ptr =front;
        for(int j=0;j<index;++j){
            ptr=ptr->next;
        }
        return ptr->data.t;
    }

    long statistics(long iin){
        //t[i]-t[p]<86400
        bool*sta = new bool[MAXLINE];
        long find;

        for(long i=0;i<MAXLINE;++i)
            sta[i]=false;     //初始化
        
        node*ptr;
        
        long ti = getT(iin);
        for(ptr=front;ptr!=NULL;ptr=ptr->next){
            if(ti - ptr->data.t < 86400&&ti - ptr->data.t >= 0){
                for(long j=0;j<ptr->data.k;++j){    //遍历
                    find = *(ptr->data.x + j);
                    if(!sta[find])
                        sta[find] = true;
                }
            }
        }

        long count=0;
        for(int l=0;l<MAXLINE;++l){
            if(sta[l])
                ++count;
        }

        return count;
    }

};

struct train{
    long t;
    long k;
    long* x;
};

int main(){
    long n;
    cin>>n;

    linkQueue<train> trq;

    long t;  //表示这辆车的到达时间
    long k;  //车上的旅客数量
    long*x;  //表示出发地
    long*output = new long[n];
    train tr;
    for(long i = 0;i<n;++i){
        cin>>t>>k;
        x=new long[k];
        for(long j=0;j<k;++j){
            cin>>x[j];
        }
        //包含该火车
        tr.t = t;
        tr.k = k;
        tr.x = x;
        trq.enQueue(tr);
    }

    for(long i=0;i<n;++i){
        output[i] = trq.statistics(i);
    }

    for(long i=0;i<n;++i)
        cout<<output[i]<<'\n';

    return 0;
}