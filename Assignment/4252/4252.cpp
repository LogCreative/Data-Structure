// 4252 函数值
#include<iostream>
using namespace std;

// 效率不正确

// 考虑迭代返回，整块放入

// 一个有限规模的只需要插入的线性双链表管
template <class elemType>
class pipe{
private:
    //更改为双链表
    struct node{
        elemType data;
        node *prev,*next;
        node (const elemType &x,node *p = NULL,node *n=NULL){
            data = x;
            prev = p;
            next = n;
        }
        node():next(NULL),prev(NULL) {}
        ~node() {}
    };
    node *head;
    node *tail; //尾部节点
    bool isEmpty;
    int size;
public:
    pipe(int initsize){
        head = new node;
        tail = new node;
        head->next=tail;
        tail->prev=head;
        isEmpty = true;
        size = initsize;
        
    };
    //合并 每次merge相同规模的数组
    void merge(elemType* array){
        node*pos;   //监视位置
        if (isEmpty){
            //初始化覆写
            elemType* ptr=array;
            pos=head;
            for (int i=0;i<size;++i){
                node *tmp=new node(*ptr);
                tmp->next=pos->next;
                tmp->next->prev=tmp;
                pos->next=tmp;
                tmp->prev=pos;
                ptr++;
                pos=pos->next;
            }
            isEmpty=false;
        }
        else{
            //正式归并

            //归并排序的治的部分

            //正在寻找的元素
            elemType *finding = array;
            pos = head;
            for(int i=size;i>0;--i){
                while (true) {
                    if (pos->next==tail)
                        return ;    //下一个到尾部了，终止该序列的放置
                    //否则此时是有下一个实数据的
                    if (pos->next->data<*finding){
                        //夹逼原理
                        pos=pos->next;
                    }
                    else
                        break;
                }
                //找到放置的位置，插入
                node*tmp=new node(*finding);
                tmp->next=pos->next;
                tmp->next->prev=tmp;
                pos->next=tmp;
                tmp->prev=pos;
                
                //移动到插入后的节点
                pos=tmp;

                //现在绝对不是最后一个实节点，所以可以删除最后一个
                tmp=tail->prev;
                tmp->prev->next=tmp->next;
                tmp->next->prev=tmp->prev;
                delete tmp;

                // 以上可以写成函数形式以优化

                finding++;
            }
            
        }
    }
    //显示
    void disp(){
        node*pos=head;
        for (int i=0;i<size;++i){
            cout<<pos->next->data<<" ";
            pos=pos->next;
        }
    }

};

// 手写一个floor函数
int floor(double input){
    //下取整函数
    // c++ 17 会向0取整。
    return static_cast<int>(input) + (input>0?0:-1);

}

// 最小的 k 个数至少对每一个函数都要取最小的 k 个数。
// 该函数将把新的最小值与 result 合并
// 按照从小到大的顺序
void minf(int a,int b,int c,int k,pipe<int>&result){
    // 采用螺旋上升式方法 自然排序

    double middle = -b/(2.0*a);
    //初值会有偏左的偏置
    int middle_int = floor(middle);

    // 决定取值的初始方向 true = 向右 false = 向左
    bool initdir = (middle - middle_int>0.5)?true:false;

    // 决定取值的初始方向 1 = 向右，0 = 向左
    middle_int += (initdir)?1:0;
    
    // 存储符号，现在是第一次取值的方向
    int sign = (initdir)?1:-1;

    int x = middle_int;       //自变量
    int *tmp = new int[k];  
    int result1;
    tmp[0] = a*x*x+b*x+c;
    for(int i=1;i<k;++i){
        sign*=-1;             //反向
        x+=sign*i;            //下一个数
        result1 = a*x*x+b*x+c;
        tmp[i] = result1; //函数值输入
    }

    //将tmp并入result
    result.merge(tmp);

    delete tmp;
}

int main(){
    int n,k;
    cin>>n>>k;
    int a,b,c;  //a>0
    //int* result = new int[k];
    pipe<int> result(k);
    for (int i=0;i<n;++i){
        cin>>a>>b>>c;
        minf(a,b,c,k,result);
    }
    result.disp();
    cout<<'\n';
    //delete result;
    return 0;
}