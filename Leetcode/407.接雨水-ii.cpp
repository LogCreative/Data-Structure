/*
 * @lc app=leetcode.cn id=407 lang=cpp
 *
 * [407] 接雨水 II
 */

#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

// @lc code=start
class Solution {
    int m;
    int n;

    int isIllegal(int i, int j){
        if (i < 0 || i > m - 1 || j < 0 || j > n - 1)
            return 1;
        return 0;
    }

    int isInvalid(int i, int j){
        if (i <= 0 || i >= m - 1 || j <= 0 || j >= n - 1)
            return 1;
        return 0;
    }
public:
    int trapRainWaterOriginal(vector<vector<int>>& heightMap) {
        // TLE
        // ^ ^ ^
        // ^ . ^
        // ^ ^ ^
        // 边上的会漏水，碰到边缘就作废。
        // “洼地”？
        // 区域四周都是高地。

        m = heightMap.size();
        n = heightMap[0].size();

        int volume = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                stack<pair<int,int>> visiting;
                visiting.push({i,j});
                int invalid = 0;
                int minHeight = INT_MAX;
                int maxHeight = 0;
                int wallHeight = INT_MAX;
                stack<pair<int,int>> pond;

                while(!visiting.empty()){
                    pair<int,int> cur = visiting.top();
                    visiting.pop();
                    visited[cur.first][cur.second] = true;
                    invalid += isInvalid(cur.first, cur.second);
                    if(invalid) break;

                    int curHeight = heightMap[cur.first][cur.second];
                    minHeight = min(minHeight, curHeight);
                    maxHeight = max(maxHeight, curHeight);
                    pond.push(cur);
                    
                    vector<pair<int,int>> candidates({
                        {cur.first-1, cur.second},
                        {cur.first+1, cur.second},
                        {cur.first, cur.second-1},
                        {cur.first, cur.second+1}});
                    for (auto candidate : candidates){
                        if (isIllegal(candidate.first, candidate.second)) continue;
                        int candHeight = heightMap[candidate.first][candidate.second];
                        if (candHeight <= maxHeight){
                            if (!visited[candidate.first][candidate.second])
                                visiting.push({candidate.first, candidate.second});
                        } else wallHeight = min(wallHeight, candHeight);
                    }
                }
                if (!invalid){
                    while(!pond.empty()){
                        auto pos = pond.top();
                        volume += wallHeight - heightMap[pos.first][pos.second];
                        heightMap[pos.first][pos.second] = wallHeight;
                        pond.pop();
                    }
                }
            }
        }

        return volume;
    }


    int trapRainWater(vector<vector<int>>& heightMap) {
        // 以边界为突破口即可。局部突破即可。
        m = heightMap.size();
        n = heightMap[0].size();
        int volume = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int,pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq;
        
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (isInvalid(i,j)){
                    pq.push({heightMap[i][j], {i, j}});
                    visited[i][j] = true;
                }
            }
        }

        while(!pq.empty()){
            auto cur = pq.top();
            int curHeight = cur.first;
            pair<int,int> curPos = cur.second;
            pq.pop();

            vector<pair<int,int>> candidates({
                        {curPos.first-1, curPos.second},
                        {curPos.first+1, curPos.second},
                        {curPos.first, curPos.second-1},
                        {curPos.first, curPos.second+1}});
            for (auto candidate : candidates){
                if (isIllegal(candidate.first, candidate.second)) continue;
                if (!visited[candidate.first][candidate.second]){
                    int candHeight = heightMap[candidate.first][candidate.second];
                    if (candHeight < curHeight)
                        volume += curHeight - candHeight;
                    visited[candidate.first][candidate.second] = true;
                    pq.push({max(candHeight, curHeight),{candidate.first, candidate.second}});
                }
            }
        }

        return volume;

    }
};
// @lc code=end

int main(){
    Solution s;
    vector<vector<int>> heightMap({{12,13,1,12},{13,4,13,12},{13,8,10,12},{12,13,12,12},{13,13,13,13}});
    cout << s.trapRainWater(heightMap);
    return 0;
}

// [[12,13,1 ,12],
//  [13,4 ,13,12],
//  [13,8 ,10,12],
//  [12,13,12,12],
//  [13,13,13,13]]