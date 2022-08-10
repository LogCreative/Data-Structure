/*
 * @lc app=leetcode.cn id=93 lang=cpp
 *
 * [93] 复原 IP 地址
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// @lc code=start
class Solution {
    int n;
    string ips;
    vector<string> res;

    bool isthreevalid(int pos) {
        int nextnum = (ips[pos] - '0') * 100 + (ips[pos + 1] - '0') * 10 + (ips[pos + 2] - '0');
        return nextnum <= 255;
    }

    // 1234 pos = 0, n = 4

    void backtrace(string curstr, int pos, int curdot) {
        if (curdot == 3) {
            if (n - pos > 3 || n - pos == 0) return ;
            if (n - pos == 3 && !isthreevalid(pos)) return ;
            if (n - pos > 1 && ips[pos] == '0') return ;
            // 1 ~ 2 3 valid
            while(pos < n) curstr.push_back(ips[pos++]);
            res.push_back(curstr);
            return ;
        }
        // 0 ~ 255
        if (n - pos > 0) {
            curstr.push_back(ips[pos]);
            backtrace(curstr + '.', pos + 1, curdot + 1);
            if (ips[pos] == '0') return ; // can not start with 0
        }
        if (n - pos > 1) {
            curstr.push_back(ips[pos + 1]);
            backtrace(curstr + '.', pos + 2, curdot + 1);
        }
        if (n - pos > 2 && isthreevalid(pos)) {
            curstr.push_back(ips[pos + 2]);
            backtrace(curstr + '.', pos + 3, curdot + 1);
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        n = s.size();
        ips = s;
        backtrace("", 0, 0);
        return res;
    }
};
// @lc code=end

