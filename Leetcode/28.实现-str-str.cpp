/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 实现 strStr()
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    vector<int> get_next(string t) {
        int n = t.length();
        vector<int> next(n);
        next[0] = -1;
        int j;
        for(int i = 1; i < n; ++i) {
            j = i - 1;
            while(j>=0 && t[next[j]+1]!=t[i]) j = next[j];
            if (j<0) next[i] = -1;
            else next[i] = next[j] + 1;
        }
        return next;
    }
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size();
        int n = needle.size();
        if (n == 0) return 0;
        
        // kmp
        vector<int> next = get_next(needle);
        int i = 0,j = 0;
        while(i < m && j < n) {
            if (needle[j] == haystack[i]) {
                ++i; ++j;
            } else if (j == 0) ++i;
            else j = next[j-1] + 1;
        }

        if (j == n) return i - j;
        else return -1;
    }
};
// @lc code=end

