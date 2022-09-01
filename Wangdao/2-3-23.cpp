// 寻找进入共同后缀的起始位置

#include<iostream>
using namespace std;

struct LinkList
{
    char data;
    LinkList* next;
    LinkList(char val): data(val), next(NULL) {}
    LinkList(char val, LinkList* next): data(val), next(next) {}
};

LinkList* suffixEntryPosition(LinkList* str1, LinkList* str2) {
    if (str1 == NULL || str2 == NULL) return NULL;
    LinkList* p = str1, *q = str2;
    while(p!=q) {
        if (p->next) p = p->next;
        else p = str2;
        if (q->next) q = q->next;
        else q = str1;
    }
    return p;
}

int main() {
    LinkList str1('.'), str2('.');
    LinkList str11('l'), str12('o'), str13('a'), str14('d'), str15('i'), str16('n'), str17('g');
    LinkList str20('b'), str21('e');
    str1.next = &str11; str11.next = &str12; str12.next = &str13; str13.next = &str14; str14.next = &str15; str15.next = &str16; str16.next = &str17;
    str2.next = &str20; str20.next = &str21; str21.next = &str15;
    cout << suffixEntryPosition(&str1, &str2) -> data << endl;
    return 0;
}