/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // _ ^ _ (strict)
        // nums[-1] = nums[n] = -inf
        // O(log n) ? binary search.
        
        //   _ _ _
        // a.1 2 [3] up
        // b.1 [3] 2 correct
        // c.(2) 1 [3] anti-peak
        // d.[3] 2 1 down

        // no return, so you can eliminate half.
        int n = nums.size();
        int left = 0, right = n - 1;
        while(left <= right){
            int mid = (left + right) / 2;
            bool go_right = mid - 1 == -1 || nums[mid] > nums[mid - 1];
            bool go_left = mid + 1 == n || nums[mid] > nums[mid + 1];
            if (go_left && go_right)
                return mid;
            if (go_left) right = mid - 1;
            else left = mid + 1;
        }
        return -1;
    }
};
// @lc code=end

