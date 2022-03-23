/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

#include<iostream>
#include<string>
using namespace std;

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        int start = 0, end = 0;
        int curlength = end - start;
        for (int i = 0; i < n; ++i){
            int left1 = i, right1 = i;
            while(left1 >= 0 && right1 < n && s[left1] == s[right1]){
                --left1; ++right1;
            }
            ++left1; --right1;  // compensation.
            if (right1 - left1 > curlength){
                start = left1;
                end = right1;
                curlength = right1 - left1;
            }

            int left2 = i, right2 = i+1;
            while(left2 >= 0 && right2 < n && s[left2] == s[right2]){
                --left2; ++right2;
            }
            ++left2; --right2;  // compensation.
            if (right2 - left2 > curlength){
                start = left2;
                end = right2;
                curlength = right2 - left2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};
// @lc code=end

