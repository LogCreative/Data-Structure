/*
 * @lc app=leetcode.cn id=316 lang=cpp
 *
 * [316] 去除重复字母
 */

#include<iostream>
#include<stack>
#include<string>
#include<map>
using namespace std;

// @lc code=start
class Solution {
public:
    string removeDuplicateLetters(string s) {
        map<char, int> alph;
        for (char c : s)
            ++alph[c];

        stack<char> st;
        map<char, bool> inStack;
        for (char c : s){
            --alph[c];

            // 出现一次
            if (inStack[c]) continue;

            // cbacdcbc
            //        ^
            //   acdb

            // 字典序最小
            while(!st.empty() && st.top() > c) {
                // 唯一
                if (alph[st.top()] == 0) break;
                inStack[st.top()] = false;
                st.pop();
            }

            st.push(c);
            inStack[c] = true;
        }


        string res = "";
        while(!st.empty()){
            res = st.top() + res;
            st.pop();
        }
        return res;
    }
};
// @lc code=end

