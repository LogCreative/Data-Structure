/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// word1 -> word2
// gap -> 1 (insert, delete)
// misalign -> 1 (replace)
// match -> 0

// @lc code=start
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size();
        int n2 = word2.size();
        vector<vector<int>> dp(n2+1, vector<int>(n1+1,0));
        for (int i = 1; i <= n2; ++i) dp[i][0] = i; //
        for (int j = 1; j <= n1; ++j) dp[0][j] = j; //
        for (int i = 1; i <= n2; ++i)
            for (int j = 1; j <= n1; ++j)
                dp[i][j] = min(min(dp[i-1][j]+1, 
                            dp[i][j-1]+1), 
                            dp[i-1][j-1]+(word2[i-1]==word1[j-1]?0:1));
        return dp[n2][n1];
    }
};
// @lc code=end

