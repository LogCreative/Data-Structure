/*
 * @lc app=leetcode.cn id=12 lang=cpp
 *
 * [12] 整数转罗马数字
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    string intToRoman(int num) {
        string ans;
        vector<pair<char,int>> romans = {
            {'M',1000}, {'D', 500}, {'C', 100},
            {'L', 50}, {'X', 10}, {'V',5}, {'I',1}};
        int times;
        char input, prev;
        for (int i = 0; i < 7; ++i) {
            times = num / romans[i].second;
            input = romans[i].first;
            prev = ans.back();
            if (times == 4) {
                if (i > 0 && i % 2 == 0) {
                    if (prev == romans[i-1].first) {
                        ans.pop_back();
                        ans.push_back(input);
                        ans.push_back(romans[i-2].first);
                    } else {
                        ans.push_back(input);
                        ans.push_back(romans[i-1].first);
                    }
                }
            } else ans += string(times, input);
            num = num % romans[i].second;
        }
        return ans;
    }
};
// @lc code=end

