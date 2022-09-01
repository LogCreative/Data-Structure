// 一个带有表头结点的单链表，
//      data link
// 寻找单链表倒数第 k 个元素的值

#include<iostream>
using namespace std;

struct LinkList
{
    int data;
    LinkList* link;
    LinkList(int val): data(val), link(NULL) {}
    LinkList(int val, LinkList* next): data(val), link(next) {}
};

int getLastKElement(LinkList *list, int k){
    LinkList *p = list, *q;
    while(--k)
        p = p -> link;
    q = list;
    while(p -> link){
        p = p -> link;
        q = q -> link;
    }
    return q->data;
}

int main() {
    LinkList list(1);
    LinkList el2(2), el3(3), el4(4), el5(5);
    list.link = &el2;
    el2.link = &el3;
    el3.link = &el4;
    el4.link = &el5;
    cout << getLastKElement(&list, 3) << endl;
    return 0;
}