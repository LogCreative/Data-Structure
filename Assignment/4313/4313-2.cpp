#include<iostream>
#include<cmath>
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

struct dicint {
    int data;
    int length;             //位数

    dicint():data(-1),length(-1) {}

    dicint(int d):data(d) {
        if(d==0) length=0;          //零只能放最后，实际上
        else{ 
            length = 0;
            while(d>0) {
                ++length;
                d/=10;
            }
        }
    }

    void RefreshLength(){
        int d = data;
        if(d==0) length=0;          //零只能放最后，实际上
        else{ 
            length = 0;
            while(d>0) {
                ++length;
                d/=10;
            }
        }
    }

    // friend bool operator>(dicint di1,dicint di2) {
        // if(di1.length==0) return false;
        // if(di2.length==0) return true;
        
        // linkStack<int> s1, s2;
        // int d1 = di1.data, d2 = di2.data;
        // int base = 1;
        // for(int i = 1;i<=di1.length;++i){
        //     s1.push(d1/base % 10);
        //     base*=10;
        // }
        // base = 1;
        // for(int i = 1;i<=di2.length;++i){
        //     s2.push(d2/base % 10);
        //     base*=10;
        // }

        // while(!s1.isEmpty() && !s2.isEmpty()){
        //     int p1 = s1.pop();
        //     int p2 = s2.pop();
        //     if(p1>p2) return true;
        //     else if(p1<p2) return false;
        // }
        // return false;
    // }

    friend bool operator>(dicint di1,dicint di2) {
        string s1 = to_string(di1.data);
        string s2 = to_string(di2.data);
        string ss1 = s1+s2;
        string ss2 = s2+s1;
        return (ss1.compare(ss2)>0);
    }

};

//冒泡排序
void bubbleSort(dicint a[],int size){
    int i,j;
    dicint tmp;
    bool flag = true;

    for(i=1;i<size&&flag;++i){
        flag=false;
        for(j=0;j<size-i;++j)
            if(a[j+1]>a[j]){
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                flag = true;
            }
    }
}

int main(){
    int n;      //数据量
    cin >> n;
 
    dicint* a = new dicint[n];

    for(int i = 0;i<n;++i){
        int data;
        cin >> data;
        a[i].data = data;
        a[i].RefreshLength();
    }
    
    bubbleSort(a,n);

    for(int i=0;i<n;++i)
        cout << a[i].data;
    cout << '\n';

    return 0;
}