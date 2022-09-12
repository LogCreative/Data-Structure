/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> digitmap = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        if (digits.length() == 0) return {};
        vector<string> ans = {""}, tmpans;
        string tmpstr;
        for (char d : digits) {
            tmpstr = digitmap[d - '0'];
            tmpans.clear();
            for (char c : tmpstr) {
                for (string s : ans) {
                    tmpans.push_back(s + c);
                }
            }
            ans = tmpans;
        }
        return ans;
    }
};
// @lc code=end

