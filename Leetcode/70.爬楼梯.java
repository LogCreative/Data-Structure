/*
 * @lc app=leetcode.cn id=70 lang=java
 *
 * [70] 爬楼梯
 */

import java.util.HashMap;

// fibonacci

// @lc code=start
class Solution {
    HashMap<Integer, Integer> stairMap = new HashMap<>();

    public int climbStairs(int n) {
        stairMap.put(0, 1);
        stairMap.put(1, 1);
        stairMap.put(2, 2);
        for (int i = 3; i <= n; ++i) {
            stairMap.put(i, stairMap.get(i-1)+stairMap.get(i-2)); // dp
        }
        return stairMap.get(n);
    }
}
// @lc code=end

