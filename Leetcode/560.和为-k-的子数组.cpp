/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;

// @lc code=start
class Solution {
public:
    int subarraySumBrutal(vector<int>& nums, int k) {
        // brutal, start with
        int n = nums.size();
        int cnt = 0;
        for (int i = 0; i < n; ++i){
            int sum = 0;
            for (int j = i; j < n; ++j){
                sum += nums[j];
                if (sum == k){
                    ++cnt;
                }
            }
        }
        return cnt;
    }

    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int> sums;
        int sum = 0;
        sums[0] = 1; // [] == 0 => 1
        int ans = 0;
        for (int i = 0; i < n; ++i){
            // end with
            sum += nums[i];
            // sum - ? == k => ? == sum - k
            ans += sums[sum - k];
            ++sums[sum];
        }
        return ans;
    }

    // There are negative numbers.
};
// @lc code=end

