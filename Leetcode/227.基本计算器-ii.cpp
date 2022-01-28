/*
 * @lc app=leetcode.cn id=227 lang=cpp
 *
 * [227] 基本计算器 II
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
        int res;
        switch (op)
        {
        case '*':
            res = op1 * op2;
            break;
        case '/':
            res = op1 / op2;
            break;
        case '+':
            res = op1 + op2;
            break;
        case '-':
            res = op1 - op2;
            break;
        }
        numStack.push(res);
    }
public:
    int calculate(string s) {
        int num = 0;
        bool num_flag = false;
        bool op_flag = false;
        for (char c : s){
            if (c == ' ') continue;
            if (c >= '0' && c <= '9'){
                num = num * 10 + (int)(c - '0');
                num_flag = true;
                op_flag = true;
            }
            else {
                if (num_flag){
                    numStack.push(num);
                    num = 0;
                    num_flag = false;
                }       
                // priority here
                // * / is greater than + -
                if (c == '*' || c == '/'){
                    while (!opStack.empty() && 
                        opStack.top() != '+' && 
                        opStack.top() != '-')
                        performOp();
                    opStack.push(c);
                } else if (c == '+' || c == '-'){
                    if(!op_flag) numStack.push(0);
                    while(!opStack.empty())
                        performOp();
                    opStack.push(c);
                }
            }
        }
        if (num_flag) numStack.push(num);
        while(!opStack.empty())
            performOp();
        return numStack.top();
    }
};
// @lc code=end

