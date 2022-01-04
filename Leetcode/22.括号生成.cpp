/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// @lc code=start
class Solution {
    vector<string> res;
    int length;
    void method(int cur, int stack, string prefix){
        if(prefix.size()==length) {res.push_back(prefix); return;}
        if(cur>0) method(cur-1, stack+1, prefix + '(');
        if(stack>0) method(cur, stack-1, prefix + ')');
    }
public:
    vector<string> generateParenthesisRecursive(int n) {
        length = 2*n;
        method(n,0, "");
        return res;
    }

    vector<string> generateParenthesis(int n){
        if (n==0) return {};
        if (n==1) return {"()"};
        vector<vector<string>> dp(n+1);
        dp[0] = {""};
        dp[1] = {"()"};
        for (int i = 2; i <= n; ++i){
            for (int j = 0; j < i; ++j){
                for (string p : dp[j]){
                    for (string q : dp[i-1-j]){
                        string str = "(" + p + ")" + q; // dp 方程
                        dp[i].push_back(str);
                    }
                }
            }
        }
        return dp[n];
    }
};
// @lc code=end

