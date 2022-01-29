/*
 * @lc app=leetcode.cn id=468 lang=cpp
 *
 * [468] 验证IP地址
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// @lc code=start
class Solution {
    vector<string> split(string s, char spliter){
        vector<string> res;
        string seg = "";
        for (char c : s){
            if (c == spliter){
                res.push_back(seg);
                seg.clear();
            } else seg += c;
        }
        res.push_back(seg); // push back the last element
        return res;
    }

    bool isIPv4(string queryIP){
        vector<string> num_seg = split(queryIP, '.');
        if (num_seg.size()!=4) return false;
        for (string seg : num_seg){
            if (seg.length()==0 ||
                (seg.length()>1 && seg[0]=='0')||
                seg.length()>3)
                return false;
            int seg_num = 0;
            for (char c : seg){
                if (isdigit(c))
                    seg_num = seg_num * 10 + c - '0';
                else return false;  // alphabatic literal
            }
            if (seg_num > 255) return false;
        }
        return true;
    }

    bool isIPv6(string queryIP){
        vector<string> hex_seg = split(queryIP, ':');
        if (hex_seg.size()!=8) return false;
        for (string seg : hex_seg){
            if (seg.length()==0 || seg.length()>=5)
                return false;
            for (char c : seg)
                if (!isxdigit(c))
                    return false;
        }
        return true;
    }
public:
    string validIPAddress(string queryIP) {
        if (queryIP.find('.')!=queryIP.size() && isIPv4(queryIP))
            return "IPv4";
        else if (queryIP.find(':')!=queryIP.size() && isIPv6(queryIP))
            return "IPv6";
        return "Neither";
    }
};
// @lc code=end

