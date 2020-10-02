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

    int absmin(int x) {
        int minmaxabs=-1,maxminabs=-1;
        BinaryNode *p=root;
        while(p!=NULL){
            if(p->data.key>x&&minmaxabs!=-1) break;
            if(p->data.key<=x) {
                minmaxabs = p->data.key; p=p->right; 
            }
            else p = p->left;        //找小的
        }
        while(p!=NULL){
            if(p->data.key<x&&maxminabs!=-1) break;
            if(p->data.key>=x){
                maxminabs = p->data.key; p=p->left; 
            }
            else p = p->right;
        }
        if(minmaxabs==-1) return maxminabs - x;
        if(maxminabs==-1) return x- minmaxabs;
        return min(maxminabs - x,x- minmaxabs);
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