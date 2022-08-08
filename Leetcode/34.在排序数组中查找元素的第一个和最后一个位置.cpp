/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> ans({-1, -1});
        int left = 0;
        int right = n - 1;
        int mid;

        if (n == 0) return ans; // nums[left] may be not accessable.

        while(left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;  // >= target
        }
        if (nums[left] != target) return ans;
        // Cannot specify left > right
        // [5,7,7,8,8,10]   6
        // left == right, nums[left] == 7
        // may be not the target.
        ans[0] = left;

        // there must be a target. Maybe it is the last one.
        right = n;
        while(left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] <= target)
                left = mid + 1;
            else
                right = mid;
        }
        ans[1] = right - 1; // left == right

        return ans;
    }
};
// @lc code=end

