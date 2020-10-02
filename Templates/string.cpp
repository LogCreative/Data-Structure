#include<iostream>
using namespace std;

class seqString{
    friend seqString operator+ (const seqString &s1, const seqString &s2);
    friend bool operator== (const seqString &s1, const seqString &s2);
    friend bool operator!= (const seqString &s1, const seqString &s2);
    friend bool operator> (const seqString &s1, const seqString &s2);
    friend bool operator>= (const seqString &s1, const seqString &s2);
    friend bool operator< (const seqString &s1, const seqString &s2);
    friend bool operator<= (const seqString &s1, const seqString &s2);
    friend ostream &operator<< (ostream &os, const seqString &s);

    char *data;
    int len;                                //数组编号

public:
    
    seqString(const char *s=""){
        for(len=0;s[len]!='/0';++len);      //直接用len
        data = new char[len+1];             //包含'/0'
        for(len=0;s[len]!='/0';++len)
            data[len] = s[len];
        data[len]='/0';
    }

    seqString(const seqString &other){
        //不需要计数器
        data = new char[other.len+1];
        for(len=0;len<=other.len;++len)
            data[len]=other.data[len];      //在other下 不越界
    }

    ~seqString(){ delete[] data; }

    int length() const { return len; }

    //seqString &opeartor=(const seqString &other){}     //不支持的类型，c++17貌似已经可以直接调用复制构造函数
    seqString subStr(int start,int num) const{
        //有可能越界
        
    }
    seqString insert(int start, const seqString &s);
    seqString remove(int start,int num);

};

// optional
class linkString{

};