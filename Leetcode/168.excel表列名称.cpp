/*
 * @lc app=leetcode.cn id=168 lang=cpp
 *
 * [168] Excel表列名称
 */

#include<iostream>
#include<string>
using namespace std;

// @lc code=start
class Solution {
public:
    string convertToTitle(int columnNumber) {

        // A -> 1
        // B -> 2
        // ...
        // Z -> 26
        // AA -> 1,1 = 26 + 1 = 27
        // AB -> 1,2 = 26 + 2 = 28
        // AZ -> 1,26 = 26 + 26
        // BA -> 2,1 = 26 * 2 + 1
        // ZZ -> 26,26 = 26 * 26 + 26 = 26 * 27 = 702
        // AAA -> 1,1,1 = 26 * 26 + 26 + 1
        // ZZZ -> 26,26,26 = 26 * 26 * 26 + 26 * 26 + 26 = 
        // AAAA -> 1,1,1,1 = 26 * 26 * 26 + 26 * 26 + 26 + 1 = 

        // 1, 26 + 1, 26 * 26 + 26 + 1, 26 * 26 * 26 + 26 * 26 + 26 + 1
        // 0, 26, 26 * 26 + 26, ...

        // 26 进制
        // 确定最高位数
        --columnNumber;
        long long int cur = 0;
        long long int tail = 1;
        while(columnNumber >= cur){
            tail *= 26;
            cur += tail;
        }
        cur -= tail;
        tail /= 26;
        string res = "";
        while(tail > 1){
            int offset = columnNumber / tail;
            res += (char)('A' + offset - 1);
            columnNumber -= offset * tail;
            tail /= 26;
        }
        res += 'A' + columnNumber;
        return res;

        // could be better by 26 every time - 1
    }
};
// @lc code=end

