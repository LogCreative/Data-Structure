#include<iostream>
using namespace std;

template<class KEY,class OTHER>
struct SET {
    KEY key;
    OTHER other;
};

template<class KEY,class OTHER>
class dynamicSearchTable {
public:
    virtual SET<KEY,OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY,OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable() {};
};

// 前提：元素互异
// 普通的二叉查找树
template<class KEY,class OTHER>
class BinarySearchTree: public dynamicSearchTable<KEY,OTHER>{
private:
    struct BinaryNode {
        SET<KEY,OTHER> data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET<KEY,OTHER> &thedata, BinaryNode *lt=NULL, BinaryNode *rt=NULL):
            data(thedata),left(lt),right(rt) {}
    };

    BinaryNode *root;
    void insert(const SET<KEY,OTHER> &x,BinaryNode *&t) {
        if(t==NULL) t=new BinaryNode(x,NULL,NULL);
        else if(x.key<t->data.key) insert(x,t->left);
        else if(t->data.key<x.key) insert(x,t->right);
    }
    void remove(const KEY &x,BinaryNode *&t) {
        if(t==NULL) return ;
        if(x<t->data.key) remove(x,t->left);
        else if(t->data.key<x) remove(x,t->right);
        else if(t->left!=NULL && t->right!=NULL) {  //有两个孩子
            BinaryNode *tmp = t->right;
            while(tmp->left!=NULL) tmp = tmp->left;
            t->data=tmp->data;
            remove(t->data.key,t->right);
        } else {                                    //有一个孩子或者是叶节点
            BinaryNode *oldNode = t;
            t = (t->left!=NULL)?t->left:t->right;
            delete oldNode;
        }
    }
    SET<KEY,OTHER> *find(const KEY &x,BinaryNode *t) const {
        if(t==NULL||t->data.key==x) return (SET<KEY,OTHER> *)t;
        if(x<t->data.key) return find(x,t->left);
        else return find(x,t->right);
    }
    void makeEmpty(BinaryNode *t) {
        if(t==NULL) return ;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

public:
    BinarySearchTree() { root = NULL; }
    ~BinarySearchTree() { makeEmpty(root); }
    SET<KEY,OTHER> *find(const KEY &x) const { return find(x,root); }
    void insert(const SET<KEY,OTHER> &x) { insert(x,root); }
    void remove(const KEY &x) { remove(x,root); }
};

