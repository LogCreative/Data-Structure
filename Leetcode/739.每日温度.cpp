/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;
        int n = temperatures.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i){
            while (!s.empty() && temperatures[i] > temperatures[s.top()]){
                res[s.top()] = i - s.top();
                s.pop();
            } 
            s.push(i);
        }
        return res;
    }
};
// @lc code=end

