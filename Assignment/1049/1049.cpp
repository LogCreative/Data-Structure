// 1049 Train Allocation

#include<iostream>
using namespace std;

template<class elemType>
class stack {
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const elemType& x) = 0;       // 修改
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual ~stack() {}
};

template<class elemType>
class seqStack : public stack<elemType> {
private:
	elemType* elem;
	int top_p;
	int maxSize;

public:
	seqStack(int initSize = 10) {
		elem = new elemType[initSize];
		maxSize = initSize;
		top_p = -1;
	}
	~seqStack() {
		delete[] elem;
	}
	bool isEmpty() const {
		return top_p == -1;
	}
	bool push(const elemType& x) {
		if (top_p == maxSize - 1)
            return false;   //操作失败
		elem[++top_p] = x;
        return true;        //操作正常
	}
	elemType pop() {
		return elem[top_p--];
	}
	elemType top() const {
		return elem[top_p];
	}
};

bool allocation(int N,int M,int *order){
    seqStack<int> alloc_st(M);  //调度栈
    int front=0;
    while (front<N){
        if (front==*order){
            ++front;
            ++order;
            continue;
        }
        else{ 
            if (!alloc_st.isEmpty()){
                //Check Stack
                if (alloc_st.top()==*order){
                    alloc_st.pop();
                    ++order;
                    continue;
                }
            }
            if (!alloc_st.push(front))
               return false;       //错误 万策尽
            ++front;
        }
    }
    // 栈
    while(!alloc_st.isEmpty()){     //非空
        if(alloc_st.pop()==*order)      //You can only pop now.
            ++order;
        else
            return false;
    }
    return true;
}


int main(){
    int T;      // 本测试数据有多少个独立的测试点
    cin >> T;

    int N;  //表示开来的火车数量
    int M;  //调度站最多可容纳的火车数量
    int* order;     //驶离顺序
    //int* ptr;
    bool* Result=new bool[T];   //结果

    for(int i=0;i<T;++i){
        cin>>N>>M;
        order=new int[N];
        for (int j=0;j<N;++j){
            cin>>order[j];  //如果效率低 就改为指针
        }
        Result[i]=allocation(N,M,order);
        delete[] order;     //删除
    }

    for(int i=0;i<T;++i)
        cout<<(Result[i]==true?"YES\n":"NO\n");

    delete[] Result;

    return 0;
}