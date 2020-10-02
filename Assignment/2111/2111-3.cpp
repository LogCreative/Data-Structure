//2111. 最小差值
#include<iostream>
using namespace std;
#define MAXLINE 100000

// AA树做集合（set）。

class MyOrderedList {
private:
    bool OrdList[MAXLINE];
    int currentlength;
public:
    MyOrderedList(){ currentlength = 0; }

    void insert(int x){
        OrdList[currentlength]=x;
        ++currentlength;
    }

    void remove(int x){
        int i;
        for(i = 0;i<currentlength;++i){
            if(OrdList[i]==x)
                break;
        }
        --currentlength;
        for(;i<currentlength;++i){
            OrdList[i]=OrdList[i+1];
        }
    }

    int absmin(int x){
        //Shell
        int step,i,j;
        int tmp;
        for(step = currentlength/2;step>0;step/=2){
            for(i=step;i<currentlength;++i){
                tmp = OrdList[i];
                for(j=i-step;j>=0&&OrdList[j]>tmp;j-=step)
                    OrdList[j+step]=OrdList[j];
                OrdList[j+step]=tmp;
            }
        }

        for(i=0;OrdList[i]<x && i<currentlength;++i);
        if(i==0) return OrdList[0]-x;
        if(i==currentlength) return x-OrdList[currentlength-1];
        //第一大
        return (OrdList[i]-x>x-OrdList[i-1])?x-OrdList[i-1]:OrdList[i-1]-x;
    }

};

int main() {
    int M;
    cin >> M;

    //BinarySearchTree<int,char> BST;
    MyOrderedList ol;

    int op;
    int x;

    int output[MAXLINE];
    int length = 0;

    for (int i=0;i<M;++i){
        scanf("%d %d",&op,&x);
        switch (op)
        {
        case 0: output[length]=ol.absmin(x); ++length; break; //cout<<BST.absmin(x)<<'\n'; break;  //询问要求的最小值
        case 1: ol.insert(x); break; //BST.insert((SET<int,char>){x,'\0'}); break;  //插入元素x
        case 2: ol.remove(x); break;//BST.remove(x); break;  //删除元素x
        }
    }

    for(int i = 0;i<length;++i)
        printf("%d\n",output[i]);

    return 0;
}