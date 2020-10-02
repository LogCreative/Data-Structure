#include<iostream>
using namespace std;

//注意背一下归并排序！为什么原来不行！

int main(){
    int m,n;
    cin >> m;
    cin >> n;

    int*l1 = new int[m];
    for(int i = 0;i<m;++i)
        cin >> l1[i];
    
    int*l2 = new int[n];
    for(int i = 0;i<n;++i)
        cin >> l2[i];

    int*l3 = new int[m+n];
    int p1 = 0, p2 = 0, p3 = 0;
    
    while(p1<m && p2<n)
        if(l1[p1]<l2[p2])
            l3[p3++] = l1[p1++];
        else l3[p3++] = l2[p2++];
    
    while(p1<m) l3[p3++] = l1[p1++];
    while(p2<n) l3[p3++] = l2[p2++];

    for(int i = 0;i<m+n;++i)
        cout << l3[i] << '\n';

    delete[] l1;
    delete[] l2;
    delete[] l3;
    return 0;
}