/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] 回文数
 */

#include<iostream>
#include<stack>
using namespace std;

// @lc code=start
class Solution {
public:
    bool isPalindrome(int x) {
        // // Using string
        // string numstr = to_string(x);
        // int n = numstr.length();
        // for (int i = 0; i < n; ++i) {
        //     if (numstr[i] != numstr[n - 1 - i])
        //         return false;
        // }
        // return true;

        // No String
        // x = rev(x)
        // sum k * 10^i = sum k * 10^{n-i}
        if (x < 0) return false;
        int tmp = x;
        long long int y = 0;
        while(x) {
            y = y * 10 + x % 10;
            x /= 10;
        }
        return y == tmp;
    }
};
// @lc code=end

