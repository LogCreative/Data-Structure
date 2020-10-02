//2111. 最小差值
#include<iostream>
#include<cmath>
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
    KEY search;
    BinaryNode *prev;
    BinaryNode *ans;
    
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

    void DFS(BinaryNode* r){
        if(r->left!=NULL){
            DFS(r->left);
            prev = r->left;
        }

        if(r->data.key>=search){
            ans = r;
            return ;
        } else {
            prev = r;
        }

        if(r->right!=NULL){
            DFS(r->right);
            prev = r->right;
        }

        return ;
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

    KEY absmin(KEY x) {
        search = x;
        prev = NULL;
        ans = NULL;
        DFS(root);

        if(prev==NULL){         //第一个
            return ans->data.key - search;
        } else if(ans==NULL){   //最后一个
            return search - prev->data.key;
        } else {
            KEY labs = search - prev->data.key;
            KEY rabs = ans->data.key - search;
            return min(labs,rabs);
        }
    }

};


int main() {
    int M;
    cin >> M;

    BinarySearchTree<int,char> BST;

    int op;
    int x;

    int* output = new int[M];
    int c = 0;

    for (int i=0;i<M;++i){
        cin >> op >> x;
        switch (op)
        {
        case 0: output[c++] = BST.absmin(x); break;  //询问要求的最小值
        case 1: BST.insert((SET<int,char>){x,'\0'}); break;  //插入元素x
        case 2: BST.remove(x); break;  //删除元素x
        }
    }

    for(int i=0;i<c;++i)
        cout << output[i] << '\n';

    return 0;
}