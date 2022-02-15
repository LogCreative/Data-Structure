/*
 * @lc app=leetcode.cn id=1380 lang=cpp
 *
 * [1380] 矩阵中的幸运数
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        // Lucky Number: -^^^^
        //               .
        //               .
        // O(mn)
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> rowmin(m);
        vector<int> res;
        for(int i = 0; i < m; ++i){
            int rowmin_el = 2e5;   // max = 1e5
            int rowmin_col;
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] < rowmin_el){
                    rowmin_el = matrix[i][j];
                    rowmin_col = j;
                }
            }
            bool flag = false;
            for (int k = 0; k < m; ++k){
                if (k == i) continue;
                if (matrix[k][rowmin_col] > rowmin_el){
                    flag = true;
                    break;
                }
            }
            if (!flag) res.push_back(rowmin_el);
        }
        return res;
    }
};
// @lc code=end

