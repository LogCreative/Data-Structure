//4036. 剁手游戏
#include<iostream>
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

    node *front, *rear;
    
public:

    linkQueue() { front = rear = NULL; }

    ~linkQueue() {
        clear();
    }

    void clear(){
        node*tmp;
        while(front!=NULL){
            tmp = front;
            front = front->next;
            delete tmp;
        }
        front = rear = NULL;
    }

    elemType deQueue() {
        node* tmp = front;
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

    bool simulation(int a,int b){
    bool round = true;  //true - NanaBa,false - LuobeiHu
        while(!isEmpty()){
            if(round){
                if(a>getHead()){
                    a-=deQueue();
                } else {
                    return false;
                }
            }
        }
    }
};



int main() {
    int T;  // 数据开始首先输入数据组数T(T<=10)
    cin >> T;

    long n;  // 现在有n(n <= 10^6)件商品依次摆在他们的面前
    long a;  // 一开始NanaBa有a元钱
    long b;  // 一开始LuobeiHu有b元钱

    linkQueue<int> c;
    int c_tmp;
    bool* result=new bool[T];

    for(int i=0;i<T;++i){
        cin>>n>>a>>b;
        
        for(int j=0;j<n;++j){
            cin>>c_tmp;
            c.enQueue(c_tmp);
        }

        result[i] = c.simulation(a,b);
    }



}