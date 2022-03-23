/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

#include<iostream>
#include<string>
using namespace std;

// @lc code=start
class Solution {
public:
    int myAtoi(string s) {       // 100% time, 70% mem 
        int n = s.length();
        // 1. 读入字符串并丢弃无用的前导空格
        int i = 0;
        while(s[i]==' ') ++i;
        // 2. 检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
        int sign = 1;
        if (s[i] == '-'){
            sign = -1;
            ++i;
        } else if (s[i] == '+') ++i;
        // 3. 读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
        long long int num = 0;
        for(int cnt = 0; cnt < 11 && isdigit(s[i]); ++i){   // MAX 10 digits.
            num = num * 10 + (s[i] - '0');
            if (!(cnt == 0 && s[i] == '0')) ++cnt;
        }
        // 4. 将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
        num = num * sign;
        // 5. 如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −2^31 的整数应该被固定为 −2^31 ，大于 2^31 − 1 的整数应该被固定为 2^31 − 1 。
        const long long int MIN_INT = -1<<31;
        const long long int MAX_INT = (1<<31) - 1;
        if (num > MAX_INT) num = MAX_INT;
        if (num < MIN_INT) num = MIN_INT;
        // 6. 返回整数作为最终结果。
        return num;
    }
};
// @lc code=end

