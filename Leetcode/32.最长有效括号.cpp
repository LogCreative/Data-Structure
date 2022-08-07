/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 */

#include<iostream>
#include<string>
#include<stack>
using namespace std;

// @lc code=start
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> pstack;
        pstack.push(-1);
        int ans = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            switch (c)
            {
            case '(':
                pstack.push(i);
                break;
            
            case ')':
                pstack.pop();
                if (pstack.empty()) {
                    pstack.push(i);   
                }
                else {
                    ans = max(ans, i - pstack.top());
                    // ) ( ) )
                    // 1 2 3 4 -> 3 - 1 = 2
                }
                break;
            }
        }
        return ans;
    }
};
// @lc code=end

