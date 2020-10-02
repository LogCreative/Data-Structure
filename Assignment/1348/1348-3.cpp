// 1348.cpp: 舞会排队

//男生和女生分别排队等待入场
//每一首新曲开始，舞池中的同学都会离开场地，正在排队的同学中男生女生从队头进入相同数量，并且尽可能多的同学搭配成舞伴一起入场。
//每一位同学只跳舞一首曲子的长度，每首曲子长度不同。
//到最后一首曲子，还未跳过舞的同学们会都进入场地一起跳舞。

// Wrong Solution

#include<iostream>
#include<iomanip>
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

// a list queue
template<class elemType>
class seqQueue:public queue<elemType>{
    elemType *elem;
    int maxsize;
    int front,rear;
    int len;
    int max_len;

    void doubleSpace(){
        elemType *tmp=elem;
        elem = new elemType[2*maxsize];
        for(int i=1;i<maxsize;++i)
            elem[i]=tmp[(front+i)%maxsize];
        front =0;
        rear=maxsize-1;
        maxsize*=2;
        delete[] tmp;
    }

public:
    int total_t;
    seqQueue(int size=10){
        elem=new elemType[size];
        maxsize=size;
        front = rear = 0;
        len = 0;
        total_t=0;
        max_len=0;
    }
    ~seqQueue() {
        delete[] elem;
    }
    bool isEmpty() const{
        return front==rear;
    }
    void enQueue(const elemType &x){
        // ordered enQueue

        // Use binary finding method

        ++len;
        ++max_len;

        if((rear+1)%maxsize==front)
            doubleSpace();
        
        if(isEmpty()){
            rear=(rear+1)%maxsize;
            elem[rear]=x;
            return ;
        }

        //int insert; //插入位置

        int low=front+1;
        int high=rear;
        int mid;
        elemType target=x;
        int result;

        while(true){
            if(low>high){
                result=-1;  //should not happen
                break;
            }
            if(low==high||low==high-1){
                result=high;
                break;
            }
            mid=(low+high)/2;
            if (elem[mid%maxsize]>target)
                high=mid;
            else if(elem[mid%maxsize]<target)
                low=mid;
            else{
                result=mid;
                break;
            }
        }

        //insert = result;
        //移动
        for(int i=rear;i>result;--i)
            elem[(i+1)%maxsize]=elem[i%maxsize];
        elem[result%maxsize]=x;

        rear=(rear+1)%maxsize;
    }
    elemType deQueue(){
        --len;

        front=front+1;
        return elem[front%maxsize];
    }
    elemType getHead() const {
        return elem[(front+1)%maxsize];
    }
    int length() const{
        return len;
    }
    double get_avg_t() const{
        return 1.00*total_t/max_len;
    }
};

void simulation(int* l,int N,seqQueue<int> &male, seqQueue<int> &female){
    int currentTime=0;  //当前时间
    //配对问询
    int m_t,f_t;
    for(int i=0;i<N-1;++i){
        //先问询
        while(!male.isEmpty() && !female.isEmpty()){
            m_t=male.getHead();
            f_t=female.getHead();
            if(m_t<=currentTime&&f_t<=currentTime){
                //男女嘉宾牵手成功，计入等待时间
                male.total_t+=currentTime-male.deQueue();
                female.total_t+=currentTime-female.deQueue();
            }
            else
                break;
        }
        currentTime+=l[i];
    }
    //最后一轮问询
    while(!male.isEmpty())
        male.total_t+=currentTime-male.deQueue();
    while(!female.isEmpty())
        female.total_t+=currentTime-female.deQueue();
}

int main(){
    int N;  //N首曲目
    cin>>N; 
    int *l=new int[N];
    for(int i=0;i<N;++i)
        cin>>l[i];      //每一首曲子的长度li
    int M;  //整个过程将有M个人进入队列
    cin>>M;
    
    seqQueue<int> male, female;
    for(int i=0;i<M;++i){
        int s,t;
        cin>>s>>t;
        (s==1)?male.enQueue(t):female.enQueue(t);
    }

    cout.setf(ios::fixed);

    cout<<fixed<<setprecision(2)<<male.get_avg_t()<<" "<<female.get_avg_t()<<'\n';

    delete[] l;
    return 0;
}