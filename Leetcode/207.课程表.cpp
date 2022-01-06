/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

#include<iostream>
#include<vector>
using namespace std;

// ()->()->()
// topological sort O(n+m)
// Another method is BFS

// @lc code=start
class Solution {
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;
    void dfs(int node){
        visited[node] = 1;
        for (auto v : edges[node]){
            if (visited[v]==0){
                dfs(v);
                if (!valid) return ;
            }
            else if (visited[v]==1){
                valid = false;
                return ;
            }
        }
        visited[node] = 2;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (auto prepair : prerequisites)
            edges[prepair[1]].push_back(prepair[0]);
        for (int i = 0; i < numCourses && valid; ++i)
            if (!visited[i])
                dfs(i);
        return valid;
    }
};
// @lc code=end

