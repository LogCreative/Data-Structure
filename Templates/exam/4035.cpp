//4035. 泰先生的时光机
#include<iostream>
using namespace std;


int main(){
    long N; //总共有N个城镇 1 < N < 500000
    long M; //仅仅够建造M台时光机（每台时光机搭载人数相同） N < M < 2000000
    cin>>N>>M;

    long* a = new long[N];
    for(long i = 0;i<N;++i)
        cin>>a[i];    //表示每个城镇中想要进行时光旅行的人数a[i]

    long output;    //时光机的最小搭载量
    cout<<output<<'\n';

    //注意：一台时光机不能被来自不同城镇的乘客共用！
}