/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // [0 1 2 3 1 2 2 3 3 4]
        //      ^         ^
        // [1 2 2]
        //    ^   ^
        int left = 0;
        int right = 0;
        int n = nums.size();
        while(right != n){
            if (nums[left] == nums[right])
                ++right;
            else
                nums[++left] = nums[right++];
        }
        return ++left;
    }
};
// @lc code=end

