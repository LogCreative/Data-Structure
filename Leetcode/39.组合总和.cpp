/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// @lc code=start
class Solution {
    vector<int> arr;
    int n;
    vector<vector<int>> findSolution(int pos, int remain){
        if (pos >= n) return {};
        int pcs = remain / arr[pos];
        vector<vector<int>> sols;
        for (int i = 0; i <= pcs; ++i){
            int new_remain = remain - i * arr[pos];
            vector<vector<int>> subSols;
            if (new_remain == 0) subSols.push_back({});
            else subSols = findSolution(pos+1, remain-i*arr[pos]);
            for (vector<int> subSol : subSols){
                auto canSol = subSol;
                for (int j = 0; j < i; ++j)
                    canSol.push_back(arr[pos]);
                sols.push_back(canSol);
            }
        }
        return sols;
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // 找零钱
        
        // 降序排序
        sort(candidates.rbegin(), candidates.rend());
        arr = candidates;
        n = arr.size();

        return findSolution(0, target);
    }
};
// @lc code=end

