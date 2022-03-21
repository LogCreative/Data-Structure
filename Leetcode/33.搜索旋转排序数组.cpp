/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    int binarySearch(vector<int>& nums, int left, int right, int target){
        while(left <= right){
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) right = mid - 1;
            else left = mid + 1; 
        }
        return -1;
    }
public:
    int search(vector<int>& nums, int target) {
        // -----_____
        // a   x   b
        // a < x > b
        // a  > x< b
        int left = 0;
        int right = nums.size();
        int mid;
        
        while(left < right){
            mid = left + (right - left) / 2;
            if (nums[mid] > nums[left]) left = mid;
            else right = mid;
        }

        // mid is the end of left part.
        int leftres = binarySearch(nums, 0, mid, target);
        int rightres = binarySearch(nums, mid+1, nums.size() - 1, target);
        if (leftres != -1) return leftres;
        return rightres;
    }
};
// @lc code=end