//AVL树
//左右子树高度差不超过 1
template<class KEY,class OTHER>
class AvlTree: public dynamicSearchTable<KEY,OTHER>
{
private:
    struct AvlNode{
        SET<KEY,OTHER> data;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const SET<KEY,OTHER> &element, AvlNode *lt, AvlNode *rt, int h=1):
            data(element),left(lt),right(rt),height(h) {}
    };

    AvlNode *root;

    void insert(const SET<KEY,OTHER> &x, AvlNode *&t){
        if(t==NULL) t = new AvlNode(x,NULL,NULL);
        else if (x.key<t->data.key){
            insert(x,t->left);
            if(height(t->left)-height(t->right)==2){
                if(x.key<t->left->data.key) LL(t); else LR(t);
            }
        } else if (t->data.key<x.key){
            insert(x,t->right);
            if(height(t->right)-height(t->left)==2){
                if(t->right->data.key<x.key) RR(t); else RL(t);
            }
        }

        t->height = max(height(t->left),height(t->right)) + 1;
    }
    bool remove(const KEY &x, AvlNode *&t) {
        if(t==NULL) return true;
        if(x==t->data.key) {                                //删除根节点
            if(t->left==NULL || t->right==NULL){            //叶节点或者只有一个儿子
                AvlNode *oldNode = t;
                t = (t->left!=NULL)?t->left:t->right;
                delete oldNode;
                return false;
            } else {
                AvlNode *tmp = t->right;
                while(tmp->left!=NULL) tmp = tmp->left;
                t->data = tmp->data;
                if(remove(tmp->data.key,t->right)) return true;
                return adjust(t,1);
            }
        }

        if(x<t->data.key){
            if(remove(x,t->left)) return true;
            return adjust(t,0);
        } else {
            if(remove(x,t->right)) return true;
            return adjust(t,1);
        }
    }
    void makeEmpty(AvlNode *t){
        if(t==NULL) return ;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    int height(AvlNode *t) const { return t==NULL?0:t->height; }
    void LL(AvlNode *&t){
        AvlNode *t1=t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = max(height(t->left),height(t->right))+1;
        t1->height = max(height(t1->left),height(t))+1;
        t = t1;
    }
    void LR(AvlNode *&t) { RR(t->left); LL(t); }
    void RL(AvlNode *&t) { LL(t->right); RR(t); }
    void RR(AvlNode *&t){
        AvlNode *t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = max(height(t->left),height(t->right))+1;
        t1->height = max(height(t1->right),height(t))+1;
        t = t1;
    }
    int max(int a, int b) { return (a>b)?a:b; }
    bool adjust(AvlNode *&t, int subTree){
        if(subTree){
            if(height(t->left)-height(t->right)==1) return true;
            if(height(t->right)==height(t->left)){--t->height;return false;}
            if(height(t->left->right)>height(t->left->left)){ LR(t); return false; }
            LL(t);
            if(height(t->right)==height(t->left)) return false;
            else return true;
        } else {
            if(height(t->right)-height(t->left)==1) return true;
            if(height(t->left)==height(t->right)){--t->height;return false;}
            if(height(t->right->left)>height(t->right->right)){ RL(t); return false; }
            RR(t);
            if(height(t->right)==height(t->left)) return false;
            else return true;
        }
    }

public:
    AvlTree() { root = NULL; }
    ~AvlTree() { makeEmpty(root); }
    SET<KEY,OTHER> *find(const KEY &x) const {
        AvlNode *t = root;

        while(t!=NULL && t->data.key!=x)
            if(t->data.key>x) t = t->left;
            else t = t->right;

        if(t==NULL) return NULL;
        else return (SET<KEY,OTHER> *)t;
    }
    void insert(const SET<KEY,OTHER> &x){ insert(x,root); }
    void remove(const KEY &x) { remove(x,root); }

};

//红黑树
// (1) 每一个节点被染成红色或黑色
// (2) 根节点是黑色的
// (3) 如果一个节点是红色的，那么它的儿子节点必须是黑色的
// (4) 从任何一个节点出发到空节点（黑色节点）的路径上，必须包含相同数目的黑色节点
template<class KEY,class OTHER>
class RedBlackTree: public dynamicSearchTable<KEY,OTHER>
{
private:
    enum colourT { RED,BLACK };
    struct RedBlackNode {
        SET<KEY,OTHER> data;
        RedBlackNode *left;
        RedBlackNode *right;
        colourT colour;

        RedBlackNode(const SET<KEY,OTHER> &element,RedBlackNode *lt=NULL,RedBlackNode *rt=NULL,colourT h=RED):data(element),left(lt),right(rt),colour(h){}
    };

    RedBlackNode *root;

