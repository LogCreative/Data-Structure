/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    int n;
    vector<bool> visited;
    vector<int> track;
    vector<vector<int>> ans;
    void backtrack(vector<int>& nums){
        if (track.size() == n){
            ans.push_back(track);
            return;
        }
        // 寻找下一个位置
        for (int i = 0; i < n; ++i){
            if (!visited[i]){
                track.push_back(nums[i]);
                visited[i] = true;
                backtrack(nums);
                visited[i] = false;
                track.pop_back();
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        n = nums.size();
        visited.resize(n, false);
        backtrack(nums);

        return ans;
    }
};
// @lc code=end

