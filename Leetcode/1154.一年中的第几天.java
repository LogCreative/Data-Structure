/*
 * @lc app=leetcode.cn id=1154 lang=java
 *
 * [1154] 一年中的第几天
 */

// @lc code=start
class Solution {
    public int dayOfYear(String date) {
        // String[] dates = date.split("-");
        // int year = Integer.parseInt(dates[0]);
        // int month = Integer.parseInt(dates[1]);
        // int day = Integer.parseInt(dates[2]);

        int year = Integer.parseInt(date.substring(0, 4));
        int month = Integer.parseInt(date.substring(5, 7));
        int day = Integer.parseInt(date.substring(8, 10));
        
        int[] numDayOfMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            numDayOfMonth[1] = 29;
        }
        int ans = 0;
        for (int i = 0; i < month - 1; ++i) {
            ans += numDayOfMonth[i];
        }
        ans += day;
        return ans;
    }
}
// @lc code=end

