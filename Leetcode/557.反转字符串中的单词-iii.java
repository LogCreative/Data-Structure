/*
 * @lc app=leetcode.cn id=557 lang=java
 *
 * [557] 反转字符串中的单词 III
 */

// @lc code=start

class Solution {
    public String reverseWords(String s) {
        char[] arr = s.toCharArray();
        int start = 0;
        for (int i = 0; i < arr.length; ++i) {
            if (arr[i]==' ') {
                reverse(arr, start, i-1);
                start = i+1;
            }
            if (i==arr.length-1){
                reverse(arr, start, i);
            }
        }
        return new String(arr);
    }

    private void reverse(char[] arr, int start, int end) {
        int l = start, r = end;
        while(l<r) {
            char tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
    }
}
// @lc code=end

