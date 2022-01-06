
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// This is a backtracing.

class Solution {
    int size;
    vector<vector<string>> res;
    void solveQueens(vector<int> state){
        int k = state.size();
        if (k == size){
            // a solution.
            vector<string> sol;
            for (int i = 0; i < size; ++i){
                string solrow;
                for (int j = 0; j < size; ++j){
                    solrow +=  state[i] == j ? "Q" : ".";
                }
                sol.push_back(solrow);
            }
            res.push_back(sol);
        }
        vector<bool> avail(size, true);         // could be improved by bit op |
        // not in the same row is guaranteed.
        for(int i = 0; i < k; ++i){
            // not in the same col.
            avail[state[i]] = false;
            // not in the same diag => two cases: left and right
            int deltarow = k - i;
            if(state[i] - deltarow >= 0) avail[state[i]-deltarow] = false;
            if(state[i] + deltarow < size) avail[state[i]+deltarow] = false;
        }
        for(int j = 0; j < size; ++j){
            if (avail[j]){
                vector<int> newstate = state;
                newstate.push_back(j);
                solveQueens(newstate);
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        size = n;
        solveQueens({});
        return res;
    }
};