// 4306.助教玩游戏
#include<iostream>
#include<string>
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

    void pushHead(const elemType &x){
        if(front==NULL)
            front = rear = new node(x);
        else
            front = new node(x,front);
    }
};


int main(){
    linkQueue<char> game;
    seqStack<char> tmp;     //临时存储栈

    // char c;
    // while((c=cin.get())!='\n')
    //     game.enQueue(c);

    string line;
    cin>>line;
    for(int i=0;i<line.length();++i)
        game.enQueue(line[i]);

    char prevChar,nextChar;
    bool flag=true;
    while(!game.isEmpty()){
        if(flag||tmp.isEmpty()){
            prevChar = game.deQueue();
            if(!game.isEmpty())
                nextChar = game.deQueue();
            else{   //只剩一个了
                game.pushHead(prevChar);
                if(tmp.isEmpty()||tmp.top()!=prevChar) break;
                flag=false;
                continue;   //重新考虑
            }
        }
        else{
            prevChar = tmp.pop();
            nextChar = game.deQueue();
        }
        if(prevChar=='1' && nextChar=='1')
            flag=false;   //消失 发生改变 下一次去考虑栈中元素
        else if(prevChar=='0' && nextChar=='0'){
            game.pushHead('1'); //0遇到0会变成1
            flag=false;   //发生改变 下一次去考虑栈中元素
        }
        else{   //互异
            tmp.push(prevChar);
            game.pushHead(nextChar);
            flag = true;    //下一次先处理队列
        }
    }

    //先输出栈 再输出队列
    seqStack<char> tmp_o;
    while(!tmp.isEmpty())
        tmp_o.push(tmp.pop());
    
    if(tmp_o.isEmpty()&&game.isEmpty()){
        cout<<"NULL"<<'\n';
        return 0;
    }

    while (!tmp_o.isEmpty())
        cout<<tmp_o.pop();
    
    while (!game.isEmpty())
        cout<<game.deQueue();
    
    cout<<'\n';

    return 0;
}