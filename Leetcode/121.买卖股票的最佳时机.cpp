/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // ____/---- DP
        int n = prices.size();
        int maxProfit = 0;
        int minPrice = 1e5;     // maxPrice = 1e4
        
        for (int i = 0; i < n; ++i){
            if (prices[i]<minPrice){
                minPrice = prices[i];
            } else if (prices[i] - minPrice > maxProfit){
                maxProfit = prices[i] - minPrice;
            }
        }

        return maxProfit;
    }
};
// @lc code=end

