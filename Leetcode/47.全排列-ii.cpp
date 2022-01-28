/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

#include<iostream>
#include<vector>
#include<set>
using namespace std;

// @lc code=start
class Solution {
    vector<vector<int>> res;
    void permutation(vector<int> nums, int n, int cur){
        if (cur == n){
            res.push_back(nums);
            return ;
        }
        set<int> visited;
        permutation(nums, n, cur+1);
        for (int i = cur+1; i < n; ++i){
            if (nums[cur] != nums[i] 
                && visited.find(nums[i]) == visited.end()){
                visited.insert(nums[i]);
                swap(nums[cur], nums[i]);
                permutation(nums, n, cur+1);
                swap(nums[cur], nums[i]);
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // -10 , 10
        // 个数 2^n / \prod i!
        int n = nums.size();
        permutation(nums, n, 0);
        return res;
    }
};
// @lc code=end

