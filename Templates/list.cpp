#include<iostream>
using namespace std;

// 标号是从 0 开始的

template<class elemType>
class list{
public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i,const elemType &x) = 0;
    virtual void remove(int i) = 0;
    virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual ~list() { }
};

template<class elemType>
class seqList: public list<elemType>{
private:
    elemType *data;
    int currentLength;                          //currentLength 需要动态更改
    int maxSize;

    void doubleSpace(){
        elemType* tmp = data;
        maxSize*=2;
        data = new elemType[maxSize];
        for(int k=0;k<currentLength;++k)        //不要忘了复制
            data[k]=tmp[k];
        delete[] tmp;
    }
public:
    seqList(int initSize = 10){
        data = new elemType[initSize];
        currentLength = 0;
        maxSize = initSize;
    }
    
    ~seqList(){
        delete[] data;
    }

    void clear(){
        currentLength = 0;                      //之后可以复写
    }

    void insert(int i,const elemType &x){
        if(currentLength==maxSize)              // currentLength>maxSize
            doubleSpace();
        for(int k=currentLength-1;k>=i;--k)     // for(int j=currentLength;j>i;--j)
            data[k+1]=data[k];                      // data[j]=data[j-1];
        data[i]=x;
        ++currentLength;                        //不要忘记
    }

    int length() const { return currentLength; }

    void remove(int i){
        for(int k=i+1;k<currentLength;++k)
            data[k-1]=data[k];
        --currentLength;                        //不要忘记
    }

    int search(const elemType &x) const {
        int k;                                  //新C++
        for(k=0;k<currentLength && data[k]!=x;++k);         //请注意空语句分号
        if(k==currentLength) return -1;
        else return k;
    }

    void traverse() const {
        for(int k=0;k<currentLength;++k)
            cout<<data[k]<<' ';
        cout<<'\n';                             //统一不使用 endl
    }

    elemType visit(int i) const{ return data[i]; }
};

// 谁 new 谁 delete

template<class elemType>
class slinkList: public list<elemType>{
private:

    struct node
    {
        elemType data;
        node* next;

        node():next(NULL) {}                //无参数项
        node(const elemType &x,node *n=NULL):data(x),next(n) {}
        ~node() {}
    };

    node* head;
    int currentLength;              //动态改变
    
    node* move(int i) const {
        node* p = head;
        while(i-->=0) p=p->next;     //返回i--  //for(;i>=0;--i)是相同的
        return p;
    }

public:

    slinkList(){
        head = new node;
        currentLength = 0;
    }

    ~slinkList() {clear();delete head;}

    void clear(){
        node* p = head->next, *q;
        head->next = NULL;          //clear需要保留head
        while(p->next!=NULL){
            q = p->next;
            delete p;
            p = q;
        }
        currentLength = 0;          //别忘了改指标
    }

    void insert(int i,const elemType &x){
        node* p = move(i-1);
        p->next = new node(x,p->next);
        ++currentLength;
    }

    int length() const { return currentLength; }

    void remove(int i){
        node* p = move(i-1);
        node* q = p->next;
        p->next=q->next;
        delete q;
        --currentLength;
    }

    int search(const elemType &x) const {       //const要加
        node* p = head->next;
        int i=0;                //没有自然计数器，需要人为造一个

        while(p!=NULL && p->data!=x){p=p->next;++i;}
        if(p==NULL) return -1;
        else return i;
    }

    void traverse() const {
        node* p = head->next;
        while(p!=NULL){
            cout<<p->data<<' ';
            p=p->next;              //移动位置
        }
        cout<<'\n';
    }

    elemType visit(int i) const{
        return move(i)->data;
    }

};

template<class elemType>
class dlinkList: public list<elemType> {
private:
    struct node
    {
        elemType data;
        node *prev,*next;

        node():prev(NULL),next(NULL) {}
        node(const elemType &x,node* p=NULL,node* n=NULL):
            data(x),prev(p),next(n) {}
        ~node() {}
    };
    node *head,*tail;
    int currentLength;

    node* move(int i) const{
        node* p = head;
        while(i-->=0) p=p->next;
        return p;
    }
    
public:

    dlinkList() {
        head = new node;
        tail = new node;
        head->next=tail;
        tail->prev=head;
        currentLength = 0;
    }

    ~dlinkList() { clear(); delete head; delete tail; }

    void clear() {
        node *p = head->next,*q;
        head->next = tail;          //设为空表的操作
        tail->prev = head;          //提前就设好
        while(p!=tail){
            q=p->next;
            delete p;
            p = q;
        }
        currentLength = 0;
    }   

    void insert(int i,const elemType &x){
        node *p = move(i-1);                    //i也行
        node *tmp = new node(x,p,p->next);
        p->next->prev=tmp;
        p->next=tmp;
        ++currentLength;
    }

    void remove(int i){
        node *p = move(i);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --currentLength;
    }

    int length() const { return currentLength; }

    int search(const elemType &x) const {
        node* p = head->next;
        int i=0;                //没有自然计数器，需要人为造一个

        while(p!=tail && p->data!=x){p=p->next;++i;}
        if(p==tail) return -1;
        else return i;
    }

    void traverse() const {
        node* p = head->next;
        while(p!=tail){
            cout<<p->data<<' ';
            p=p->next;              //移动位置
        }
        cout<<'\n';
    }

    elemType visit(int i) const {
        return move(i)->data;
    }
};

/**************测试函数****************/

void seqListTest() {
    seqList<int> sl;
    for(int k=0;k<15;++k)
        sl.insert(k,k);
    cout<<sl.length()<<'\n';
    int x=10;
    cout<<sl.search(x)<<'\n';       // 引用规则：必须是变量
    sl.traverse();
    cout<<sl.visit(10)<<'\n';
    sl.remove(10);
}


void slinkListTest(){
    slinkList<int> sl;         //请不要忘了加模板参数
    for(int k=0;k<15;++k)
        sl.insert(k,k);
    cout<<sl.length()<<'\n';
    int x=10;
    cout<<sl.search(x)<<'\n';       // 引用规则：必须是变量
    sl.traverse();
    cout<<sl.visit(10)<<'\n';
    sl.remove(10);
}

void dlinkListTest(){
    dlinkList<int> sl;         //请不要忘了加模板参数
    for(int k=0;k<15;++k)
        sl.insert(k,k);
    cout<<sl.length()<<'\n';
    int x=10;
    cout<<sl.search(x)<<'\n';       // 引用规则：必须是变量
    sl.traverse();
    cout<<sl.visit(10)<<'\n';
    sl.remove(10);
}

int main(){

    //seqListTest();

    //slinkListTest();

    //dlinkListTest();

    return 0;
}

// 应用：LonglongInt 类