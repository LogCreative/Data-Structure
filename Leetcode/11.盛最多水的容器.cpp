/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1;
        int area = 0;
        while (left < right)
        {
            area = max(area, min(height[left], height[right]) * (right - left));
            if (height[left] > height[right]) --right;  // 消去状态
            else ++left;
        }
        return area;
    }
};
// @lc code=end

