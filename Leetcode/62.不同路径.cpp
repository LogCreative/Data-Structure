/*
 * @lc app=leetcode.cn id=62 lang=cpp
 *
 * [62] 不同路径
 */

// @lc code=start
class Solution {
public:
    int uniquePaths(int m, int n) {
        m = m - 1;
        n = n - 1;
        // C_{m+n}^m = (m+n)!/(m!n!) = (m+n)(m+n-1)···(n+1)/(m!)
        long long int res = 1;
        int cur = m;
        for(int l = m+n; l > n; --l)
            if (l % cur == 0)
                res *= l / cur--;
            else
                res *= l;
        for(; cur >= 1; --cur)
            res /= cur;
        return res;
    }
};
// @lc code=end