    void makeEmpty(RedBlackNode *&t){
        if(t!=NULL){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t=NULL;
    }
    void insertAdjust(RedBlackNode *gp,RedBlackNode *p,RedBlackNode *t){
        if(p->colour) return ;          //没有出现连续红节点
        if(p==root){
            p->colour = BLACK;
            return ;
        }
        if(gp->left==p)
            if(p->left==t)  LL(gp);
            else LR(gp);
        else if(p->right==t) RR(gp);
            else RL(gp);
    }
    void removeAdjust(RedBlackNode *&p,RedBlackNode *&c,RedBlackNode *&t,KEY del){
        if(c->colour==RED) return ;
        if(c==root)
            if(c->left&&c->right&&c->right->colour==c->left->colour){
                c->colour=RED;
                c->left->colour=c->right->colour=BLACK;
                return ;
            }
        
        if(((c->left&&c->left->colour)||c->left==NULL)
            && ((c->right&&c->right->colour)||c->right==NULL))
            if(((t->left&&t->left->colour)||t->left==NULL)
                &&((t->right&&t->right->colour)||t->right==NULL))
                    { p->colour = BLACK; t->colour=c->colour=RED; }
            else {
                if(p->left==t)
                    if(t->left && t->left->colour==RED){
                        t->left->colour=BLACK;
                        LL(p);
                        p = t;
                    } else {
                        LR(p);
                        p = p->right;
                        p->colour = BLACK;
                    }
                else if(t->right&&t->right->colour==RED){
                    t->right->colour = BLACK;
                    RR(p);
                    p=t;
                    } else {
                        RL(p);
                        p=p->left;
                        p->colour = BLACK;
                    }
                c->colour=RED;
            }
            else {
                if(c->data.key==del){
                    if(c->left&&c->right){
                        if(c->right->colour==BLACK){
                            LL(c); c=c->right;
                        }
                        return ;
                    }
                    if(c->left){
                        LL(c);
                        p = c;
                        c = c->right;
                    }
                    else {
                        RR(c);
                        p = c;
                        c = c->left;
                    }
                }
                else {
                    p = c;
                    c = (del<p->data.key?p->left:p->right);
                    t = (c==p->left?p->right:p->left);
                    if(c->colour==BLACK){
                        if(t==p->right) RR(p);
                        else LL(p);
                        p = t;
                        t = (c==p->left?p->right:p->left);
                        removeAdjust(p,c,t,del);
                    }
                }
            }
    }
    void LL(RedBlackNode *gp){
        RedBlackNode *p = gp->left, *t=p->left;
        RedBlackNode tmp = *gp;
        gp->data = p->data;
        gp->left = t;
        gp->right = p;
        p->data = tmp.data;
        p->left = p->right;
        p->right = tmp.right;
    }
    void LR(RedBlackNode *gp){
        RedBlackNode *p=gp->left, *t=p->right;
        RedBlackNode tmp = *gp;
        gp->data = t->data;
        gp->right = t;
        p->right = t->left;
        t->data = tmp.data;
        t->left = t->right;
        t->right = tmp.right;
    }
    void RL(RedBlackNode *gp){
        RedBlackNode *p=gp->right, *t=p->left;
        RedBlackNode tmp = *gp;
        gp->data = t->data;
        gp->left = t;
        p->left = t->right;
        t->data = tmp.data;
        t->right = t->left;
        t->left = tmp.left;
    }
    void RR(RedBlackNode *gp){
        RedBlackNode *p = gp->right, *t=p->right;
        RedBlackNode tmp = *gp;
        gp->data = p->data;
        gp->right = t;
        gp->left = p;
        p->data = tmp.data;
        p->right = p->left;
        p->left = tmp.left;
    }
public:
    RedBlackTree(RedBlackNode*t=NULL) { root = t; }
    ~RedBlackTree() { makeEmpty(root); }
    SET<KEY,OTHER> *find(const KEY &x) const{
        RedBlackNode *t = root;
        while(t!=NULL && t->data.key!=x)
            if(t->data.key>x) t=t->left;
            else t=t->right;
        
        if(t==NULL) return NULL;
        else return (SET<KEY,OTHER>*) t;
    }
    void insert(const SET<KEY,OTHER> &x){
        RedBlackNode *t,*parent,*grandP;

        if(root==NULL){
            root=new RedBlackNode(x,NULL,NULL,BLACK);
            return;
        }

        parent = grandP = t = root;
        while(true){
            if(t){
                if(t->left&&t->left->colour==RED&&
                    t->right&&t->right->colour==RED){
                        t->left->colour = t->right->colour = BLACK;
                        t->colour = RED;
                        insertAdjust(grandP,parent,t);
                    }
                grandP = parent;
                parent = t;
                t = (t->data.key>x.key?t->left:t->right);
            }
            else {
                t = new RedBlackNode(x);
                if(x.key<parent->data.key) parent->left = t;
                else parent->right = t;
                insertAdjust(grandP,parent,t);
                root->colour = BLACK;
                return ;
            }
        }
    }
    void remove(const KEY &x){
        KEY del = x;
        RedBlackNode *t,*p,*c;

        if(root==NULL) return ;
        if(root->data.key==x && root->left==NULL && root->right==NULL){
            delete root;
            root = NULL;
            return ;
        }

        p=c=t=root;
        while(true){
            removeAdjust(p,c,t,del);
            if(c->data.key==del && c->left&&c->right){
                RedBlackNode *tmp = c->right;
                while(tmp->left) tmp = tmp->left;
                c->data = tmp->data;
                del = tmp->data.key;
                p = c;
                c = c->right;
                t = p->left;
                continue;
            }

            if(c->data.key==del){
                delete c;
                if(p->left==c) p->left=NULL;
                else p->right = NULL;
                root->colour = BLACK;
                return ;
            }
            p = c;
            c = (del<p->data.key?p->left:p->right);
            t = (c==p->left?p->right:p->left);
        }
    }
};

//AA树
// (1) 如果节点是一个叶子，层次是1.
// (2) 如果节点是红色的，就是它父亲的层次
// (3) 如果节点是黑色的，比它父亲的层次少1
// (4) 空节点的层次是0
//水平链表示法
// (1) 水平链只能是右儿子链（因为只有右儿子才可能是红色的）
// (2) 不可能有两条连续的水平链（因为不会有连续的红色节点）
// (3) 在层次2或2以上的绩点必定有两个儿子
// (4) 如果一个节点没有右水平链，它的两个儿子就在同一层
template<class KEY,class OTHER>
class AATree: public dynamicSearchTable<KEY,OTHER> {
private:
    struct AANode {
        SET<KEY,OTHER> data;
        AANode *left;
        AANode *right;
        int level;

