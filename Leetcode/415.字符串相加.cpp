/*
 * @lc app=leetcode.cn id=415 lang=cpp
 *
 * [415] 字符串相加
 */

#include<iostream>
#include<string>
using namespace std;

// @lc code=start
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;
        string ans = "";
        while(i >= 0 || j >= 0 || carry != 0){
            int a = i >= 0 ? num1[i] - '0' : 0;
            int b = j >= 0 ? num2[j] - '0' : 0;
            int digit = a + b + carry;
            carry = digit / 10;
            ans = (char)(digit % 10 + '0') + ans;
            --i;
            --j;
        }
        return ans;
    }
};
// @lc code=end

