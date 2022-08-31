// D((a,b,c)) = |a-b|+|b-c|+|c-a|
// S_1, S_2, S_3 三个集合对应三元组中距离最小的对应的距离。

#include<iostream>
using namespace std;

int minimumDist(int* arr1, int n1, int* arr2, int n2, int* arr3, int n3) {
    int minDist = INT32_MAX;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            for (int k = 0; k < n3; ++k) {
                int curDist = abs(*(arr1 + i) - *(arr2 + j)) + abs(*(arr1 + i) - *(arr3 + k)) + abs(*(arr2 + j) - *(arr3 + k));
                minDist = curDist < minDist ? curDist : minDist;
            }
        }
    }
    return minDist;
}

int isMin(int a, int b, int c) {
    if (a <= b && a <= c) return true;
    return false;
}

// 固定 c 找 a
int newMinimumDist(int* arr1, int n1, int* arr2, int n2, int* arr3, int n3) {
    int i = 0, j = 0, k = 0, minDist = INT32_MAX;
    while(i < n1 && j < n2 && k < n3) {
        int curDist =  abs(*(arr1 + i) - *(arr2 + j)) + abs(*(arr1 + i) - *(arr3 + k)) + abs(*(arr2 + j) - *(arr3 + k));
        if (curDist < minDist) minDist = curDist;
        if (isMin(*(arr1 + i), *(arr2 + j), *(arr3 + k))) ++i;
        else if (isMin(*(arr2 + j), *(arr1 + i), *(arr3 + k))) ++j;
        else ++k;
    }
    return minDist;
}

int main() {
    int S1[3] = {-1,0,9};
    int S2[4] = {-25,-10,10,11};
    int S3[5] = {2,9,17,30,41};
    cout << minimumDist(S1, 3, S2, 4, S3, 5) << endl;
    cout << newMinimumDist(S1, 3, S2, 4, S3, 5) << endl;
    return 0;
}