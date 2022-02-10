/*
 * @lc app=leetcode.cn id=240 lang=cpp
 *
 * [240] 搜索二维矩阵 II
 */

#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
    // vector<vector<int>> mat;
    int m,n;

    // // Using an array for the sake of data neighboring.
    // int binarySearchLowerBound(vector<int>& array, int target){
    //     int left = 0, right = array.size() - 1, res = -1;
    //     while(left <= right){
    //         int mid = (left + right) / 2;
    //         if (array[mid] <= target) {
    //             res = mid;
    //             left = mid + 1;
    //         } else {
    //             right = mid - 1;
    //         }
    //     }
    //     return res;
    // }

    // // Shrink the range by binary Search.
    // bool searchSubMatrix(int topRow, int bottomRow, int leftCol, int rightCol, int target){
    //     // invalid: if the submatrix is illegal.
    //     if (topRow > bottomRow || leftCol > rightCol) return false;

    //     // topRow and leftCol will be regarded as the offset.
        
    //     // Shrink the range of row first.
    //     int rowSliceLen = bottomRow - topRow + 1;
    //     vector<int> rowSearch(rowSliceLen);
    //     for (int i = 0; i < rowSliceLen ; ++i)
    //         rowSearch[i] = mat[topRow + i][leftCol];
    //     int newbottomRow = binarySearchLowerBound(rowSearch, target);
    //     if (newbottomRow == -1) return false;
    //     newbottomRow += topRow;     // Row offset.
    //     if (mat[newbottomRow][leftCol] == target) return true;

    //     // Shrink the range of column next.
    //     int colSliceLen = rightCol - leftCol + 1;
    //     vector<int> columnSearch(colSliceLen);
    //     for (int j = 0; j < colSliceLen; ++j)
    //         columnSearch[j] = mat[topRow][leftCol + j];
    //     int newRightCol = binarySearchLowerBound(columnSearch, target);
    //     if (newRightCol == -1) return false;
    //     newRightCol += leftCol;     // Column offset.
    //     if (mat[topRow][newRightCol] == target) return true;

    //     // Otherwise the first Column and the first Row has been examined.
    //     // Search the submatrix by shrinking the range of 1.
    //     return searchSubMatrix(topRow + 1, newbottomRow, leftCol + 1, newRightCol, target);
    // }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        
        /* TLE 1 */
        // // Shrink the range first.
        // // select the range of columns.
        // // which will reveal the first column >= target.
        // int rightColumn = binarySearchLowerBound(matrix[0],target);

        // // select the range of rows.
        // vector<int> rowFirst(m);
        // for (int i = 0; i < m; ++i)
        //     rowFirst[i] = matrix[i][0];
        // int bottomRow = binarySearchLowerBound(rowFirst, target);

        // for (int i = 0; i <= bottomRow; ++i){
        //     for (int j = 0; j <= rightColumn; ++j){
        //         if (matrix[i][j] == target)
        //             return true;
        //     }
        // }

        // return false;

        /* TLE 2 */
        // mat = matrix;
        // return searchSubMatrix(0, m - 1, 0, n - 1, target);

        /* We should start from the right upper corner.
           And reduce the size for either row or column
           so that every time we only need to search O(1)
           instead of O(max(m,n)) from TLE 2.
         */
        int x = 0, y = n - 1;
        // matrix[x][y] > target, this column is deleted.
        // matrix[x][y] < target, this row is deleted.
        while(x <= m - 1 && y >= 0){
            int element = matrix[x][y];
            if (element == target) return true;
            if (element > target) --y;
            else ++x;
        }

        return false;

    }
};
// @lc code=end