        AANode(const SET<KEY,OTHER> &thedata,AANode *lt,AANode *rt,int lv=1):
            data(thedata),left(lt),right(rt),level(lv) {}
    };

    AANode *root;

    void insert(const SET<KEY,OTHER> &x,AANode *&t){
        if(t==NULL) t = new AANode(x,NULL,NULL);
        else if (x.key<t->data.key) insert(x,t->left);
            else if (t->data.key<x.key) insert(x,t->right);
                else return ;
        LL(t);
        RR(t);
    }
    void remove(const KEY &x, AANode *&t){
        if(t==NULL) return ;
        if(x<t->data.key) remove(x,t->left);
        else if(t->data.key<x) remove(x,t->right);
            else if (t->left!=NULL && t->right!=NULL){
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
            t->right->level=t->level;
        LL(t);
        if(t->right!=NULL) LL(t->right);
        if(t->right!=NULL&&t->right->right!=NULL) LL(t->right->right);
        RR(t);
        if(t->right!=NULL) RR(t->right);
    }
    void makeEmpty(AANode *t) {
        if(t!=NULL){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }
    void LL(AANode *&t){
        if(t->left!=NULL && t->left->level==t->level){
            AANode *t1=t->left;
            t->left = t1->right;
            t1->right = t;
            t = t1;
        }
    }
    void RR(AANode *&t){
        if(t->right!=NULL && t->right->right!=NULL && t->right->right->level==t->level){
            AANode *t1=t->right;
            t->right = t1->left;
            t1->left = t;
            t = t1;
            t->level++;
        }
    }
    int min(int a,int b){ return a<b?a:b; }

public:
    AATree() { root = NULL; }
    ~AATree() { makeEmpty(root); }
    SET<KEY,OTHER> *find(const KEY &x) const {
        AANode *t = root;

        while(t!=NULL && t->data.key!=x)
            if(t->data.key>x) t = t->left;
            else t = t->right;
        
        if(t==NULL) return NULL;
        else return (SET<KEY,OTHER> *)t;
    }
    void insert(const SET<KEY,OTHER> &x) { insert(x,root); }
    void remove(const KEY &x) { remove(x,root); }
};

//伸展树

//散列表（哈希）

//闭哈希表
template<class KEY,class OTHER>
class closeHashTable: public dynamicSearchTable<KEY,OTHER>{
private:
    struct node {
        SET<KEY,OTHER> data;
        int state;  // 0--empty 1--active 2--deleted

        node() {state=0;}
    };

    node *array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x){return x;}
public:
    closeHashTable(int length=101,int (*f)(const KEY &x)=defaultKey){
        size = length;
        array = new node[size];
        key = f;
    }
    ~closeHashTable(){ delete[] array; }

    SET<KEY,OTHER> *find(const KEY &x) const{
        int initPos,pos;

        initPos = pos = key(x)%size;
        do{
            if(array[pos].state == 0) return NULL;
            if(array[pos].state == 1 && array[pos].data.key==x)
                return (SET<KEY,OTHER> *)&array[pos];
            pos = (pos+1)%size;
        } while(pos!=initPos);

    }

    void insert(const SET<KEY,OTHER> &x){
        int initPos,pos;

        initPos = pos = key(x.key) % size;
        do{
            if(array[pos].state!=1){
                array[pos].data=x;
                array[pos].state=1;
                return ;
            }
            pos = (pos+1)%size;
        } while(pos!=initPos);
    }

    void remove(const KEY &x){
        int initPos,pos;

        initPos = pos = key(x)%size;
        do{
            if(array[pos].state==0) return ;
            if(array[pos].state==1 && array[pos].data.key==x){
                array[pos].state=2;
                return ;
            }
            pos = (pos+1)%size;
        } while (pos!=initPos);
    }
};

//开哈希表
template<class KEY,class OTHER>
class openHashTable: public dynamicSearchTable<KEY,OTHER>{
private:
    struct node {
        SET<KEY,OTHER> data;
        node *next;

