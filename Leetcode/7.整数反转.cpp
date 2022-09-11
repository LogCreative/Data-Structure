/*
 * @lc app=leetcode.cn id=7 lang=cpp
 *
 * [7] 整数反转
 */

#include<iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    int reverse(int x) {
        string numstr = to_string(x);
        int sign = 1;
        if (numstr[0] == '-') {
            sign = -1;
            numstr = numstr.substr(1);
        }
        int n = numstr.length();
        // if (n > 10) return 0;
        string cmpstr;
        int res = 0;
        if (n == 10) {
            if (sign > 0) cmpstr = to_string(INT32_MAX);
            else cmpstr = to_string(INT32_MIN).substr(1);
            bool prev = true;
            int digit, cmpres;
            for (int i = n - 1; i >= 0; --i) {
                cmpres = numstr[i] - cmpstr[n - 1 - i];
                if (prev)
                    if (cmpres > 0) return 0;
                    else if (cmpres < 0) prev = false;
                res = res * 10 + (numstr[i] - '0');
            }
        } else {
            for (int i = n - 1; i >= 0; --i) {
                res = res * 10 + (numstr[i] - '0');
            }
        }
        return sign * res;
    }
};
// @lc code=end

