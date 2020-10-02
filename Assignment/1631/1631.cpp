// 1631.cpp: 字符串相除
#include<iostream>

#define MAXLINE 501 //对于所有测试用例，字符串最大长度小于501
using namespace std;

//str1除以str2的商是“15”，详细过程是：将两个字符串分别"看做"整型数5001和98, 整型数5001除以整型数98的商是51，最后再反转，得出的结果即是”15“

class seqstring{
private:
    char *data;
    int len;
    
public:
    //构造
    seqstring(const char *s=""){
        for (len=0;s[len]!='\0';++len);
        data=new char[len+1];
        for (len=0;s[len]!='\0';++len)
            data[len]=s[len];
        data[len]='\0';
    }
    //复制构造
    seqstring(const seqstring &other){
        data=new char[other.len+1];
        for(len=0;len<=other.len;++len)
            data[len]=other.data[len];
        --len;
    }
    ~seqstring() {} //析构
    //取字符串长度
    int length() const {return len;}
    //逆反
    void reverse(){
        seqstring tmp=*this;
        for(int i=len-1;i>=0;--i)
            tmp.data[len-1-i]=data[i];
        *this=tmp;
    }
    //补0函数前补
    void addzero(int num){
        seqstring tmp;
        tmp.data=new char[len+num+1];
        tmp.len=len+num;
        int i;
        for (i=0;i<num;++i)
            tmp.data[i]='0';
        for (i=num;i<len+num;++i)
            tmp.data[i]=data[i-num];
        tmp.data[len+num]='\0';
        *this=tmp;
    }
    //后补0
    void zeroadd(int num){
        seqstring tmp;
        tmp.data=new char[len+num+1];
        tmp.len=len+num;
        int i;
        for(i=0;i<len;++i)
            tmp.data[i]=data[i];
        for(i=len;i<len+num;++i)
            tmp.data[i]='0';
        tmp.data[len+num]='\0';
        *this=tmp;
    }
    bool isNonegative(){
         if(data[0]=='\n')
             return false;
        return true;
    }
    bool isPositive(){
        if(data[0]=='0'||data[0]=='\n')
            return false;
        return true;
    }
    //字符串相减
    seqstring subtraction(seqstring const &subtractor){
        char* result=new char[length()];
        if(length()<subtractor.length())
            return (seqstring)"\n"; //异常
        if(length()==subtractor.length()){
            for(int i=0;i<length();++i){
                if(data[i]>subtractor.data[i])
                    break;
                else
                {
                    if(data[i]<subtractor.data[i])
                        return (seqstring)"\n"; //异常
                }
            }
        }
        seqstring r_subtractor=subtractor;
        r_subtractor.addzero(length()-subtractor.length());
        int i,mid_digit;
        for (i=len-1;i>=0;--i){
            //末尾开始计算
            mid_digit=data[i]-r_subtractor.data[i];
            if (mid_digit<0){
                mid_digit+=10;
                data[i-1]-=1;
            }
            result[i]=(char)(mid_digit+(int)'0');
        }
        result[len]='\0';
            //去0操作
            
            for(i=0;result[i]=='0';++i);
            char* tmp_res=new char[len-i+1];
            for(int t=0;i<=len;++i,++t)
                tmp_res[t]=result[i];
            if(tmp_res[0]=='\0'){
                tmp_res[0]='0';
                tmp_res[1]='\0';
            }
            seqstring tmp_result(tmp_res);
            //delete[] result;
            //delete[] tmp_res;
            return tmp_result;
        
    }
    //字符串相除
    seqstring division(seqstring const &divider){
        seqstring s,v;//s存商 v存余数
        seqstring c_d;
        seqstring temp;
        int*r=new int[len];
        for(int i=0;i<len;++i){
            r[i]=0;
        }
        if(length()<divider.length()||(length()==divider.length()&&!subtraction(divider).isNonegative()))
            return (seqstring)"0";
        
        int t=length()-divider.length();
        c_d=divider;
        c_d.zeroadd(t);
        int r_ptr=0;
        
        while(t>=0){
            while((temp=subtraction(c_d)).isNonegative()){
                ++r[r_ptr];
                *this=temp;
            }
            ++r_ptr;
            --t;
            c_d=divider;
            c_d.zeroadd(t);
        }

        char*tmp_result=new char[r_ptr+1];
        for(int i=0;i<r_ptr;++i){
            tmp_result[i]=r[i]+'0';
        }
        tmp_result[r_ptr]='\0';
        
        //去零操作
        int i;
        for(i=0;tmp_result[i]=='0';++i);
        char* tmp_res=new char[r_ptr-i+1];
            for(int t=0;i<=r_ptr;++i,++t)
                tmp_res[t]=tmp_result[i];
            if(tmp_res[0]=='\0'){
                tmp_res[0]='0';
                tmp_res[1]='\0';
            }

        seqstring result(tmp_res);
        delete[] r;
        delete[] tmp_result;
        delete[] tmp_res;
        return result;
    }
    void disp() const {
        for(int i=0;i<len;++i)
            cout<<data[i];
        cout<<'\n';
    }
};

int main(){
    char str1[MAXLINE],str2[MAXLINE];
    cin>>str1>>str2;

    seqstring seqstr1(str1), seqstr2(str2);
    //取反
    seqstr1.reverse();
    seqstr2.reverse();

    //除法
    seqstring seqstrres = seqstr1.division(seqstr2);
    
    //seqstring seqstrres = seqstr1.subtraction(seqstr2);

    //结果取反
    seqstrres.reverse();
    
    //显示结果
    seqstrres.disp();

    return 0;
}