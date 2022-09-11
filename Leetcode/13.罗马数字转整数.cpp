/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */

#include<iostream>
#include<map>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        map<char, int> romans = {
            {'M', 0}, {'D', 1}, {'C', 2},
            {'L', 3}, {'X', 4}, {'V',5}, {'I',6} };
        vector<int> nums = {1000, 500, 100, 50, 10, 5, 1};
        int cur, next;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            cur = romans[s[i]];
            if (i + 1 < n) {
                next = romans[s[i+1]];
                if (cur > 0 && cur % 2 == 0 
                    && (next == cur - 1 || next == cur - 2)){
                    ans += nums[next] - nums[cur];
                    ++i;
                } else ans += nums[cur];
            } else ans += nums[cur];
        }
        return ans;
    }
};
// @lc code=end

