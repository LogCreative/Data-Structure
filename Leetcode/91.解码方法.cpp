// @before-stub-for-debug-begin
#include <vector>
#include <string>
// #include "commoncppproblem91.h"

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=91 lang=cpp
 *
 * [91] 解码方法
 */

// @lc code=start
class Solution {
public:
    // talk about contribution.
    int numDecodings(string s) {
        int n = s.size();
        if (s[0] == '0'){
            return 0;       // no solution.
        }
        // vector<int> f;
        // f.push_back(1);
        // f.push_back(1);
        int cur = 1; int pre = 1;
        for (int i = 1; i < n; ++i){
            if (s[i] == '0'){
                if (s[i-1] == '1' || s[i-1] == '2'){
                    // f.push_back(f[i-2+1]);
                    int tmp = pre;
                    pre = cur;
                    cur = tmp;
                } else return 0;    // 30 cannot be decoded.
            } else {
                if (s[i-1] == '1' || 
                    (s[i-1] == '2' && s[i] <= '6')){
                        // f.push_back(f[i-1+1]+f[i-2+1]);
                        int tmp = pre + cur;
                        pre = cur;
                        cur = tmp;
                    }
                else {
                    // f.push_back(f[i-1+1]);
                    pre = cur;
                }
            }
        }
        return cur;
    }
};
// @lc code=end
