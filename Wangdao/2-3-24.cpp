// 保留单链表中绝对值相等结点的第一个

#include<iostream>
#include<stdlib.h>
using namespace std;

struct LinkList
{
    int data;  // abs <= n
    LinkList* link;
    LinkList(): link(NULL) {}
    LinkList(int val): data(val), link(NULL) {}
    LinkList(int val, LinkList* next): data(val), link(next) {}
};

void keepTheFirstValue(LinkList* head, int n) {
    bool* occur = new bool[n+1];
    for (int i = 0; i <= n; ++i)
        occur[i] = false;
    
    while(head && head->link) {
        if(occur[abs(head->link->data)]){
            //delete
            LinkList* tmp = head->link;
            head->link = head->link->link;
        }
        else occur[abs(head->link->data)] = true;  
        head = head->link;
    }

    delete[] occur;
}

int main() {
    LinkList head;
    LinkList el1(21), el2(-15), el3(-15), el4(-7), el5(15);
    head.link = &el1; el1.link = &el2; el2.link = &el3; el3.link = &el4; el4.link = &el5;
    LinkList *p = &head;
    keepTheFirstValue(&head, 21);
    while(p->link){
        cout << p->link->data << endl;
        p = p -> link;
    }
    return 0;
}