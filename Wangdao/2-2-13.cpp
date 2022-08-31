// 找出数组中未出现过的最小正整数。
// 最简单的是排序。

#include<iostream>
using namespace std;

int minimumMissingPositiveInteger(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (*(arr + i) < 0)
            *(arr + i) = n + 1;
    }
    // [5,3,2,3]
    for (int i = 0; i < n; ++i) {
        int b = abs(*(arr + i));        // may be negative since it may be flagged.
        if (b <= n)
            *(arr + b - 1) = -abs(*(arr + b - 1));
    }

    for (int i = 0; i < n; ++i) {
        if (*(arr + i) > 0)
            return i + 1;
    }
    return n + 1;   // every one is negative
}

int main() {
    int A[4] = {-5, 3, 2, 3};
    cout << minimumMissingPositiveInteger(A, 4) << endl;
    return 0;
}