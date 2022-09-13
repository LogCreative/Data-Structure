/*
 * @lc app=leetcode.cn id=38 lang=cpp
 *
 * [38] 外观数列
 */

#include<iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) return "1";
        string prevstr = countAndSay(n - 1) + '\0';
        char cur = 0;
        int cnt = 0;
        string ans = "";
        for (char c : prevstr) {
            if (cur == c) ++cnt;
            else {
                if (cur != 0) ans += to_string(cnt) + cur;
                cur = c; cnt = 1;
            }
        }
        return ans;
    }
};
// @lc code=end

