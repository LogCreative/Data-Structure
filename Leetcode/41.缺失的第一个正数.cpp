/*
 * @lc app=leetcode.cn id=41 lang=cpp
 *
 * [41] 缺失的第一个正数
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        // // [9, 7, 11, 12]
        // //  

        // // if min = x > 1 then 1
        // // if min = x == 1 then 
        // // step improve the area that include 1's right boundary.

        // int arrmin = INT32_MAX;

        // for (int i = 0; i < n; ++i) {
        //     if (nums[i]<=0) continue;
        //     // Assume all numbers are positive.
        //     if (nums[i] > 0 && nums[i] < arrmin) {
        //         arrmin = nums[i];
        //     }
        // }

        // if (arrmin > 1) return 1;

        // // [1----]  [-----]
        // //        ↑
        // // [  ][][  ] -> [      ] [  ]

        // // ^^^^-^^^1^_
        // // prevmin > 2, then 

        // int left = 1;
        // int right = 1;

        // for (int i = 0; i < n; ++i) {
            
        // }

        // // Another hashing...
        // // The right bound is critical
        // follow the rule with clever alternatives.
        // What has to be done, has to be done.

        for (int i = 0; i < n; ++i) {
            if (nums[i] <= 0) {
                nums[i] = n + 1;
            }
        }

        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
                // keep the absolute since we want the position.
            }
        }

        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0)
                return i + 1;
        }

        return n + 1;

        // swaping is also very attractive.
        // every swap make the element in the correct place.
        // if it is 1~n. The wrong place is the answer.

    }
};
// @lc code=end

