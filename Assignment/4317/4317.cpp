#include<iostream>
#include<cmath>
using namespace std;

//在集合中找出两个数a,b，使得他们相加之和等于m， 并返回这两个数在集合A 中的下标值，如果有多个则返回a和b差值的绝对值最大的，即|a-b|最大的a和b的下标值 。现假定一定存在这样的a和b使得a+b=m。

// 应该用哈希https://leetcode-cn.com/problems/two-sum/solution/liang-shu-zhi-he-by-leetcode-2/

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
        elemType x = tmp->data;
        front = front->next;
        if (front==NULL) rear = NULL;
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

};


struct goodPair{
    int i;
    int j;
    int ai;
    int aj;

    goodPair(int eye,int jay,int aeye, int ajay):i(eye),j(jay),ai(aeye),aj(ajay) {}
};

int main(){
    int n;
    cin >> n;

    int* A = new int[n];
    for(int i = 0; i<n; ++i)
        cin >> A[i];
    
    int m;
    cin >> m;

    linkQueue<goodPair> pq; 

    for(int i = 0; i<n; ++i){
        for(int j = i+1; j<n; ++j){
            if(A[i]+A[j]==m)
                pq.enQueue(goodPair(i,j,A[i],A[j]));
        }
    }

    int mini=-1, minj=-1, minai = -1, minaj = -1;
    while(!pq.isEmpty()){
        goodPair cur = pq.deQueue();
        if(abs(cur.ai - cur.aj)>abs(minai - minaj)||
        (abs(cur.ai - cur.aj)==abs(minai - minaj)&&abs(cur.i-cur.j)>abs(mini-minj))||
        (abs(cur.ai - cur.aj)==abs(minai - minaj)&&abs(cur.i-cur.j)==abs(mini-minj))&&cur.i<mini){
            mini = cur.i;
            minj = cur.j;
            minai = cur.ai;
            minaj = cur.aj;
        }
    }

    cout << mini << ' ' << minj;

    return 0;
}