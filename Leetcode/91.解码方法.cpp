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
    string str;
    int ans;

    // X Y Z -> X 
    // ^     

    //  12 ->  1 2 ->  1 2 
    // ^        ^          ^
    // 0        0          0
    //                     2
    //          1         12
    //                     2

    int startsfrom(int cur, int pos){
        if (pos == str.length()){
            return 1;   // a solution
        }
        int num = str[pos] - '0';
        if (cur == 0 && num == 0)
            return ;

        if (cur + num <= 26){
            startsfrom(0, pos + 1);
        }
        if (cur == 0)
            startsfrom(num, pos + 1);
        
        // if (cur == 0){
        //     if (num == 0){
        //         // starts at 0, no solution
        //         return ;
        //     }
        //     // single number
        //     // startsfrom(0, pos + 1);
        //     startsfrom(num, pos + 1);
        // } else {
        //     if (cur + num <= 26){
        //         startsfrom(0, pos + 1);
        //     }
        //     // startsfrom(num, pos + 1);
        // }
    }
public:
    int numDecodings(string s) {
        str = s;
        ans = 0;
        startsfrom(0, 0);
        return ans;
    }
};
// @lc code=end
