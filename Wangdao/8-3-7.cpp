// 划分集合A为A1和A2，元素个数分别是n1和n2，对应的元素和为S1和S2，尽可能使得|n1-n2|最小而|S1-S2|最大。

#include<iostream>
using namespace std;

void partition(int a[], int& low, int& high) {
    int pivot = a[low];
    do {
        while(low < high && a[high]>=pivot) --high;
        if (low < high) {a[low]=a[high]; ++low;}
        while(low < high && a[low]<=pivot) ++low;
        if (low < high) {a[high]=a[low]; --high;}
    } while (low != high);
    a[low] = pivot;
}

int divideSet(int a[], int n) {
    // 排序取中点       O(nlogn)
    // 快速排序取pivot！两边内部无需排序 O(n)
    int low = 0, low0 = 0, high = n - 1, high0 = n - 1;
    while(true) {
        partition(a, low, high);
        if (low == n / 2 - 1) break;
        if (low < n / 2 - 1) {      // 右半部分
            low0 = ++low;
            high = high0;   // 恢复原区间
        }
        else {               // 左半部分
            high0 = --high;
            low = low0;
        }
    }
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n/2; ++i) s1 += a[i];
    for (int i = n/2; i < n; ++i) s2 += a[i];
    return s2-s1;
}

int main() {
    int a[10] = {10,8,7,4,5,6,3,2,1,9};
    cout << divideSet(a, 10) << endl;
    return 0;
}