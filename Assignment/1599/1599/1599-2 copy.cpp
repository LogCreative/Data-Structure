// 1599 Brackets Stack
// 模拟一个括号栈，其元素是三种括号()、[]、{}。

// 给出长为n的操作序列，按序列要求完成以下几种操作：

// push
// pop（栈空则忽略此操作）
// 输出栈顶元素（栈空则忽略此操作）
// 询问当前括号是否匹配（栈空则认为匹配）

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
public:
	seqStack(int initSize = 10) {
		elem = new elemType[initSize];
		maxSize = initSize;
		top_p = -1;
	}
	~seqStack() {
		delete[] elem;
	}
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
	int get_maxSize(){
		return maxSize;
	}

};

class balance {
private:
	seqStack<char> cst;

	bool CheckMatch(char Symb1, char Symb2) {
		if (Symb1=='(' && Symb2 == ')' ||
			Symb1=='[' && Symb2 == ']' ||
			Symb1=='{' && Symb2 == '}' )
			return true;
		else
			return false;
	}

public:
	//构造函数
	balance() { }

	char* CheckBalance() {
		if (cst.isEmpty())
			return "YES"; //栈空则认为匹配

		//不使用数组 怀疑有检测
		//char* tmp = new char[length];

		//结果
		//char result=NULL;

		char LastChar, Match;
		//反向读取栈 Back Stack
		seqStack<char> b_cst(cst.get_maxSize()),b2_cst(cst.get_maxSize());	//分配一步到位
		while (!cst.isEmpty()){
			LastChar=cst.pop();
			b_cst.push(LastChar);
			b2_cst.push(LastChar);
		}

		while (!b2_cst.isEmpty())
			cst.push(b2_cst.pop());		//推入原栈

		//检测栈 Check Stack
		seqStack<char> c_cst(cst.get_maxSize());	//分配一步到位

		while (!b_cst.isEmpty()) {
			LastChar = b_cst.pop();

				switch (LastChar)
				{
					//如果是开括号，进栈
				case '(': case '[': case '{':
					c_cst.push(LastChar);
					break;
					//如果是闭括号
				case ')': case ']': case '}':
					if (c_cst.isEmpty()) {
						//如果是空
						return "NO";
					}
					else {
						//查看最近的括号
						Match = c_cst.pop();
						if (!CheckMatch(Match, LastChar)) {
							return "NO";
						}
						break;
					}
				default:
					break;
				}

		}

			if (!c_cst.isEmpty()) {
				return "NO";
			}
			else {
				return "YES";
			}
	}

	//操作
	char* stack_op(int op, char sym = 0) {
		switch (op) {
		case 1:
			cst.push(sym);
			break;
		case 2:
			if (cst.isEmpty())
				break;
			else
				cst.pop(); break;
		case 3:
			if (cst.isEmpty())
				break;
			else
				return (char*)cst.top(); break;
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
	balance b;

	//输出
	char** output = new char*[n];
	for (i=0;i<n;++i){
		output[i]=new char[4];
	}

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
		if (output[i]!=0)
		cout<<output[i]<<endl;
	}

	//仍然不正确

	//system("pause");

	return 0;
}