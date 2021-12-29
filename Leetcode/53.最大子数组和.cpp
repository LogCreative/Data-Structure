/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // divide and conquer
        int n = nums.size();
        vector<int> f;
        f.push_back(nums[0]);
        int maxf = nums[0];
        for (int i = 1; i < n; ++i){
            // if negative, it cannot be part of the biggest sequence.
            int newf = f[i-1]>0 ? f[i-1]+nums[i] : nums[i];
            f.push_back(newf);
            if (newf > maxf){
                maxf = newf;
            }
        }
        return maxf;
    }
};
// @lc code=end

