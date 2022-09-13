/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// @lc code=start
class Solution {

public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> mp;
        for (string str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].push_back(str);
        }
        for (auto it = mp.begin(); it != mp.end(); ++it)
            ans.push_back(it->second);
        return ans;
    }
};
// @lc code=end

