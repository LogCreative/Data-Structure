// 1599 Brackets Stack
// 模拟一个括号栈，其元素是三种括号()、[]、{}。

// 给出长为n的操作序列，按序列要求完成以下几种操作：

// push
// pop（栈空则忽略此操作）
// 输出栈顶元素（栈空则忽略此操作）
// 询问当前括号是否匹配（栈空则认为匹配）

//一般如果数据范围是100万的话需要O(N)的复杂度。

#include<iostream>
using namespace std;

template<class elemType>
class stack {
public:
	virtual bool isEmpty() const = 0;
	virtual void push(const elemType& x) = 0;
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual ~stack() {}
};

template<class elemType>
class seqStack : public stack<elemType> {
private:
	elemType* elem;
	int top_p;
	int maxSize;
	void doubleSpace() {
		elemType* tmp = elem;
		elem = new elemType[2 * maxSize];
		for (int i = 0; i < maxSize; ++i) {
			elem[i] = tmp[i];
		}
		maxSize *= 2;
		delete[] tmp;
	}
	bool CheckMatch(char Symb1, char Symb2) {
		if (Symb1 == '(' && Symb2 == ')' ||
			Symb1 == '[' && Symb2 == ']' ||
			Symb1 == '{' && Symb2 == '}')
			return true;
		else
			return false;
	}

public:
	seqStack(int initSize = 10) {
		elem = new elemType[initSize];
		maxSize = initSize;
		top_p = -1;
	}
	~seqStack() {
		delete[] elem;
	}
	// void BackCopyTo(seqStack<elemType> &st){
	// 	for(int i=top_p;i>=0;--i){
	// 		st.push(elem[i]);
	// 	}
	// }
	bool isEmpty() const {
		return top_p == -1;
	}
	void push(const elemType& x) {
		if (top_p == maxSize - 1)
			doubleSpace();
		elem[++top_p] = x;
	}
	elemType pop() {
		return elem[top_p--];
	}
	elemType top() const {
		return elem[top_p];
	}
	int get_top_p() {
		return top_p;
	}
	int get_maxSize() {
		return maxSize;
	}

	char CheckBalance() {
		if (isEmpty())
			return '1'; //栈空则认为匹配

		if (top_p % 2 == 0)
			return '2';	//奇数串返回为不配对

		char LastChar;

		//Check Bracket Stack
		seqStack<char> c_cst(get_maxSize());

		for (int i = 0; i <= top_p; ++i) {
			LastChar = elem[i];
			if (c_cst.isEmpty()) {
				c_cst.push(LastChar);
			}
			else {
				switch (LastChar)
				{
				case ')':
					if (c_cst.pop() != '(')
						return '2';
					break;
				case ']':
					if (c_cst.pop() != '[')
						return '2';
					break;
				case '}':
					if (c_cst.pop() != '{')
						return '2';
					break;
				default:
					c_cst.push(LastChar);
					break;
				}
			}
		}

		if (!c_cst.isEmpty()) {
			return '2';
		}
		return '1';
	}

	//操作
	char stack_op(int op, char sym = 0) {
		switch (op) {
		case 1:
			push(sym);
			break;
		case 2:
			if (isEmpty())
				break;
			else
				pop(); break;
		case 3:
			if (isEmpty())
				break;
			else
				return top(); break;
		case 4:
			//匹配
			return CheckBalance();
			break;
		default:
			break;
		}
		return 0;
	}


};


int main() {
	int i, n;
	int op;
	char sym;
	cin >> n;     //操作数

	//括号栈
	seqStack<char> b;

	//输出
	char* output = new char[n];

	for (i = 0; i < n; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> sym;
			output[i] = b.stack_op(op, sym);
		}
		else {
			output[i] = b.stack_op(op);
		}
	}

	for (i = 0; i < n; ++i) {
		switch (output[i]) {
		case '1':
			cout << "YES" << endl; break;
		case '2':
			cout << "NO" << endl; break;
		case 0:
			break;
		default:
			cout << output[i] << endl; break;
		}
	}

	delete[] output;

	//system("pause");

	return 0;
}