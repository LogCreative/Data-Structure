/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        int l = INT32_MAX;
        int tmpl;
        for (int i = 0; i < n; ++i) {
            tmpl = strs[i].length();
            if (tmpl < l) l = tmpl;
        }
        string ans;
        char c;
        for (int k = 0; k < l; ++k) {
            c = strs[0][k];
            for (int i = 1; i < n; ++i)
                if (strs[i][k] != c) return ans;
            ans.push_back(c);
        }
        return ans;
    }
};
// @lc code=end

