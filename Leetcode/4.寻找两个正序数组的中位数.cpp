/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        // [ o o o o M . . . . ]
        // O(m+n) is simple, just merge.
        // O(log(m+n)) is hard, requires binary search.

        
        

    }
};
// @lc code=end

