/*
 * @lc app=leetcode.cn id=40 lang=cpp
 *
 * [40] 组合总和 II
 */

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// @lc code=start
class Solution {
    vector<int> candis;
    int n;
    vector<vector<int>> ans;
    void backtrace(vector<int> cur, int begin, int remain) {
        if (remain == 0) {
            ans.push_back(cur);
            return ;
        }
        if (begin == n) return ;
        int num = candis[begin];
        int dupcnt = 0;
        for (int j = begin; j < n; ++j)
            if (candis[j] == num)
                ++dupcnt;
        for (int i = 0; i <= dupcnt; ++i){
            backtrace(cur, begin + dupcnt, remain);
            cur.push_back(num);
            remain -= num;
            if (remain < 0) break;
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        // shrink array range
        for (int x : candidates)
            if (x <= target)
                candis.push_back(x);
        n = candis.size();
        backtrace({}, 0, target);
        return ans;
    }
};
// @lc code=end

