#include<iostream>
using namespace std;

template<class Type>
int divide(Type a[],int low,int high){
    Type k = a[low];
    do{
        while(low<high && a[high]>=k) --high;
        if(low<high){a[low]=a[high];++low;}
        while(low<high && a[low]<=k) ++low;
        if(low<high){a[high]=a[low];--high;}
    } while(low!=high);
    a[low]=k;
    return low;
}

template<class Type>
void quickSort(Type a[],int low,int high){
    int mid;
    if (low>=high) return ;
    mid = divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}

template<class Type>
void quickSort(Type a[],int size){
    quickSort(a,0,size-1);
}

int main(){
    int N;
    cin >> N;

    int* a = new int[N];

    for(int i=0;i<N;++i)
        cin >> a[i];

    quickSort(a,N);

    int tmp = a[0];
    int count = 1;
    for(int i=1;i<N;++i){
        //走一遍
        if(a[i]>tmp){
            ++count;
            tmp = a[i];
        }
    }
    cout << count << '\n';

    delete[] a;
    return 0;
    
}