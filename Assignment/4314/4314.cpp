#include<iostream>
using namespace std;

int times;

//冒泡排序
void bubbleSort(int a[],int size){
    int i,j;
    int tmp;
    bool flag = true;

    for(i=1;i<size&&flag;++i){
        flag=false;
        for(j=0;j<size-i;++j)
            if(a[j+1]<a[j]){
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                flag = true;
                ++times;
            }
    }
}

int main(){
    int n;      //数据量
    cin >> n;

    times = 0;

    int *a = new int[n];
    for(int i = 0;i<n;++i)
        cin >> a[i];
    
    bubbleSort(a,n);

    cout << times << '\n';
    return 0;
}