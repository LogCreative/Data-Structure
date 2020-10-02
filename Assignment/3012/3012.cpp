// 3012. Stack Overflow?

#include<iostream>
using namespace std;

template<class elemType>
class stack{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};

//int 顺序栈
class seqStack: public stack<int>{
private:
    int *elem;
    int top_p;
    int maxSize;
    void doubleSpace(){
        int *tmp=elem;
        elem=new int[2*maxSize];
        for (int i=0;i<maxSize;++i){
            elem[i]=tmp[i];
        }
        maxSize*=2;
        delete[] tmp;
    }
public:
    seqStack(int initSize=10){
        elem=new int[initSize];
        maxSize=initSize;
        top_p=-1;
    }
    ~seqStack(){
        delete[] elem;
    }
    bool isEmpty() const {
        return top_p==-1;
    }
    void push(const int &x){
        if (top_p==maxSize-1)
            doubleSpace();
        elem[++top_p]=x;
    }
    int pop(){
        return elem[top_p--];
    }
    int top() const {
        return elem[top_p];
    }

    //需要封装在类中以获得类的访问
    int stack_op(int op,int num){
        switch(op){
            case 1:
                push(num);  //压入栈
                return 0; //"OK";
                break;
            case 2:
                if (isEmpty())  //空栈
                    return -1;//"ERROR";
                else{
                    if (pop()==num) //出栈并比较
                        return 1;//"YES";
                    else
                    {
                        return 2;//"NO";
                    }
                }
                break;
            default:
                break;
        }
    }
};


int main(){
    int i, n;
    int op, num;
    cin>>n;

    //创建一个栈
    seqStack* st=new seqStack();

    //创建输出
    int* output=new int[n];

    for (i=0;i<n;++i){
        cin>>op>>num;
        output[i]=st->stack_op(op,num);
    }

    for (i=0;i<n;++i){
        switch(output[i]){
            case 0:
                cout<<"OK"<<endl;break;
            case -1:
                cout<<"ERROR"<<endl;break;
            case 1:
                cout<<"YES"<<endl;break;
            case 2:
                cout<<"NO"<<endl;break;
            default:
                break;
        }
    }

    delete st;
    delete[] output;

    //system("pause");
    return 0;
}

