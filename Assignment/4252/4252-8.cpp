// 4252 函数值 - 数组实现
#include<iostream>
using namespace std;

//not the solution.
//需要使用优先队列

// 根据对称性，需要多取一个数，最后少输出一个数
int const offset = 1;

// 考虑迭代返回，整块放入

// 一个有限规模的只需要插入的数组管
template <class elemType>
class pipe{
private:
    elemType* data;
    bool isEmpty;
    int size;
    int len;
public:
    pipe(int initsize){
        size = initsize;
        data = new elemType[size*2];    //初始时申请更多的空间
        //isEmpty = true;    
        len = 0;  //size
    };
    void sort(){
        //满时排序
        elemType* arr=data;//0~len
        for(int gap = len / 2; gap > 0; gap = gap / 2) {
            for(int i = gap; i < len; i++) {
                int j = i;
                elemType current = arr[i];
                while(j - gap >= 0 && current < arr[j - gap]) {
                    arr[j] = arr[j - gap];
                    j = j - gap;
                }
                arr[j] = current;
            }
        }
    }
    void push_back(elemType x){
        
        data[len]=x;
        ++len;  //还没有数据

        if(len==size*2){
            sort();
            len=size;
        }
    }
    //显示
    void disp(){
        for(int i=0;i<size;++i)
            cout<<data[i]<<" "; //少输出一个数
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
    //int *tmp = new int[k];
    int tmp;

    // 循环计算，实时判定，减少计算量
    int i=0;
    
    //每一轮内 二分法起点会不变
    //int low=0;

    while(i<k){
        tmp = a*x*x+b*x+c; //函数值
        ++i;
        sign*=-1;             //反向
        x+=sign*i;            //下一个数

        result.push_back(tmp);  //自动排序
    }

    //将tmp并入result
    //result.merge(tmp);

    //delete tmp;
}

int main(){
    int n,k;
    cin>>n>>k;
    int a,b,c;  //a>0
    //int* result = new int[k];
    k=k+offset;
    pipe<int> result(k);
    for (int i=0;i<n;++i){
        cin>>a>>b>>c;
        minf(a,b,c,k,result);
    }
    result.disp();
    cout<<'\n';
    //delete result;
    //system("pause");
    return 0;
}