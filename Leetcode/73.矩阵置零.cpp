/*
 * @lc app=leetcode.cn id=73 lang=cpp
 *
 * [73] 矩阵置零
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool flag_col = false;
        bool flag_row = false;
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                flag_col = true;
                break;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                flag_row = true;
                break;
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    for (int k = i - 1; k >= 0; --k)
                        matrix[k][j] = 0;
                    for (int k = j - 1; k >= 0; --k)
                        matrix[i][k] = 0;
                    continue;
                }
                if (matrix[i][0] == 0) {
                    matrix[i][j] = 0;
                }
                if (matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (flag_col) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }
        if (flag_row) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};
// @lc code=end

