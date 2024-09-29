/*
 * @lc app=leetcode.cn id=88 lang=java
 *
 * [88] 合并两个有序数组
 */

// @lc code=start
class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        // int[] nums_t = new int[m+n];
        // int cur_m = 0, cur_n = 0, cur_t = 0;
        // while(cur_m < m && cur_n < n) {
        //     if (nums1[cur_m] < nums2[cur_n]) {
        //         nums_t[cur_t] = nums1[cur_m];
        //         cur_m++;
        //         cur_t++;
        //     } else {
        //         nums_t[cur_t] = nums2[cur_n];
        //         cur_n++;
        //         cur_t++;
        //     }
        // }
        // for (int i = cur_m; i < m; ++i) {
        //     nums_t[cur_t] = nums1[i];
        //     cur_t++;
        // }
        // for (int i = cur_n; i < n; ++i) {
        //     nums_t[cur_t] = nums2[i];
        //     cur_t++;
        // }
        // for (int i = 0; i < m+n; ++i) {
        //     nums1[i] = nums_t[i];
        // }

        int cur_m = m-1;
        int cur_n = n-1;
        int cur_t = m+n-1;
        while(cur_m>=0 && cur_n>=0) {
            if (nums1[cur_m]>nums2[cur_n]) {
                nums1[cur_t] = nums1[cur_m];
                cur_m--;
                cur_t--;
            } else {
                nums1[cur_t] = nums2[cur_n];
                cur_n--;
                cur_t--;
            }
        }
        if (cur_m>=0) {
            for (int i = cur_m; i >= 0; --i) {
                nums1[cur_t] = nums1[i];
                cur_t--;
            }
        }
        if (cur_n>=0) {
            for (int i = cur_n; i >= 0; --i) {
                nums1[cur_t] = nums2[i];
                cur_t--;
            }
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {0};
        int[] nums2 = {1};
        sol.merge(nums1, 0, nums2, 0);
    }
}
// @lc code=end

