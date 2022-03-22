// @before-stub-for-debug-begin
#include <vector>
#include <string>

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=912 lang=cpp
 *
 * [912] 排序数组
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    void percolateDown(vector<int>& nums, int hole, int len){
        int child;
        int tmp = nums[hole];
        for (; hole*2<len-1;hole=child){    //
            child=hole*2+1;                 //
            if (child!=len-1&&nums[child+1]>nums[child])    //
                ++child;
            if (nums[child]>tmp)
                nums[hole]=nums[child];
            else break;
        }
        nums[hole] = tmp;
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        int i;
        int n = nums.size();
        int tmp;
        for (i = n/2 - 1; i >= 0; --i)
            percolateDown(nums, i, nums.size());         // build heap
        for (i = n-1; i>0; --i){
            swap(nums[0], nums[i]);
            percolateDown(nums, 0, i);
        }

        return nums;
    }
};
// @lc code=end

int main(){
    Solution s;
    auto arr = s.sortArray({5,2,3,1});
}