/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    int divide(vector<int>& a, int low, int high){
        int k = a[low];
        do {
            while(low<high && a[high]<=k) --high;
            if (low<high) {a[low]=a[high];++low;}
            while(low<high && a[low]>=k) ++low;
            if (low<high) {a[high]=a[low]; --high;}
        } while(low!=high);
        a[low] = k;
        return low;
    }

    int divideRand(vector<int>& a, int low, int high){
        int pivot = rand() % (high - low + 1) + low;
        if (pivot != low){
            int tmp = a[low];
            a[low] = a[pivot];
            a[pivot] = tmp;
        }

        return divide(a, low, high);
    }

    void quickSort(vector<int>& a, int low, int high){
        if (low >= high) return;
        int mid = divide(a, low, high);
        quickSort(a,low,mid-1);
        quickSort(a,mid+1,high);
    }

    int search;
    int quickSortDetect(vector<int>& a, int low, int high){
        if (low >= high) return -1;
        int mid = divide(a, low, high);
        if (mid == search - 1) return mid;  // maintain the same position.
        if (quickSortDetect(a,low,mid-1)>=0) return mid;
        if (quickSortDetect(a,mid+1,high)>=0) return mid;
        return -1;
    }

    int quickSortDetectRand(vector<int>& a, int low, int high){
        if (low >= high) return -1;
        int mid = divideRand(a, low, high);
        if (mid == search - 1) return mid;  // maintain the same position.
        if (quickSortDetect(a,low,mid-1)>=0) return mid;
        if (quickSortDetect(a,mid+1,high)>=0) return mid;
        return -1;
    }
public:
    int findKthLargestBubble(vector<int>& nums, int k) {
        // Bubble Sort Baseline O(n^2) 1.3s
        int n = nums.size();
        bool flag = true;
        for (int i = 0; i < n && flag; ++i){
            flag = false;
            for (int j = 1; j < n; ++j){
                if (nums[j]>nums[j-1]){
                    int tmp = nums[j-1];
                    nums[j-1] = nums[j];
                    nums[j] = tmp;
                    flag = true;
                }
            }
        }
        // for (auto it = nums.begin(); it != nums.end(); ++it)
        //     cout << *it << endl;
        return nums[k-1];
    }

    int findKthLargestQuickSort(vector<int>& nums, int k) {
        // Quick Sort O(nlogn) 0.14s
        int n = nums.size();
        quickSort(nums,0,n-1);
        return nums[k-1];
    }

    int findKthLargestReplace(vector<int>& nums, int k) {
        // [3,2,1,5,6,4] k=2
        // _ _ -> 3 _ -> 3 2 -> 3 2 -> 5 3 -> 
        // O(nk) 0.124s
        int n = nums.size();
        vector<int> largestlist(k,-1e5);     // nums[i]>=-1e4
        for (int i = 0; i < n; ++i){
            for (auto it = largestlist.begin(); it != largestlist.end(); ++it){
                if (nums[i]>*it){
                    largestlist.pop_back();
                    largestlist.insert(it, nums[i]);
                    break;
                }
            }
        }
        // for (auto it = largestlist.begin(); it != largestlist.end(); ++it)
        //     cout << *it << endl;
        return largestlist[k-1];
    }

    int findKthLargestDeterminedQuick(vector<int>& nums, int k) {
        // Determined Quick Sort
        // Omega(n^2) 0.06s
        int n = nums.size();
        search = k;
        quickSortDetect(nums, 0, n-1);
        return nums[k-1];
    }

    int findKthLargest(vector<int>& nums, int k) {
        // With Randomized Determined Quick Sort
        // O(n) 0.056s
        int n = nums.size();
        search = k;
        quickSortDetectRand(nums, 0, n-1);
        return nums[k-1];
    }
};
// @lc code=end