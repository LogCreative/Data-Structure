/*
 * @lc app=leetcode.cn id=554 lang=cpp
 *
 * [554] 砖墙
 */

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// @lc code=start
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        // [1,2,2,1]
        // [3,  1,2]
        // [1,3,2  ]
        // [2,4    ]
        // [3,1,2  ]
        // [1,3,1,1]
        unordered_map<int, int> crack;
        int max_crack = 0;
        int max_num = 0;
        for (auto layer : wall){
            int cur = 0;
            int b = layer.size();
            for (int i = 0; i < b - 1; ++i) {
                cur += layer[i];
                if (++crack[cur] > max_num) {
                    max_crack = cur;
                    max_num = crack[cur];  
                }
            }
        }
        if (max_crack == 0) return wall.size();
        return wall.size() - max_num;
    }
};
// @lc code=end

