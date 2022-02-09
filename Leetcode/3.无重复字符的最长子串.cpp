/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

#include<iostream>
#include<string>
using namespace std;

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Sliding window
        // XXXXOOXXXOO
        int maxLen = 0;  // the maximum length of substring till this element.
        int curLen = 0;  // the length of substring end with this element.
        string curSubstr;
        int n = s.size();
        for (int i = 0; i < n; ++i){
            char c = s[i];
            if (curSubstr.find(c) == -1){
                curSubstr += c;
                if (++curLen>maxLen)
                    maxLen = curLen;
            } else {
                curSubstr.clear();
                curLen = 0;
                for (int j = i - 1; j >= 0; --j){  // must be somewhere else has
                    if (s[j] == c)
                        break;
                    curSubstr += s[j];
                    ++curLen;
                }
                reverse(curSubstr.begin(), curSubstr.end());
                curSubstr += c;
                ++curLen;
            }
        }
        return maxLen;
    }
};
// @lc code=end

