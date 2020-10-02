// 1348.cpp: 舞会排队
 
//男生和女生分别排队等待入场
//每一首新曲开始，舞池中的同学都会离开场地，正在排队的同学中男生女生从队头进入相同数量，并且尽可能多的同学搭配成舞伴一起入场。
//每一位同学只跳舞一首曲子的长度，每首曲子长度不同。
//到最后一首曲子，还未跳过舞的同学们会都进入场地一起跳舞。
 
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
 
template<class elemType>
class linkQueue{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x,node *N=NULL){
            data=x;
            next=N;
        }
        node():next(NULL){}
        ~node() {}
    };
    node *front,*rear;
    int len;
public:
    int total_t;
    linkQueue(){
        front=new node();
        rear=new node();
        front->next=rear;
        len=0;total_t=0;}
    ~linkQueue(){
        //析构
        node * pos=front;
        while(pos!=rear){
            node*tmp=pos;
            pos=pos->next;
            delete tmp;
        }
        delete pos;
    }
    bool isEmpty() const {return front->next==rear;}
    void enQueue(const elemType &x){
        //ordered enQueue
        ++len;
        
        node*pos=front;
        if(!isEmpty()){
        //non-trival, find the pos.    
            while(pos->next->data<=x){
                pos=pos->next;
                if(pos->next==rear)
                    break;
            }
        }
        
        //insert after pos
        pos->next=new node(x,pos->next);
        
    }
    elemType deQueue(){
        // You can not deQueue if it is empty.
        node*tmp=front->next;
        elemType value=front->next->data;
        front->next=front->next->next;
        delete tmp;
        return value;
    }
    elemType getHead() const {return front->next->data;}
    int length() const {return len;}
    double get_avg_t() const{
        return 1.00*total_t/len;
    }
    
};
 
void simulation(int* l,int N,linkQueue<int> &male, linkQueue<int> &female){
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

    // while(!male.isEmpty()){
    //     m_t=currentTime-male.deQueue();
    //     if(m_t>=0)
    //         male.total_t+=m_t;
    //     else
    //         break;
    // }   
    // while(!female.isEmpty()){
    //     f_t=currentTime-female.deQueue();
    //     if(f_t>=0)
    //         female.total_t+=f_t;
    //     else
    //         break;   
    // }
 
}
 
int main(){
    int N;  //N首曲目
    cin>>N; 
    int *l=new int[N];
    for(int i=0;i<N;++i)
        cin>>l[i];      //每一首曲子的长度li
    int M;  //整个过程将有M个人进入队列
    cin>>M;
    
    linkQueue<int> male, female;
    for(int i=0;i<M;++i){
        int s,t;
        cin>>s>>t;
        (s==1)?male.enQueue(t):female.enQueue(t);
    }
 
    simulation(l,N,male,female);
 
    cout.setf(ios::fixed);
 
    cout<<fixed<<setprecision(2)<<male.get_avg_t()<<" "<<female.get_avg_t()<<'\n';
 
    delete[] l;
    return 0;
}