/*
 * @lc app=leetcode.cn id=54 lang=java
 *
 * [54] 螺旋矩阵
 */

import java.util.ArrayList;
import java.util.List;

// @lc code=start
class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        int m = matrix.length, n;
        List<Integer> ans = new ArrayList<Integer>();
        if (m > 0) {
            n = matrix[0].length;
            if (n == 0) return ans;
        } else return ans;

        int r = n - 1, d = m - 1, l = 0, u = 0;
        
        while(true) {
            for (int i = l; i <= r; ++i) ans.add(matrix[u][i]);
            if (++u>d) break;
            for (int i = u; i <= d; ++i) ans.add(matrix[i][r]);
            if (--r<l) break;
            for (int i = r; i >= l; --i) ans.add(matrix[d][i]);
            if (--d<u) break;
            for (int i = d; i >= u; --i) ans.add(matrix[i][l]);
            if (++l>r) break;
        }
        return ans;
    }
}
// @lc code=end

