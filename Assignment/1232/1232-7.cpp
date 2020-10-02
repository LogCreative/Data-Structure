// 1232. maze
// Triangle Maze & non-iteration Find

// 无能为力
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

    int currentLength;
    
public:
    node *front,*rear;

    linkQueue() { front = rear = NULL; currentLength = 0;}

    //复制构造函数
    linkQueue(const linkQueue<elemType> &lq){
        front = rear = NULL; currentLength = 0;
        node *p = lq.front;
        while(p!=NULL){
            enQueue(p->data);
            p = p->next;
        }
    }

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
        --currentLength;
        return x;
    }

    void enQueue(const elemType &x){
        if(rear==NULL)
            front = rear = new node(x);
        else
            rear = rear->next = new node(x);     // rear->next 先被赋值，然后再赋给 rear 上

        ++currentLength;
    }

    elemType getHead() const { return front->data; }

    bool isEmpty() const { return front==NULL; }        //注意不是两者相等

    bool isExist(const elemType x){
        node *p = front;
        while(p!=NULL){
            if(p->data==x) return true;
            p = p->next;
        }
        return false;
    }

    int getLength() const {return currentLength;}

    //字典序友元函数
    friend bool operator<(const linkQueue<elemType> q1,const linkQueue<elemType> q2) {
        if(q1.getLength()<q2.getLength()) return true;
        else if(q1.getLength()>q2.getLength()) return false;
        else {  //长度相同
            node *p1 = q1.front;
            node *p2 = q2.front;
            while(p1!=NULL){
                if(p1->data<p2->data) return true;
                else if(p1->data>p2->data) return false;
                else{
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }
            return false;
        }
    }

    
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
        return false;
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

    // 最短路径 + 字典序最小

    // 所有可选路径
    linkQueue<linkQueue<int>> paths;

    //搜索
    void SearchPath(int current,linkQueue<int> cp){
        if(current==End){paths.enQueue(cp); return ;}
        int nextNode;
        for(int i=0;i<4;++i){
            if(isAvaliable(current,nextNode,i) &&
               !cp.isExist(nextNode) && Find(current)==Find(nextNode)){
                   linkQueue<int> cpp = cp;
                   cpp.enQueue(nextNode);
                   SearchPath(nextNode,cpp);
            }
        }
    }

    void OutputPath(){
       //暴力贪婪搜索

        linkQueue<int> begq;
        begq.enQueue(Start);
        //Start from Start.
        SearchPath(Start,begq);

        //Search complete
        linkQueue<int> minq = paths.deQueue();
        while(!paths.isEmpty()){
            linkQueue<int> comp = paths.deQueue();
            if(comp<minq){
                minq = comp;
            }
        }
        while(!minq.isEmpty()){
            cout<<minq.deQueue()<<' ';
        }
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