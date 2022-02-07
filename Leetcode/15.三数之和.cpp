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

        /* neglected */

        // // Since there are duplicated numbers.
        // // The sorting action is required.
        // // O(nlog n)
        // sort(nums.begin(), nums.end());

        // // Tackle with the first solution here ...
        // // TODO: could be improved by binary search.
        // auto zeroFirstPos = find(nums.begin(), nums.end(), 0);
        // vector<int>::iterator zeroLastPos;
        // if (zeroFirstPos != nums.end()){
        //     zeroLastPos = zeroFirstPos;
        //     while(zeroLastPos + 1 != nums.end() && *(zeroLastPos + 1) == 0)
        //         ++zeroLastPos;
        //     if (zeroLastPos - zeroFirstPos >= 2)
        //         ans.push_back({0,0,0});
        //     if (zeroFirstPos == nums.begin() ||  // There is no negative number.
        //         zeroLastPos + 1 == nums.end())   // There is no positive number.
        //         return ans; 
        // }

        // vector<int> diffNums;     // save unique nums
        // vector<int> dupNums;      // has >= 2 appearance
        // int lastElement = -2e5;   // minimum el == -1e5
        // int dupCnt = 0;
        // for (int num : nums){
        //     if (num == lastElement){
        //         if (++dupCnt >= 2) continue;
        //         dupNums.push_back(num);
        //     } else {
        //         dupCnt = 0;
        //         lastElement = num;
        //         diffNums.push_back(num);
        //     }
        // }

        // // After getting...
        // // -4 -3 -3 -2 -2 -2 -1 -1 0 0 1 1 2 2 2 3 
        // // Use O(n) complexity to drop unwanted elements
        // vector<int> filteredNums;
        // int lastElement = -2e5; // the minimum el == -1e5
        // int dupCnt = 0;
        // for (int num : nums){
        //     if (num == lastElement){

        //         if (++dupCnt>=2) continue;
        //     } else {
        //         dupCnt = 0;
        //         lastElement = num;
        //     }
        //     filteredNums.push_back(num);
        // }
        
        // //    -1 -1 0 0 1 1
        // //  zeroLeft^   ^zeroRight
        // auto zeroLeft = filteredNums.end();
        // auto zeroRight = filteredNums.end();
        // for (auto it = nums.begin(); it != nums.end(); ++it){
        //     if (*it < 0) zeroLeft = it;
        //     else if (*it == 0) {
        //         if (*(it - 1) != 0) zeroLeft = it;
        //     }
        //     else {zeroRight = it; break;} 
        // }

        // // the first element is negative.
        // for (auto i = filteredNums.begin(); i != zeroLeft; ++i){
        //     int neg = *i;
        //     auto searchBegin = i + 1;
        //     if (*(i + 1) == neg){
        //         // Try to match the single third number.
        //         int expectedEl = -neg * 2;
        //         for (auto j = zeroRight; j != filteredNums.end(); ++j){
        //             if (*j == expectedEl) {
        //                 ans.push_back({neg, neg, expectedEl});
        //                 break;
        //             }
        //         }
        //         searchBegin++;  // The range start from the next different element.
        //     }
            
        //     // Now the solution could be:
        //     // * neg,   0, pos (if 0 exists.)
        //     if (*zeroLeft == 0){
        //         for (auto j = zeroRight + 1; j != filteredNums.end(); ++j){

        //         }
        //     }
        //     // * neg, neg, pos
        //     // * neg, pos, pos
        // }
    }
};
// @lc code=end

