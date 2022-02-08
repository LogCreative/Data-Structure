/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> twoSumBrutal(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            for (int j = i + 1; j < n; ++j){
                if (nums[i] + nums[j] == target)
                    return {i,j};
            }
        }
        return {};
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> hashtable; // O(n)
        for (int i = 0; i < n; ++i){
            auto it = hashtable.find(target - nums[i]);
            if (it!=hashtable.end())    // avoid self and self.
                return {it->second, i};
            hashtable[nums[i]] = i;
        }
        return {};
    }    
};
// @lc code=end

