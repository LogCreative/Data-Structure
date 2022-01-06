/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    vector<vector<char>> board;
    string word;
    vector<vector<bool>> visited;
    int m,n;
    bool dfs(int x, int y, int k){
        if (k==word.size()-1){
            if (word[k]==board[x][y]) return true;
            return false;
        }
        int move[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        for (int l = 0; l < 4; ++l){
            int newx = x + move[l][0];
            int newy = y + move[l][1];
            if (newx >= 0 && newx < m && newy >= 0 && newy < n &&
                !visited[newx][newy] && word[k+1]==board[newx][newy]){
                visited[newx][newy] = true;
                if (dfs(newx,newy,k+1)) return true;
                visited[newx][newy] = false;   // use stack to backtrack.
            }
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& _board, string _word) {
        board = _board;
        word = _word;
        m = _board.size();
        n = _board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n,false));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j){
                if (word[0] == board[i][j]){
                    visited[i][j] = true;
                    if (dfs(i,j,0)) return true;
                    visited[i][j] = false;
                }
            }
        return false;
    }
};
// @lc code=end