        node(const SET<KEY,OTHER> &d,node *n = NULL):data(d),next(n) {}
        node():next(NULL) {}
    };

    node **array;
    int size;
    int (*key)(const KEY &x);   //强制转换
    static int defaultKey(const int &x){ return x; }
public:
    openHashTable(int length=101,int (*f)(const KEY &x)=defaultKey){
        size = length;
        array = new node*[size];
        key = f;
        for(int i=0;i<size;++i)
            array[i]=NULL;
    }
    ~openHashTable(){
        node *p,*q;

        for(int i=0;i<size;++i){
            p = array[i];
            while(p!=NULL) {q=p->next; delete p; p=q;}
        }

        delete[] array;
    }

    SET<KEY,OTHER> *find(const KEY &x) const{
        int pos;
        node *p;

        pos = key(x) %size;
        p = array[pos];
        while(p!=NULL && !(p->data.key==x)) p = p->next;
        if(p==NULL) return NULL;
        else return (SET<KEY,OTHER> *)p;
    }

    void insert(const SET<KEY,OTHER> &x){
        int pos;

        pos = key(x.key) % size;
        array[pos]=new node(x,array[pos]);
    }

    void remove(const KEY &x){
        int pos;
        node *p,*q;

        pos = key(x)%size;
        if(array[pos]==NULL) return;
        p = array[pos];
        if(array[pos]->data.key==x){
            array[pos]=p->next;
            delete p;
            return ;
        }
        while(p->next!=NULL&&!(p->next->data.key==x)) p=p->next;

        if(p->next!=NULL){
            q=p->next;
            p->next = q->next;
            delete q;
        }
    }
};


class MyHashSet {
    struct node {
        int data;
        node *next;
        
        node(int d,node *n = NULL):data(d),next(n) {}
    };
    
    node **array;
    int size;
    
public:
    /** Initialize your data structure here. */
    MyHashSet(int s=101) {
        size = s;
        array = new node*[size];
        for(int i=0;i<size;++i)
            array[i]=NULL;
    }
    
    void add(int key) {
        int pos;
        
        pos = key % size;
        array[pos] = new node(key,array[pos]);
    }
    
    void remove(int key) {
        int pos;
        node *p,*q;
        
        pos = key % size;
        for(p=array[pos];p!=NULL;p=p->next)
            if(p->data==key)
                p->data=-1;
        
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int pos;
        node *p;
        
        pos = key % size;
        p = array[pos];
        while(p!=NULL && p->data!=key) p = p->next;
        if(p==NULL) return false;
        else return true;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

int main(){
    // AvlTree<int,char> at;
    // for(int i=5;i>=0;--i)
    //     at.insert({i,'\0'});

    // AATree<int,char> aa;
    // for(int i=5;i>=0;--i)
    //     aa.insert({i,'\0'});

    // RedBlackTree<int,char> rb;
    // for(int i=5;i>=0;--i)
    //     rb.insert({i,'\0'});

    // closeHashTable<int,char> cht;
    // for(int i=25;i>=0;--i)
    //     cht.insert({i,'\0'});

    // openHashTable<int,char> oht;
    // for(int i=25;i>=0;--i)
    //     oht.insert({i,'\0'});

    // MyHashSet hashSet();
    // hashSet->add(1);         
    // hashSet->add(2);         
    // hashSet.contains(1);    // 返回 true
    // hashSet.contains(3);    // 返回 false (未找到)
    // hashSet.add(2);          
    // hashSet.contains(2);    // 返回 true
    // hashSet.remove(2);          
    // hashSet.contains(2);    // 返回  false (已经被删除)

    return 0;
}