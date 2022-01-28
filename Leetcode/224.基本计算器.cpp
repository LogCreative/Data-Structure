/*
 * @lc app=leetcode.cn id=224 lang=cpp
 *
 * [224] 基本计算器
 */

#include<iostream>
#include<stack>
#include<string>
using namespace std;

// @lc code=start
class Solution {
    stack<int> numStack;
    stack<char> opStack;
    void performOp(){
        char op = opStack.top();
        opStack.pop();
        int op2 = numStack.top();
        numStack.pop();
        int op1 = numStack.top();
        numStack.pop();
        int res = op == '+' ? op1 + op2 : op1 - op2;
        numStack.push(res);
    }
public:
    int calculate(string s) {
        int num = 0;
        bool num_flag = false;
        bool op_flag = false;
        for (char c : s) {
            if (c == ' ') continue;
            if (c >= '0' && c <= '9'){
                num = num * 10 + (int)(c - '0');
                num_flag = true;
            }
            else {
                // The splitter for numbers.
                if (num_flag){
                    numStack.push(num);
                    num = 0;
                    num_flag = false;
                    op_flag = true;
                }
                if (c == '('){
                    opStack.push(c);
                    op_flag = false;
                }
                else if (c == ')'){
                    while(opStack.top()!='(')
                        performOp();
                    opStack.pop(); // pop '('
                    op_flag = true;
                } else if (c == '+' || c == '-'){
                    // how to treat a negative number.
                    if (!op_flag) numStack.push(0);
                    while(!opStack.empty() && opStack.top()!='(')
                        performOp();
                    opStack.push(c);    // no priority difference here.
                }
            }
        }
        if (num_flag) numStack.push(num);
        while (!opStack.empty())
            performOp();
        return numStack.top();
    }
};
// @lc code=end

