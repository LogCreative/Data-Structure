// @before-stub-for-debug-begin
#include<iostream>
#include <vector>
#include <string>

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] 翻转字符串里的单词
 */

// @lc code=start
class Solution {
public:
    string reverseWords(string s) {
        vector<string> str_stack;
        string cur_word = "";
        for (char c : s){
            if (c == ' ') {
                if (cur_word != ""){
                    str_stack.push_back(cur_word);
                    cur_word = "";
                }
            } else {
                cur_word = cur_word + c;
            }
        }
        if (cur_word != "")
            str_stack.push_back(cur_word);
        string new_str = "";
        while(!str_stack.empty()){
            cout << str_stack.back() << ' ';
            new_str = new_str + str_stack.back();
            str_stack.pop_back();
            if (!str_stack.empty())
                new_str = new_str + ' ';
        }
        return new_str;
    }
};
// @lc code=end

