// 1205.cpp 
// Ackermann 函数，只要求递归算法。

#include <iostream>

using namespace std;

// A(m,n)=
// n+1,				m=0;
// A(m-1,1)			m>0 && n==0;
// A(m-1,A(m,n-1))	else.

int Ackermann(int m, int n) {
	if (m == 0)
		return n + 1;
	else if (m > 0 && n == 0)
		return Ackermann(m - 1, 1);
	else
		return Ackermann(m - 1, Ackermann(m, n - 1));
}

int main()
{
	int m, n;
	cin >> m >> n;	//0<=n,m<=10

	cout << Ackermann(m, n);

	return 0;
}
