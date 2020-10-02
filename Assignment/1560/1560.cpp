// 1560. BST
// 用于维护集合的二叉查找树为传统的二叉查找树
// 不能用传统方法。
#include<iostream>
#include<string>
using namespace std;

string output;  //输出
string tempstr; //临时存储

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
        ~BinaryNode() {}
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
        if (x==t->data.key){
            if(t->left==NULL&&t->right==NULL){  //叶子结点
                if(t==root) root=NULL;
                t = NULL;
            }
            else if(t->left!=NULL&&t->right==NULL){
                if(t==root) root=t->left;
                BinaryNode *oldNode = t;
                t = (t->left!=NULL)?t->left:t->right;
                oldNode = NULL;
            }
            else if(t->right!=NULL){
                BinaryNode *tmp = t->right;
                while(tmp->left!=NULL) tmp=tmp->left;
                t->data = tmp->data;
                remove(t->data.key,t->right);
            }
        }
        else if (x<t->data.key) remove(x,t->left);
        else remove(x,t->right);
        
    }

    SET<KEY,OTHER> *find(const KEY &x, BinaryNode *t) const {
        if (t==NULL||t->data.key==x)
            return (SET<KEY,OTHER>*) t;
        if (x<t->data.key){
            tempstr+="l";
            return find(x,t->left);
        }
        else {
            tempstr+="r";
            return find(x,t->right);
        }
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
        tempstr = "*";  //初始化
        SET<KEY,OTHER>* tmp = find(x,root);
        if(tmp==NULL)
            output+=(string)"Nothing.";
        else
            output+=tempstr;
        output+="\n";
        return tmp;
    }

    void insert(const SET<KEY,OTHER> &x) {
        //如若添加已存在的元素或删除不存在的元素，则该操作不应产生影响。
        if (find(x.key,root)!=NULL) return ;
        insert(x,root);
    }

    void remove(const KEY &x) {
        if (find(x,root)==NULL) return ;
        remove(x,root);
    }
    
};

int main() {
    
    int Q;
    cin >> Q;   //操作个数

    BinarySearchTree<int,char> BST; //空类型
    output = "";

    char op;
    int x;
    for (int i = 0;i < Q;++i) {
        cin >> op >> x;
        switch(op) {
            case '+': BST.insert((SET<int,char>){x,'\0'}); break;  //添加
            case '-': BST.remove(x); break;  //删除
            case '*': BST.find(x); break; //查找
        }
    }

    cout<<output;
    return 0;

}