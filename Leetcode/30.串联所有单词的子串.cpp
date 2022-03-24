/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<queue>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // barfoothefoobarman
        // ------
        //    ^-----
        //  ------
        //     ^-----
        // Sliding window with multiple start points.
        int n = s.size();
        int m = words.size();
        int d = words[0].size();

        unordered_map<string, int> wordmap;
        for (string word : words)
            wordmap[word]++;        // maybe multiple times.

        vector<int> ans;
        for (int i = 0; i < d; ++i){
            unordered_map<string, int> tmpmap = wordmap;

            // NO PASS AND LOST MATAINABILITY.
            // queue<string> matched;
            // int subn = 0;
            // string curword = "";
            // int left = i;
            // for (auto it = s.begin() + i; it != s.end(); ++it){
            //     curword += *it;
            //     // cout << curword;
            //     if (++subn == d) {
            //         subn = 0;
            //         // processing the word.
            //         if (tmpmap.find(curword) != tmpmap.end()) {
            //             matched.push(curword);
            //             --tmpmap[curword];
            //             int cursize = matched.size();
            //             if (cursize == m){
            //                 int curcnt = tmpmap[curword];
            //                 if (curcnt == 0){
            //                     ans.push_back(left);
            //                     tmpmap[matched.front()]++;
            //                     matched.pop();
            //                     left += d;
            //                 } else if (curcnt < 0) {
            //                     // overload  == 0
            //                     // --^
            //                     for (int i = 0; i < cursize - 1; ++i){
            //                         string delword = matched.front();
            //                         tmpmap[delword]++;
            //                         matched.pop();
            //                         left += d;  // --
            //                         if (delword == curword) break;
            //                     }
            //                 }
            //             }
            //         } else {
            //             // --- x ->
            //             while(!matched.empty()){
            //                 tmpmap[matched.front()]++;
            //                 matched.pop();
            //                 left += d;  // ---
            //             }
            //             left += d; // x
            //         }
            //         curword = "";
            //     }
            // }
            // while(!matched.empty()){
            //     tmpmap[matched.front()]++;
            //     matched.pop();
            // }

            int subn = 0;
            string tmpstr = "";
            vector<string> wordslices;
            for (auto it = s.begin() + i; it != s.end(); ++it){
                tmpstr += *it;
                if (++subn == d) {
                    subn = 0;
                    // processing the word.
                    wordslices.push_back(tmpstr);
                    tmpstr = "";
                }
            }

            int slicen = wordslices.size();
            for (int j = 0; j < slicen - m + 1; ++j) {
                int k;
                for (k = j; k < j + m; ++k) {
                    string curword = wordslices[k];
                    // cout << curword << " ";
                    if (tmpmap.find(curword) != tmpmap.end() && tmpmap[curword] > 0) --tmpmap[curword];
                    else  break;
                }
                // cout << endl;
                if (k == j + m) ans.push_back(i + j * d);
                tmpmap = wordmap;
            }
        }

        return ans;
    }
};
// @lc code=end

int main(){
    Solution s;
    vector<string> words({"a"});
    s.findSubstring("a",words);
}