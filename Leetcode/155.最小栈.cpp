/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

#include<iostream>
#include<stack>
using namespace std;

// @lc code=start
class MinStack {
    stack<int> s;
    stack<int> min_s;
public:
    MinStack() {
        min_s.push(INT_MAX);
    }
    
    void push(int val) {
        s.push(val);
        min_s.push(min(val, min_s.top()));
    }
    
    void pop() {
        s.pop();
        min_s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min_s.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

