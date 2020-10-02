// 4252 函数值 - 数组实现
#include<iostream>
using namespace std;

// 答案错误

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
        data = new elemType[size];
        //isEmpty = true;    
        len = 0;  
    };
    //推入
    void push(elemType inserter){
        if(len<size){
            //未满
            //由于每次都要并入相同数量的元素，所以未满时将按次序插入，或者第一轮时推入。
            data[len]=inserter;
            ++len;
        }
    }
    //合并 二分法并入 返回是否插入成功
    bool merge(elemType inserter,int &low){
        //满了
        //二分查找位置，同一轮之内，进行优化，由于是已经排好序的数组
        //但是初始下界在同一轮中相同
        int high=size-1;
        int mid;
        elemType target = inserter;
        int result;

                while(true){
                    if(low>high){
                        return false;
                    }
                    if(low==high||low==high-1){
                        if(target<data[low])
                            {result=low;break;}
                        else if(target<data[high])
                            {result=high;break;}
                        else{result=high+1;break;}
                    }
                    mid=(low+high)/2;
                    if (data[mid]>target)
                        high=mid;
                    else if(data[mid]<target)
                        low=mid;
                    else{
                        result=mid;
                        break;
                    }
                }
        if(result==size)    //如果当前插入的比最大的还大，下面不必再进行插入
            return false;
        //否则插入
        for(int i=size-2;i>=result;--i)
            data[i+1]=data[i];
        data[result]=target;
        return true;
        
    }
    //显示
    void disp(){
        for(int i=0;i<size;++i)
            cout<<data[i]<<" ";
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
void minf(int a,int b,int c,int k,pipe<int>&result,int round){
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
    int low=0;

    while(i<k){
        tmp = a*x*x+b*x+c; //函数值
        ++i;
        sign*=-1;             //反向
        x+=sign*i;            //下一个数

        //决定是否留在循环里
        if(round==0){
            //初始轮
            result.push(tmp);
            continue;
        }
        //非初始轮
        if(!result.merge(tmp,low))
             break;

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
    pipe<int> result(k);
    for (int i=0;i<n;++i){
        cin>>a>>b>>c;
        minf(a,b,c,k,result,i);
    }
    result.disp();
    cout<<'\n';
    //delete result;
    //system("pause");
    return 0;
}