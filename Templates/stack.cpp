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

void seqStackTest() {
    seqStack<int> ss;
    for(int i=0;i<15;++i)
        ss.push(i);
    ss.pop();
    cout<<(ss.isEmpty()?"YES":"NO")<<'\n';
}

void linkStackTest() {
    linkStack<int> ss;
    for(int i=0;i<15;++i)
        ss.push(i);
    ss.pop();
    cout<<(ss.isEmpty()?"YES":"NO")<<'\n';
}

int main(){
    linkStackTest();

    return 0;
}

//应用：括号配对