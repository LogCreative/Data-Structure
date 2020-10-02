// 1021.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// n^2

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int n;
	cin >> n;
    
	int bound[4] = { n,n,-1,0 };	//Record 4 boundaries. R D L U
	int dir[2] = { 1,0 };			//Record the movement direction. X Y
	int pos[2] = { 0,0 };			//Record the current position. x y
	int i, j, k;					//row col, index

	//Dynamic 2-dim matrix.
	int** matrix = new int* [n];
	for (j = 0; j <= n-1; ++j)
		matrix[j] = new int[n];	

	//The first step.
	matrix[0][0] = 1;

	//If it is trival.
	if (n > 1) {
		for (k = 2; k <= n * n; ++k) {	//n*n*(4*3+3)

			//What to do next.
			if (dir[0] == 1) {
				if (pos[0] + dir[0] >= bound[0]) {
					bound[0]--;
					dir[0] = 0; dir[1] = 1;
				}
			}
			else if (dir[1] == 1) {
				if (pos[1] + dir[1] >= bound[1]) {
					bound[1]--;
					dir[1] = 0; dir[0] = -1;
				}
			}
			else if (dir[0] == -1) {
				if (pos[0] + dir[0] <= bound[2]) {
					bound[2]++;
					dir[0] = 0; dir[1] = -1;
				}
			}
			else if (dir[1] == -1) {
				if (pos[1] + dir[1] <= bound[3]) {
					bound[3]++;
					dir[1] = 0; dir[0] = 1;
				}
			}

			//Move.
			pos[0] += dir[0];
			pos[1] += dir[1];

			//Assign number.
			matrix[pos[1]][pos[0]] = k;
		}
	}

	//Output the matrix.
	for (i = 0; i < n; ++i) { //n*n
		for (j = 0; j < n; ++j) {
			cout << setw(6) << matrix[i][j];
		}
		cout << endl;
	}

	//Clean the matrix.
	delete[] matrix;

}