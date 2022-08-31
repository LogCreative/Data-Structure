// 设将 n 个整数存放在一维数组 R 中，设计一个在时间和空间两方面都尽可能高效的算法。将 R 中保存的序列循环左移 p 个位置。

#include<iostream>
#include<vector>
using namespace std;

void reverse(int *arr, int n){
    for (int i = 0; i < n / 2; ++i) {
        int tmp = *(arr + i);
        *(arr + i) = *(arr + n - i - 1);
        *(arr + n - i - 1) = tmp;
    }
}

void loopShiftLeft(int* arr, int n, int p){
    // [x x x x o o o o o o]
    reverse(arr, p);
    reverse(arr + p, n - p);
    reverse(arr, n);
}

int main() {
    int R[10] = {1,2,3,4,5,6,7,8,9,10};
    loopShiftLeft(R, 10, 4);
    for (int i = 0; i < 10; ++i)
        cout << R[i] << " ";
    cout << endl;
    return 0;
}