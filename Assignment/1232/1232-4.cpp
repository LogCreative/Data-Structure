// 1232. maze
// Triangle Maze & non-iteration Find
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

    // bool isExist(const elemType x){
    //     node *p = front;
    //     while(p!=NULL){
    //         if(p->data==x) return true;
    //         p = p->next;
    //     }
    //     return false;
    // }

};

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

class TriMaze {
private:
    int levelLineNum;
    int* levelEnd;
    int* Parent;
    int Start, End;

    int getLevel(int node){
        int i;
        for(i = 1; i <= levelLineNum; ++i)
            if(node>levelEnd[i-1] && node<=levelEnd[i])
                break;
        return i;
    }

    int Find(int x){
        // We break the wall only in different layers.
        linkQueue<int> spque;
        while(true){
            if(Parent[x]<0)
                break;
            spque.enQueue(x);
            x = Parent[x];
        }

        while(!spque.isEmpty())
            Parent[spque.deQueue()] = x;

        return x;
    }

    void Union(int root1, int root2){
        // Find the root to Union.
        root1 = Find(root1);
        root2 = Find(root2);

        if(root1==root2) return ;
        if(Parent[root1]>Parent[root2]){
            Parent[root2] += Parent[root1];
            Parent[root1] = root2;
        } else {
            Parent[root1] += Parent[root2];
            Parent[root2] = root1;
        }

    }

    bool isAvaliable(int currentNode, int &nextNode, int dir){
        int levelOfCur = getLevel(currentNode);
        switch(dir){
            case 0:         //左上
                nextNode = currentNode - levelOfCur;
                if(nextNode>levelEnd[levelOfCur-2])
                    return true;
                else return false;
            case 1:         //右上
                nextNode = currentNode - levelOfCur + 1;
                if(nextNode<=levelEnd[levelOfCur-1])
                    return true;  
                else return false;
            case 2:         //左下
                nextNode = currentNode + levelOfCur;
                if(levelOfCur<levelLineNum)
                    return true;  
                else return false;
            case 3:         //右下
                nextNode = currentNode + levelOfCur + 1;
                if(levelOfCur<levelLineNum)
                    return true;  
                else return false;
        }
    }

    void printPath(int start, int end, int prev[]){
        if(start == end){
            cout << start;
            return ;
        }
        printPath(start,prev[end],prev);
        cout << ' ' << end;
    }

public:
    TriMaze(int N,int A,int B){
        levelLineNum = N;

        // Initialize the Level End.
        levelEnd = new int[N+1];
        levelEnd[0] = 0;            //Non-exists
        for(int i = 1; i <= N; ++i)
            levelEnd[i] = levelEnd[i-1] + i;
        
        
        // Initialize the Parent Array.
        Parent = new int[levelEnd[N] + 1];
        for(int i = 1; i <= levelEnd[N]; ++i)
            Parent[i] = -1;
        
        Start = A;
        End = B;
    }

    ~TriMaze(){
        delete[] levelEnd;
        delete[] Parent;
    }

    void OutputPath(){
        linkStack<int> path;
        bool* isVisited = new bool[levelEnd[levelLineNum]+1];
        for(int i = 1;i<=levelEnd[levelLineNum];++i)
            isVisited[i] = false;
        isVisited[Start] = true;
        path.push(Start);
        int nextNode;
        bool flag;

        while(path.top()!=End){
            flag = false;
            for(int i = 0; i<4; ++i){
                if(isAvaliable(path.top(),nextNode,i)&&!isVisited[nextNode]){
                    isVisited[nextNode] = true;
                    path.push(nextNode);
                    flag = true;
                    break;
                }
            }
            if(!flag)
                path.pop();     //退回去
        }

        linkStack<int> antiPath;
        while(!path.isEmpty())
            antiPath.push(path.pop());

        while(!antiPath.isEmpty())
            cout<<antiPath.pop()<<' ';
        cout<<'\n';
    }

    bool isThrough() {
        int commonParent = Find(Start);
        if(commonParent==Find(End)){
            // Output The Path.
            OutputPath();
            return true;
        } else return false;
    }

    void breakWall(int node, int dir){
        int ToParent;
        if(isAvaliable(node,ToParent,dir))
            Union(node,ToParent);
    }
    
};

int main(){
    int N;          //迷宫行数
    cin >> N;

    int A;          //迷宫入口
    int B;          //迷宫出口
    cin >> A >> B;

    TriMaze tm(N,A,B);

    int P;          //节点编号
    int Q;          //墙的方向
    while(!tm.isThrough()){
        cin >> P >> Q;
        tm.breakWall(P,Q);
    }

    return 0;
}