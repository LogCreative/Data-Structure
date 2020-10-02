// 1203.cpp 

#include <iostream>
#include <cstring>

using namespace std;

template<class elemType>
class list {
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const elemType& x) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const elemType &x) const = 0;
	virtual elemType visit(int i)const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

// 这里我使用单链表 从1开始计数。
template<class elemType>
class sLinkList : public list<elemType> {

	// + 运算符重载
	friend sLinkList<elemType> operator+ (
		const sLinkList<elemType>&sllA,
		const sLinkList<elemType>&sllB
		) {
		sLinkList<elemType> sllAns;

		for (int i = 1; i <= sllA.length(); ++i)
			sllAns.insert(i, sllA.visit(i));

		for (int i = 1; i <= sllB.length(); ++i)
			sllAns.insert(i + sllA.length(), sllB.visit(i));

		return sllAns;
	}

private:
	struct node {
		elemType data;
		node* next;

		node(const elemType& x, node* n = NULL) { data = x; next = n; }
		node() :next(NULL) {}
		~node() {}
	};

	node* head;
	int currentLength;
	
	// 移动
	node* move(int i) const {
		node* p = head;
		while (i-- > 0)
		{
			p = p->next;
		}
		return p;
	}
public:
	// 构造函数
	sLinkList<elemType>() {  //构造
		head = new node;
		currentLength = 0;
	}

	// 复制构造函数
	sLinkList<elemType>(sLinkList<elemType> const &sllB) { 
		head = new node;
		currentLength = 0;

		node* p = head;
		for (int i = 1; i <= sllB.length(); ++i) {
			p->next = new node(sllB.visit(i));
			p = p->next;
			++currentLength;
		}
	}

	// 析构
	~sLinkList<elemType>() { clear(); delete head; }    

	// 清除
	void clear() {
		node* p = head->next, * q;
		head->next = NULL;
		while (p != NULL) {
			q = p->next;
			delete p;
			p = q;
		}
		currentLength = 0;
	}

	// 长度
	int length() const { return currentLength; }  

	// 插入
	void insert(int i, const elemType& x) {
		node* pos;

		pos = move(i - 1);
		pos->next = new node(x, pos->next);
		++currentLength;
	}

	// 移除
	void remove(int i) {			
		node* pos, * tmp;
		pos = move(i - 1);
		tmp = pos->next;
		pos->next = pos->next->next;
		delete tmp;
		--currentLength;
	}

	// 搜索
	int search(const elemType& x) const {	
		node* p = head->next;
		int i;
		for (i = 1; i <= currentLength; ++i) {
			if (p->data == x) {
				return i;
			}
			else {
				p = p->next;
			}
		}
		return -1;
	}

	// 访问
	elemType visit(int i) const {
		return (move(i)->data);
	}

	// 遍历
	void traverse() const {  
		node* p = head;
		for (int i = 1; i <= length(); ++i) {
			p = p->next;
			cout << p->data << ' ';
		}
		cout << endl;
	}
};

//template<class elemType>
//sLinkList<elemType> operator+(sLinkList<elemType> &sllB) {
//	// 构造新线性链表
//	sLinkList<elemType>* sllAns = new sLinkList<elemType>(sllB);	
//
//	for (int i = 1; i <= sllB->length(); ++i)
//		sllAns->insert(i + this->length(), sllB->visit(i));
//
//	return sllAns;
//}

//template<class elemType>
//sLinkList<elemType> operator+(
//	const sLinkList<elemType>&sllA, 
//	const sLinkList<elemType>&sllB)
//{
//	sLinkList<elemType> sllAns = new sLinkList<elemType>();
//
//	for (int i = 1; i <= sllA->length(); ++i)
//		sllAns->insert(i, sllA->visit(i));
//
//	for (int i = 1; i <= this->length(); ++i)
//		sllAns->insert(i + sllA->length(), sllB->visit(i));
//
//	return sllAns;
//}

//template<class elemType>
//sLinkList<elemType>* operator+(
//	//const sLinkList<elemType> *sllA,
//	const sLinkList<elemType> sllB) 
//{
//	// 构造新线性链表
//	sLinkList<elemType>* sllAns = new sLinkList<elemType>(this);
//
//	//for (int i = 1; i <= sllA->length(); ++i)
//	//	sllAns->insert(i, sllA->visit(i));
//
//	for (int i = 1; i <= this->length(); ++i)
//		sllAns->insert(i + sllA->length(), sllB->visit(i));
//
//	return sllAns;
//}

template<class elemType>
void Input_Plus() {
	sLinkList<elemType> sllA, sllB;

	int n, m;
	cin >> n >> m;			//包括两个正整数n,m. (1<=n,m<=10000)

	int i; elemType tmp;
	for (i = 1; i <= n; ++i) {
		cin >> tmp;
		sllA.insert(i, tmp);
	}

	for (i = 1; i <= m; ++i) {
		cin >> tmp;
		sllB.insert(i, tmp);
	}

	sLinkList<elemType> Ans = sllA + sllB;	//使用了重载运算符

	Ans.traverse();
}

int main()
{
	char type[7] = { 0 };
	cin.getline(type,7);	//int、char、double

	// 定义两个线性表
	if (strcmp(type,(char*)"int")==0)
		Input_Plus<int>();
	else if (strcmp(type, (char*)"char")==0)
		Input_Plus<char>();
	else if (strcmp(type, (char*)"double")==0)
		Input_Plus<double>();

	return 0;

}

