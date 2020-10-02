#include<iostream>
using namespace std;

// 两个整数位数分别保证不超过1000000, 输出两个正整数的和

// 输入：char的输入
// push_back() 用栈更好

// 定义char的加法

// 计算按照最后一位（链表的第 0 个元素开始加），满10进1。
// 容易知道，这个进位最多只会加1.

// 倒序输出

// 列表抽象类:使用 char 类
class list {
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const char& x) = 0;
	//virtual void remove(int i) = 0; 不需要删除
	//virtual int search(const char &x) const = 0; 不需要搜索
	virtual char visit(int i)const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

// 单链表
class sLinkListBigInt : public list {
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
	char visit(int i) const {//访问 返回整数
		return (move(i)->data);
	}

	void traverse() const {  //遍历
		node* p = head;
		for (int i = 1; i <= length(); ++i) {
			p = p->next;
			cout << p->data;
		}
		cout << endl;
	}

	void reverse() { //转置 不使用
		node* p, * q;
		p = head->next; head->next = NULL;
		while (p) {
			q = p->next;
			p->next = head->next;
			head->next = p;
			p = q;
		}
	}
};

// int operator+ (const char &b){
//     int Add1=(int)this - (int)'0';
//     int Add2=(int)b - (int)'0';
//     return (Add1+Add2);
// }

int main() {
	//输入
	sLinkListBigInt* BigInt1 = new sLinkListBigInt();
	sLinkListBigInt* BigInt2 = new sLinkListBigInt();

	//输出
	sLinkListBigInt* BigIntAns = new sLinkListBigInt();

	char tmp;
	//int i = 0;
	while (true) {
		cin.get(tmp);
		if (tmp != '\n') {
			BigInt1->insert(1, tmp);
		}
		else {
			break;
		}
	}

	//i = 0;
	while (true) {
		cin.get(tmp);
		if (tmp != '\n') {
			BigInt2->insert(1, tmp);
		}
		else {
			break;
		}
	}

	//转置
	//BigInt1->reverse();
	//BigInt2->reverse();

	//BigInt1->traverse();
	//BigInt2->traverse();

	int next_tmp = 0; //进位预留
	if (BigInt1->length() > BigInt2->length()) {
		for (i = BigInt2->length() + 1; i <= BigInt1->length(); ++i) {
			BigInt2->insert(i, (char)'0');
		}
	}
	else if (BigInt1->length() < BigInt2->length()) {
		for (i = BigInt1->length() + 1; i <= BigInt2->length(); ++i) {
			BigInt1->insert(i, (char)'0');
		}
	}
	for (i=1;i<=BigInt1->length();++i){
	//for (i = BigInt1->length(); i >= 1; --i) {
		next_tmp += ((int)(BigInt1->visit(i) - '0')
			+ (int)(BigInt2->visit(i) - '0'));
		BigIntAns->insert(i, (char)((next_tmp % 10) + '0'));
		next_tmp = next_tmp / 10;
		//BigIntAns->traverse();
	}
	if (next_tmp > 0) {
		BigIntAns->insert(i, (char)(next_tmp + '0'));
		next_tmp = 0;
	}

	BigIntAns->reverse();

	BigIntAns->traverse();

	return 0;
}