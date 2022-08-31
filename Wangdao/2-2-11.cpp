// 一个长为 L 的升序序列 S，处在第 \ceil{L/2} 个位置的数称为 S 的中位数，两个序列的中位数是含他们所有元素的升序序列的中位数，现有两个等长升序序列 A 和 B，找出 A 和 B 的中位数。

#include<iostream>
using namespace std;

int findMedian(int* arr1, int* arr2, int n) {
    // postion n*2/2=n
    int pos1 = 0;
    int pos2 = 0;
    int cnt = 0;
    while(pos1 < n && pos2 < n) {
        if (*(arr1+pos1) < *(arr2+pos2)) {
            if (++cnt == n)
                return *(arr1 + pos1);
            ++pos1;
        }
        else {
            if (++cnt == n)
                return *(arr2 + pos2);
            ++pos2;
        }
    }
    while(pos1 < n) {
        if (++cnt == n)
            return *(arr1 + pos1);
        ++pos1;
    }
    while(pos2 < n) {
        if (++cnt == n)
            return *(arr2 + pos2);
        ++pos2;
    }
}

int main() {
    int A[5] = {11,13,15,17,19};
    int B[5] = {2,4,6,8,20};
    cout << findMedian(A, B, 5) << endl;
    return 0;
}

// 另解：
//      A 的中位数 a，B 的中位数 b。
//      根据 a 与 b 的关系不断舍弃一些数组继续寻找
//      log_2 n