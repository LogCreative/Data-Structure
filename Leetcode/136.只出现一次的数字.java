/*
 * @lc app=leetcode.cn id=136 lang=java
 *
 * [136] 只出现一次的数字
 */

// @lc code=start
class Solution {
    public int singleNumber(int[] nums) {
        // 4 ^ 1 ^ 2 ^ 1 ^ 2 = 4 ^ 1 ^ 1 ^ 2 ^ 2 = 4
        // 异或
        int ans = 0;
        for (int num : nums) {
            ans ^= num;
        }
        return ans;
    }
}
// @lc code=end

