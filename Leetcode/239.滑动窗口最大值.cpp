/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int,int>> pq;       // cannot use set to replace it
        for (int l = 0; l < k; ++l)
            pq.emplace(nums[l], l);
        vector<int> ans;
        int n = nums.size();
        ans.push_back(pq.top().first);
        for (int i = k; i < n; ++i){
            pq.emplace(nums[i], i);
            while(pq.top().second <= i - k)
                pq.pop();       // ensure remove the left top ones.
            ans.push_back(pq.top().first);
        }
        return ans;
    }
};
// @lc code=end

int main(){
    Solution sol;
    vector<int> arr({1,3,1,2,0,5});
    sol.maxSlidingWindow(arr, 3);
}
