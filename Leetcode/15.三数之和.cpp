/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // If the length is smaller than 3,
        // Then there is no solution.
        if (nums.size()<3) return {};

        // Solutions:
        //  * 0 0 0
        //  * non-zero element will not appear over twice
        //    so the third appearance and later 
        //    should be dropped.
        //  * in order to avoid duplicated solutions,
        //    if the second appearance of the non-zero element
        //    could not be picked up simutanously with 
        //    the first apperance, the second one should be 
        //    dropped as well.
        //  * and the first could always be put a negative one
        //    aside from the all zero solution.
        //  * the other two will be found from the start point
        //    of this negative element.

        // Zero
        // a)   0,   0,   0
        
        // dupNums
        // b) neg  * 2, pos
        // c) neg,  pos * 2

        // diffNums
        // d) neg,   0, pos
        // e) neg, neg, pos
        // f) neg, pos, pos

        // Initialize answer.
        vector<vector<int>> ans;

        // The occurance map.
        map<int,int> occ;

        for(int num : nums)
            if (occ.find(num) != occ.end())
                occ[num]++;
            else occ[num] = 1;

        if (occ[0] >= 3) ans.push_back({0,0,0});    // a)
        
        set<int> negSet;
        set<int> posSet;
        set<int> dupSet;       // without 0
        for(auto it = occ.begin(); it != occ.end(); ++it){
            if (it->first>0) posSet.insert(it->first);
            if (it->first<0) negSet.insert(it->first);
            if (it->first!=0 && it->second >= 2) dupSet.insert(it->first);
        }
        if (negSet.empty() || posSet.empty()) return ans;
        
        for(int dupnum : dupSet){
            int expectedEl = - dupnum * 2;
            if (dupnum < 0){ // b)
                if (posSet.find(expectedEl)!=posSet.end())
                    ans.push_back({dupnum, dupnum, expectedEl});
            }
            else{            // c)
                if (negSet.find(expectedEl)!=negSet.end())
                    ans.push_back({dupnum, dupnum, expectedEl});
            }
        }

        if (occ[0] >= 1){
            for (int negnum : negSet){     // d)
                if (posSet.find(-negnum)!=posSet.end())
                    ans.push_back({negnum, 0, -negnum});
            }
        }

        vector<int> negNums;
        vector<int> posNums;
        negNums.assign(negSet.begin(), negSet.end());
        posNums.assign(posSet.begin(), posSet.end());

        // e)
        for (auto i = negNums.begin(); i != negNums.end(); ++i){
            for (auto j = i + 1; j != negNums.end(); ++j){
                int expectedEl = - *i - *j;
                if (posSet.find(expectedEl)!=posSet.end())
                    ans.push_back({*i, *j, expectedEl});
            }
        }

        // f)
        for (auto i = posNums.begin(); i != posNums.end(); ++i){
            for (auto j = i + 1; j != posNums.end(); ++j){
                int expectedEl = - *i - *j;
                if (negSet.find(expectedEl)!=negSet.end())
                    ans.push_back({*i, *j, expectedEl});
            }
        }

        return ans;

        /*
            Should try out the double-pointer solution.
            sort()
            start from left;
            search in the right range for double pointer
                left and right, shrink the range.
        */

    }
};
// @lc code=end

