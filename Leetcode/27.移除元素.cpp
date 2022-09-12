/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            if (nums[i] != val)
                nums[k++] = nums[i];
        return k;
    }
};
// @lc code=end

