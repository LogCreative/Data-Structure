/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        int n = s.length();
        vector<string> strs(numRows);
        // 0 1 2 3 4 5 6
        // 0 1 2 3 2 1 0
        // -abs(x - 3) + 3
        int offset = numRows - 1;
        int period = offset * 2;
        for (int i = 0; i < n; ++i)
            strs[-abs(i % period - offset) + offset] += s[i];
        string ans;
        for (string str : strs)
            ans += str;
        return ans;
        // Answer 2
        // string ans;
        // for (int i = 0; i < numRows; ++i) {
        //     for (int j = 0; j + i < n; j += period) {
        //         ans += s[i + j];
        //         if (0 < i && i < numRows - 1 && j + period - i < n)
        //             ans += s[j + period - i];
        //     }
        // }
        // return ans;
    }
};
// @lc code=end

