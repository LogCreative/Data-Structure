/*
 * @lc app=leetcode.cn id=43 lang=cpp
 *
 * [43] 字符串相乘
 */

#include<iostream>
#include<algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    string multiply(string num1, string num2) {
        if ((num1.length() == 1 && num1[0] == '0') ||
            (num2.length() == 1 && num2[0] == '0')
        ) return "0";

        int n1, n2, offset = 0, carry, midres, lendiff;
        string ans, lineans, tmpans;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        for (char c2 : num2) {
            n2 = c2 - '0';
            lineans.clear();
            carry = 0;
            for (char c1 : num1) {
                n1 = c1 - '0';
                midres = n1 * n2 + carry;
                carry = midres / 10;
                midres = midres % 10;
                lineans.push_back(midres + '0');
            }
            if (carry > 0) lineans.push_back(carry + '0');
            reverse(lineans.begin(), lineans.end());
            lineans += string(offset, '0');
            ++offset;
            // cout << lineans << endl;

            lendiff = lineans.length() - ans.length();
            if (lendiff >= 0)
                ans.insert(0, string(lendiff, '0'));
            else lineans.insert(0, string(-lendiff, '0'));

            carry = 0;
            tmpans.clear();
            for (int i = lineans.length() - 1; i >= 0; --i){
                midres = ans[i] - '0' + lineans[i] - '0' + carry;
                carry = midres / 10;
                midres = midres % 10;
                tmpans.push_back(midres + '0');
            }
            if (carry > 0) tmpans.push_back(carry + '0');
            reverse(tmpans.begin(), tmpans.end());
            ans = tmpans;
        }
        return ans;
    }
};
// @lc code=end

