// 1348.cpp: 舞会排队

//男生和女生分别排队等待入场
//每一首新曲开始，舞池中的同学都会离开场地，正在排队的同学中男生女生从队头进入相同数量，并且尽可能多的同学搭配成舞伴一起入场。
//每一位同学只跳舞一首曲子的长度，每首曲子长度不同。
//到最后一首曲子，还未跳过舞的同学们会都进入场地一起跳舞。

// 排序问题

// 这次不再插入时判断，而是插入完排序

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

// a list queue simple one.
// 牺牲一个元素 front
template<class elemType>
class seqQueue:public queue<elemType>{
    elemType *elem;
    int maxsize;
    int front,rear;
    int max_len;

    void doubleSpace(){
        elemType* tmp=elem;
        elem=new elemType[2*maxsize];
        for(int i=front;i<=rear;++i)
            elem[i]=tmp[i];
        maxsize*=2;
        delete[] tmp;
    }

public:
    int total_t;
    seqQueue(int size=10){
        elem=new elemType[size];
        maxsize=size;
        front= rear = 0;
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
        //just enQueue
        ++max_len;

        //full
        if(rear+1==maxsize)
            doubleSpace();
        
        //insert
        ++rear;
        elem[rear]=x;
    }
    elemType deQueue(){
        ++front;
        return elem[front];
    }
    void sort(){
        // Shell sort, nonegative
        // Time complexity < O(n^2)
        
        int len = rear;
        elemType* arr=elem+1;//1~rear
        for(int gap = len / 2; gap > 0; gap = gap / 2) {
            for(int i = gap; i < len; i++) {
                int j = i;
                elemType current = arr[i];
                while(j - gap >= 0 && current < arr[j - gap]) {
                    arr[j] = arr[j - gap];
                    j = j - gap;
                }
                arr[j] = current;
            }
        }

    }

    elemType getHead() const {
        elemType tmp=elem[front+1];
        return tmp;
    }
    double get_avg_t() const{
        if(max_len==0)
            return 0;
        return 1.00*total_t/max_len;
    }
    void disp() const{
        for(int i=front+1;i<=rear;++i)
            cout<<elem[i]<<" ";
        cout<<'\n';
    }
};

void simulation(int* l,int N,seqQueue<int> &male, seqQueue<int> &female){
    //before simulation, sort needed.

    male.sort();
    female.sort();

    int currentTime = 0;
    int m_t,f_t;
    for(int i=0;i<N-1;++i){
        while(!male.isEmpty()&&!female.isEmpty()){
            m_t=currentTime-male.getHead();
            f_t=currentTime-female.getHead();
            if(m_t>=0&&f_t>=0){
                male.total_t+=currentTime-male.deQueue();
                female.total_t+=currentTime-female.deQueue();
            }
            else
                break;
        }
        currentTime+=l[i];
    }

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
        if(s==1){
            male.enQueue(t);
        }
        else if(s==2){
            female.enQueue(t);
        }
        //(s==1)?male.enQueue(t):female.enQueue(t);
    }

    //male.disp();
    //female.disp();

    simulation(l,N,male,female);

    cout.setf(ios::fixed);

    cout<<fixed<<setprecision(2)<<male.get_avg_t()<<" "<<female.get_avg_t()<<endl;
    
    cout.unsetf(ios::fixed);

    delete[] l;
    return 0;
}