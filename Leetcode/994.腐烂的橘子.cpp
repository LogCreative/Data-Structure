/*
 * @lc app=leetcode.cn id=994 lang=cpp
 *
 * [994] 腐烂的橘子
 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// @lc code=start
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<pair<int,int>> rotted;
        int minute = 0;
        int goods = 0;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                int state = grid[i][j];
                if (state == 1) ++goods;
                if (state == 2) rotted.push_back({i,j});
            }
        }

        while(true){
            vector<pair<int,int>> next_rotted;
            for (auto r : rotted) {
                vector<pair<int,int>> candidates({
                    { r.first - 1, r.second },
                    { r.first + 1, r.second },
                    { r.first, r.second - 1 },
                    { r.first, r.second + 1 }
                });
                for (auto c : candidates) {
                    if (c.first >= 0 && c.first < m
                        && c.second >= 0 && c.second < n
                        && grid[c.first][c.second] == 1) {
                            --goods;
                            grid[c.first][c.second] = 2;
                            next_rotted.push_back(c);
                    }
                }
            }
            if (next_rotted.empty()) break;
            rotted = next_rotted;
            ++minute;
        }

        if (goods > 0) return -1;
        return minute;
    }
};
// @lc code=end

