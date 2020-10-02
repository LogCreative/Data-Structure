// 两个整数位数分别保证不超过1000000, 输出两个正整数的和

// 输入：char的输入

// 定义char的加法

// 计算按照最后一位（链表的第 0 个元素开始加），满10进1。
// 容易知道，这个进位最多只会加1.

// 倒序输出

#include<iostream>
using namespace std;

class list {
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const char& x) = 0;
	//virtual void remove(int i) = 0; 不需要删除
	//virtual int search(const char &x) const = 0; 不需要搜索
	//virtual char visit(int i)const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

// 单链表
class sLinkListBigInt : public list {

	friend sLinkListBigInt operator+(
		sLinkListBigInt & BigInt1,
		sLinkListBigInt & BigInt2) {
		int i;
		int next_tmp = 0; //进位预留

		sLinkListBigInt BigIntAns;

		// Pre-load
		char* BigInt1cha = BigInt1.generate_cha();
		char* BigInt2cha = BigInt2.generate_cha();

		if (BigInt1.length() > BigInt2.length()) {
			for (i = 1; i <= BigInt1.length(); ++i) {
				if (i <= BigInt2.length()) {
					next_tmp += ((int)(BigInt1cha[i - 1] - '0') + (int)(BigInt2cha[i - 1] - '0'));
				}
				else {
					next_tmp += (int)(BigInt1cha[i - 1] - '0');
				}
				
				BigIntAns.insert(i, (char)((next_tmp % 10) + '0'));
				next_tmp = next_tmp / 10;
			}
		}
		else {
			for (i = 1; i <= BigInt2.length(); ++i) {
				if (i <= BigInt1.length()) {
					next_tmp += ((int)(BigInt1cha[i - 1] - '0') + (int)(BigInt2cha[i - 1] - '0'));
				}
				else {
					next_tmp += (int)(BigInt2cha[i - 1] - '0');
				}

				BigIntAns.insert(i, (char)((next_tmp % 10) + '0'));
				next_tmp = next_tmp / 10;
			}

		}

		//最后进位
		if (next_tmp > 0) {
			BigIntAns.insert(i, (char)(next_tmp + '0'));
			next_tmp = 0;
		}

		delete[] BigInt1cha, BigInt2cha;

		return BigIntAns;
	}


private:
	struct node {
		char data;
		node* next;

		node(const char& x, node* n = NULL) { data = x; next = n; }
		node() :next(NULL) {}
		~node() {}
	};

	node* head;
	int currentLength;

	node* move(int i) const {    //移动
		node* p = head;
		while (i-- > 0)
		{
			p = p->next;
		}
		return p;
	}

public:
	sLinkListBigInt() {  //构造
		head = new node;
		currentLength = 0;
	}

	// 复制构造函数
	sLinkListBigInt(sLinkListBigInt const& BigInt2) {
		head = new node;
		currentLength = 0;

		node* p = head;

		char* BigInt2cha = BigInt2.generate_cha();

		for (int i = 1; i <= BigInt2.length(); ++i) {
			p->next = new node(BigInt2cha[i-1]);
			p = p->next;
			++currentLength;
		}

		delete[] BigInt2cha;
	}

	~sLinkListBigInt() { clear(); delete head; }    //析构

	void clear() {       //清除
		node* p = head->next, * q;
		head->next = NULL;
		while (p != NULL) {
			q = p->next;
			delete p;
			p = q;
		}
		currentLength = 0;
	}

	int length() const { return currentLength; }  //长度

	void insert(int i, const char& x) {
		node* pos;

		pos = move(i - 1);
		pos->next = new node(x, pos->next);
		++currentLength;
	}
	//void remove(int i);
	//int search(const char &x) const;
	//char visit(int i) const {//访问 返回整数
	//	return (move(i)->data);
	//}

	void traverse() const {
		int i;
		char* output = new char[length()+1];
		node* p = head;

		for (i = 1; i <= length();++i) {
			output[length()-i] = p->next->data;
			p = p->next;
		}
		output[length()] = '\0';
		cout << output <<'\n';
		delete[] output;
	}

	char* generate_cha() const {
		char* BigIntInt = new char[length()];
		node* p = head;

		for (int i = 0; i < length(); ++i) {
			BigIntInt[i] = (p->next->data);
			p = p->next;
		}
		return BigIntInt;
	}

};

int main() {
	//输入
	sLinkListBigInt BigInt1, BigInt2;

	char tmp;

	while (true) {
		cin.get(tmp);
		if (tmp != '\n') {
			BigInt1.insert(1, tmp);
		}
		else {
			break;
		}
	}

	while (true) {
		cin.get(tmp);
		if (tmp != '\n') {
			BigInt2.insert(1, tmp);
		}
		else {
			break;
		}
	}

	//输出
	sLinkListBigInt BigIntAns = BigInt1 + BigInt2;

	BigIntAns.traverse();

	return 0;
}