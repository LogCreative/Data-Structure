/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int cur = 0, ans = 0;
        int range, move, m, expected;
        while(cur < n - 1){
            range = nums[cur];
            m = -1;
            if (cur + range >= n - 1) return ++ans;
            for (int i = 1; i <= range; ++i) {
                expected = nums[cur + i] + i;
                if (expected >= m) {
                    move = i;
                    m = expected;
                }
            }
            cur += move;
            ++ans;
        }
        return ans;
    }
};
// @lc code=end

