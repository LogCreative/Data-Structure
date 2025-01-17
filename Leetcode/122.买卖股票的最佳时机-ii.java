/*
 * @lc app=leetcode.cn id=122 lang=java
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
class Solution {
    public int maxProfit(int[] prices) {
        // 不用模拟交易过程，只考虑贡献
        int ans = 0;
        for (int i = 1; i < prices.length; ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) {
                ans += diff;
            }
        }
        return ans;
    }
}
// @lc code=end

