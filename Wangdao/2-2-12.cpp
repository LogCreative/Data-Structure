// 已知一个整数数列 A，每个元素 0 <= a_i < n，若多于 n/2 的元素相同为 x，则称 x 为 A 的主元素。寻找 A 的主元素。

#include<iostream>
using namespace std;

int findMainElement(int *arr, int n) {
    // Moore
    int ans;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int b = *(arr + i);
        if (cnt == 0) ans = b;
        if (b == ans) ++cnt;
        else --cnt;
    }
    if (cnt > 0) return ans;
    return -1;
}

int main() {
    int A[8] = {0,5,5,3,5,7,5,5};
    cout << findMainElement(A, 8) << endl;
    int B[8] = {0,5,5,3,5,1,5,7};
    cout << findMainElement(B, 8) << endl;
    return 0;
}

// 可以写次优解。