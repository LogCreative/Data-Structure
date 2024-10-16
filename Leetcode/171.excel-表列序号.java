/*
 * @lc app=leetcode.cn id=171 lang=java
 *
 * [171] Excel 表列序号
 */

// @lc code=start
class Solution {
    public int titleToNumber(String columnTitle) {
        char[] arr = columnTitle.toCharArray();
        int ans = 0;
        int multipler = 1;
        for (int i = arr.length - 1; i >= 0; --i) {
            ans += (arr[i] - 'A' + 1) * multipler;
            multipler *= 26;
        }
        return ans;
    }
}
// @lc code=end

