/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] Sqrt(x)
 */

#include<iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x, y = -1;
        while(left <= right){
            int mid = (right - left) / 2 + left;
            if ((long long int)mid * mid <= x){
                y = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return y;
    }
};
// @lc code=end

