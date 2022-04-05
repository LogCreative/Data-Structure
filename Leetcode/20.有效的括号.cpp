/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

#include<iostream>
#include<string>
#include<stack>
using namespace std;

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> cstack;
        for (char c : s){
            switch (c)
            {
            case '(': case '[': case '{':
                cstack.push(c);
                break;
            
            case ')':
                if (cstack.empty() || cstack.top() != '(')
                    return false;
                else cstack.pop();
                break;
            
            case ']':
                if (cstack.empty() || cstack.top() != '[')
                    return false;
                else cstack.pop();
                break;
            
            case '}':
                if (cstack.empty() || cstack.top() != '{')
                    return false;
                else cstack.pop();
                break;
            }
        }
        if (!cstack.empty()) return false;
        return true;
    }
};
// @lc code=end

