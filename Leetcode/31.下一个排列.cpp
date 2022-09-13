/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        int i,j;
        for (j = n - 1; j >= 1; --j)
            if (nums[j-1] < nums[j])
                break;
        if (j > 0){
            //  /\_ .
            // /
            for (i = n - 1; i >= j; --i)
                if (nums[i] > nums[j-1])
                    break;
            // nums[i] > nums[j-1] < nums[j]
            // nums[i-1] > nums[i] > nums[i+1]
            // 
            swap(nums[i],nums[j-1]); // next permutation
        }
        reverse(nums.begin() + j, nums.end());
    }
};
// @lc code=end

