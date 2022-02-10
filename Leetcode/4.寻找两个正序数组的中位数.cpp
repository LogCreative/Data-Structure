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
        // By elimination.

        int k = (m + n) / 2;
        int curk = k;
        int left1 = 0, left2 = 0;
        int kth;
        while(true){

            if (left1 == m) {
                kth = nums2[left2 + (curk == 0 ? 0 : curk - 1)]; 
                left2 += curk;
                break; 
            }
            if (left2 == n) {
                kth = nums1[left1 + (curk == 0 ? 0 : curk - 1)]; 
                left1 += curk;
                break; 
            }
            if (curk == 1) {
                if (nums1[left1]<nums2[left2]){
                    kth = nums1[left1];
                    left1 += 1;
                } else {
                    kth = nums2[left2];
                    left2 += 1;
                }
                break; 
            }
            
            int offset = curk/2 - 1;
            int pivot1 = left1 + offset;
            int pivot2 = left2 + offset;
            if (pivot1 >= m)
                pivot1 = m - 1;
            if (pivot2 >= n)
                pivot2 = n - 1;
            if (nums1[pivot1]<=nums2[pivot2]){
                curk -= pivot1 - left1 + 1;
                left1 = pivot1 + 1;
            }
            else {
                curk -= pivot2 - left2 + 1;
                left2 = pivot2 + 1;
            }
        }
        
        // requires k + 1;
        int kp1;
        if (left1 == m) kp1 = nums2[left2];
        else if (left2 == n) kp1 = nums1[left1];
        else kp1 = min(nums1[left1], nums2[left2]);

        if ((m + n) % 2 == 0){
            return (kth + kp1) / 2.0;
        }

        return kp1;

    }
};
// @lc code=end

