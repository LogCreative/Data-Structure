//2111. 最小差值
#include<iostream>
using namespace std;

// 集合的元素类型
template<class KEY, class OTHER>
struct SET {
    KEY key;        //关键字值
    OTHER other;    //其他信息
};

// 动态查找表的抽象类
template<class KEY, class OTHER>
class dynamicSearchTable {
public:
    virtual SET<KEY,OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY,OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable() {}
};

template<class KEY, class OTHER>
class BinarySearchTree: public dynamicSearchTable<KEY,OTHER> {
private:
    struct BinaryNode
    {
        SET<KEY,OTHER> data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET<KEY,OTHER> & thedata, BinaryNode *lt=NULL,
            BinaryNode *rt=NULL): data(thedata),left(lt),right(rt) { }
    };
    BinaryNode *root;
    
    void insert(const SET<KEY,OTHER> &x, BinaryNode *&t) {
        if (t==NULL)
            t = new BinaryNode(x,NULL,NULL);
        else if (x.key<t->data.key)
            insert(x,t->left);
        else if (t->data.key<x.key)
            insert(x,t->right);
    }

    void remove(const KEY &x, BinaryNode *&t) {
        if (t==NULL) return ;
        if (x<t->data.key) remove(x,t->left);
        else if (t->data.key<x) remove(x,t->right);
        else if (t->left!=NULL&&t->right!=NULL){
            BinaryNode *tmp = t->right;
            while(tmp->left!=NULL) tmp=tmp->left;
            t->data = tmp->data;
            remove(t->data.key,t->right);
        }
        else {
            BinaryNode *oldNode = t;
            t = (t->left!=NULL)?t->left:t->right;
            delete oldNode;
        }
        
    }

    SET<KEY,OTHER> *find(const KEY &x, BinaryNode *t) const {
        if (t==NULL||t->data.key==x)
            return (SET<KEY,OTHER>*) t;
        if (x<t->data.key)
            return find(x,t->left);
        else
            return find(x,t->right);
    }

    void makeEmpty(BinaryNode *t) {
        if(t==NULL) return ;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    
    
public:
    BinarySearchTree() {
        root = NULL;
    }
    ~BinarySearchTree() {
        makeEmpty(root);
    }

    SET<KEY,OTHER> *find(const KEY &x) const {
        return find(x,root);
    }

    void insert(const SET<KEY,OTHER> &x) {
        insert(x,root);
    }

    void remove(const KEY &x) {
        remove(x,root);
    }
    
    BinaryNode* maxnode(BinaryNode* t1,BinaryNode *t2){
        if(t1==NULL) return t2;
        if(t2==NULL) return t1;
        return (t1->data.key>t2->data.key)?t1:t2;
    }

    BinaryNode* minnode(BinaryNode* t1,BinaryNode *t2){
        if(t1==NULL) return t2;
        if(t2==NULL) return t1;
        return (t1->data.key>t2->data.key)?t2:t1;
    }

    BinaryNode* minmaxnode(int x, BinaryNode *t){
        //现寻找比x小于等于的最大的，
        if(t->data.key<=x)
            minmax = maxnode(minmax,t);   //刷新
        if(t->left!=NULL)
            minmax = minmaxnode(x,t->left);
        if(t->right!=NULL && t->right->data.key<=x) //一旦右树大了，一定不行了
            minmax = minmaxnode(x,t->right);
        return minmax;
    }

    BinaryNode* maxminnode(int x, BinaryNode *t){
        if(t->data.key>x)
            maxmin = minnode(maxmin,t);   //刷新
        if(t->left!=NULL && t->data.key>x)
            maxmin = maxminnode(x,t->left);
        if(t->right!=NULL)
            maxmin = maxminnode(x,t->right);
        return maxmin;
    }

    BinaryNode* minmax, *maxmin;

    int absmin(int x) {
        if(root==NULL) return -1;   //异常
        minmax = maxmin = NULL;
        minmax = minmaxnode(x,root);
        maxmin = maxminnode(x,root);
        if(minmax==NULL) return (maxmin->data.key - x);
        if(maxmin==NULL) return (x - minmax->data.key);
        return (maxmin->data.key - x>x - minmax->data.key)?x - minmax->data.key:maxmin->data.key - x;
    }

};


int main() {
    int M;
    cin >> M;

    BinarySearchTree<int,char> BST;

    int op;
    int x;
    for (int i=0;i<M;++i){
        cin >> op >> x;
        switch (op)
        {
        case 0: cout<<BST.absmin(x)<<'\n'; break;  //询问要求的最小值
        case 1: BST.insert((SET<int,char>){x,'\0'}); break;  //插入元素x
        case 2: BST.remove(x); break;  //删除元素x
        }
    }

    return 0;
}