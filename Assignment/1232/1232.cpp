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

    bool throughPath(int &currentNode, int &nextNode, int levelOfCur, int commonParent, int dir){
        switch(dir){
            case 0:         //左上
                nextNode = currentNode - levelOfCur;
                if(nextNode>levelEnd[levelOfCur-2])
                    break;
                else return false;
            case 1:         //右上
                nextNode = currentNode - levelOfCur + 1;
                if(nextNode<=levelEnd[levelOfCur-1])
                    break;  
                else return false;
            case 2:         //左下
                nextNode = currentNode + levelOfCur;
                if(levelOfCur<levelLineNum)
                    break;  
                else return false;
            case 3:         //右下
                nextNode = currentNode + levelOfCur + 1;
                if(levelOfCur<levelLineNum)
                    break;  
                else return false;
        }
        
        if(Find(nextNode)==commonParent){
            cout << nextNode << ' ';
            currentNode = nextNode;
            return true;
        } else return false;
    }

    bool isThrough() {
        int commonParent = Find(Start);
        int currentNode = Start;
        int nextNode;
        if(commonParent==Find(End)){
            cout << Start << ' ';
            // When it is through, output the result.

            // The lowest Order of Path.
            // The discontinuousity of the same level provides 
            // the only path by getting to the common parent 
            // by going up and down and best left to 
            // ensure the path is correct.
            int levelOfCur;
            while(currentNode!=End){
                levelOfCur = getLevel(currentNode);
                if(levelOfCur<=getLevel(commonParent)){
                    //Upper First
                    for(int i=0;i<=3;++i)
                        if(throughPath(currentNode,nextNode,levelOfCur,commonParent,i))
                            break;
                } else{
                    //Down First
                    int proi[4] ={2,3,0,1};
                    for(int i=0;i<=3;++i)
                        if(throughPath(currentNode,nextNode,levelOfCur,commonParent,proi[i]))
                            break;
                }
            }

            return true;
        } else return false;
    }

    void breakWall(int node, int dir){

        int levelOfParent = getLevel(node);
        int ToParent;

        switch(dir){
            case 0:         //左上
                ToParent = node - levelOfParent;
                if(ToParent>levelEnd[levelOfParent-2])
                    Union(levelOfParent,ToParent);
                break;  
            case 1:         //右上
                ToParent = node - levelOfParent + 1;
                if(ToParent<=levelEnd[levelOfParent-1])
                    Union(levelOfParent,ToParent);
                break;  
            case 2:         //左下
                ToParent = node + levelOfParent;
                if(levelOfParent<levelLineNum)
                    Union(levelOfParent,ToParent);
                break;
            case 3:         //右下
                ToParent = node + levelOfParent + 1;
                if(levelOfParent<levelLineNum)
                    Union(levelOfParent,ToParent);
                break;
        }
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