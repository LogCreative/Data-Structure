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
    //virtual SET<KEY,OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY,OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable() {}
};

template<class KEY, class OTHER>
class AATree: public dynamicSearchTable<KEY,OTHER> {
private:
    struct AANode
    {
        SET<KEY,OTHER> data;
        AANode *left;
        AANode *right;
        int level;

        AANode(const SET<KEY,OTHER> & thedata, AANode *lt=NULL,
            AANode *rt=NULL,int lv=1): data(thedata),left(lt),right(rt),level(lv) { }
    };
    AANode *root;
    
    void LL(AANode *&t){
        if(t->left!=NULL && t->left->level==t->level){
            AANode *t1 = t->left;
            t->left = t1->right;
            t1->right = t;
            t = t1;
        }
    }

    void RR(AANode *&t){
        if(t->right!=NULL && t->right->right!=NULL &&
        t->right->right->level==t->level){
            AANode *t1 = t->right;
            t->right = t1->left;
            t1->left = t;
            t = t1;
            t->level++;
        }
    }

    void insert(const SET<KEY,OTHER> &x, AANode *&t) {
        if(t==NULL)
            t=new AANode(x,NULL,NULL);
        else if(x.key<t->data.key)
            insert(x,t->left);
        else if(t->data.key<x.key)
            insert(x,t->right);
        else return ;

        LL(t);
        RR(t);
    }

    void remove(const KEY &x, AANode *&t) {
        if(t==NULL) return ;
        if(x<t->data.key) remove(x,t->left);
        else if(t->data.key<x) remove(x,t->right);
            else if(t->left!=NULL && t->right!=NULL){
                AANode *tmp = t->right;
                while(tmp->left!=NULL) tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data.key,t->right);
            }
            else {
                AANode *oldNode = t;
                t = (t->left!=NULL)?t->left:t->right;
                delete oldNode;
                return ;
            }
        if(t->left==NULL||t->right==NULL) t->level=1;
        else t->level=min(t->left->level,t->right->level)+1;
        if(t->right!=NULL&&t->right->level>t->level)
            t->right->level = t->level;
        LL(t);
        if(t->right!=NULL) LL(t->right);
        if(t->right!=NULL && t->right->right!=NULL) LL(t->right->right);
        RR(t);
        if(t->right!=NULL) RR(t->right);
    }

    void makeEmpty(AANode *t) {
        if(t==NULL) return ;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

public:
    AATree() {
        root = NULL;
    }
    ~AATree() {
        makeEmpty(root);
    }

    void insert(const SET<KEY,OTHER> &x) {
        insert(x,root);
    }

    void remove(const KEY &x) {
        remove(x,root);
    }

    KEY absmin(KEY x) {
        int ans = -1;
        AANode *n = root;

        while (n != NULL) {
            if (x < n->data.key) {
                if(ans==-1) ans = n->data.key - x;
                else ans = min((n->data.key - x), ans);
                n = n->left;
            } else if (x > n->data.key) {
                if(ans==-1) ans = x - n->data.key;
                else ans = min((x - n->data.key), ans);
                n = n->right;
            } else {
                return 0;
            }
        }

        return ans;
    }

};


int main() {
    int M;
    cin >> M;

    AATree<int,char> BST;

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