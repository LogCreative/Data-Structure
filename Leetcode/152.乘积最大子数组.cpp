/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        //       * nums[j]
        // x[i-1][j-1]  x[i-1][j]
        //                        * nums[i]
        // x[i][j-1]    x[i][j]

        // [x x -2 x x -1 x 0 x x]

        // y[0] = nums[0]
        // y[i] = y[i-1] * nums[i] if y[i-1]>=0 and nums[i]>0
        // or y[i-1]<0 and nums[i]<=0

        // 最小的可以变成最大的
        // nums[i] 可以分割

        int pre_max = nums[0], pre_min = nums[0], ans = nums[0];
        for (int i = 1; i < n; ++i) {
            int mx = pre_max, mn = pre_min;     // Save state.
            pre_max = max(mx * nums[i], max(nums[i], mn * nums[i]));
            pre_min = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(pre_max, ans);
        }
        return ans;
    }
};
// @lc code=end

