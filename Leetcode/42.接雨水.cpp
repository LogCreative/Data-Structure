/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        int n = height.size();
        vector<bool> visited(n, false);
        pq.push({height[0], 0});
        visited[0] = true;
        pq.push({height[n-1], n-1});
        visited[n-1] = true;

        int volume = 0;

        while(!pq.empty()){
            auto cur = pq.top();
            int curHeight = cur.first;
            int curPos = cur.second;
            pq.pop();

            vector<int> candidates({curPos-1, curPos+1});
            for (int candidate : candidates) {
                if (candidate >= 0 && candidate < n && !visited[candidate]){
                    int candHeight = height[candidate];
                    if (candHeight < curHeight)
                        volume += curHeight - candHeight;
                    visited[candidate] = true;
                    pq.push({max(candHeight, curHeight), candidate});
                }
            }

        }

        return volume;
    }
};
// @lc code=end

