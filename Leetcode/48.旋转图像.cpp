/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n==0 || n==1) return;
        // a cycle link list method
        int startpoint = (n - n % 2) / 2 - 1;
        for (int linelength = 2 + n % 2;
            linelength <= n;
            linelength += 2){
                vector<int> savedline;
                auto ptr = matrix[startpoint].begin() + startpoint;
                for (int i = 0; i < linelength - 1; ++i)
                    savedline.push_back(*ptr++);
                for (int k = 1; k < linelength; ++k){
                    int i = startpoint + k;
                    int endpoint = startpoint + linelength - 1;
                    int j = endpoint - k;
                    matrix[startpoint][j] = matrix[i][startpoint];
                    matrix[i][startpoint] = matrix[endpoint][i];
                    matrix[endpoint][i] = matrix[j][endpoint];
                    matrix[j][endpoint] = savedline.back();
                    savedline.pop_back();
                }
                startpoint -= 1;
            }
    }
};
// @lc code=end

