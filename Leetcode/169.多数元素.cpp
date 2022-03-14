/*
 * @lc app=leetcode.cn id=169 lang=cpp
 *
 * [169] 多数元素
 */

#include<iostream>
#include<vector>
#include<map>
using namespace std;

// @lc code=start
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // [3, 2, 3]
        // [2,2,1,1,1,2,2]
        // [1,1,1,2,2,2,2]
        // [1,1,3,2,2,2,2]
        // [2,2,2,2,1,1,3]

        // i == ans   +1
        // i == rival -1
        
        // Moore

        int ans;
        int cnt = 0;
        for (int b : nums){
            if (cnt == 0) ans = b;
            if (b == ans) ++cnt;
            else --cnt;
        }
        return ans;
        
    }
};
// @lc code=end

