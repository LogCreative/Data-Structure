//全部重写

//需要堆排序。
//4252 和 1348 都需要排序

#include<iostream>
#include<iomanip>
using namespace std;

void sort(double* arr,int len){

        //shell sort

        for(int gap = len / 2; gap > 0; gap = gap / 2) {
            for(int i = gap; i < len; i++) {
                int j = i;
                double current = arr[i];
                while(j - gap >= 0 && current < arr[j - gap]) {
                    arr[j] = arr[j - gap];
                    j = j - gap;
                }
                arr[j] = current;
            }
        }
}

int main(){
    int i;

    int N;
    cin>>N;
    int* l=new int[N];
    for(i=0;i<N;++i)
        cin>>l[i];
    int M;
    cin>>M;

    double *male,*female;
    male=new double[M+1];
    female=new double[M+1];
    
    int male_num=0,female_num=0;
    int s,t;

    for(int i=0;i<M;++i){
        cin>>s>>t;
        if(s==1)
            male[male_num++]=t;
        else if(s==2)
            female[female_num++]=t;
    }

    sort(male,male_num);
    sort(female,female_num);

    //simulation
    double currentTime=0;

    double m_total=0,f_total=0;

    int male_head=0,female_head=0;

    for(int i=0;i<N;currentTime+=l[i],++i){
        if(i==N-1){
            while(male_head<male_num){
                m_total+=currentTime-male[male_head];
                male_head++;
            }
            while(female_head<female_num){
                f_total+=currentTime-female[female_head];
                female_head++;
            }
        }
        else{
            while(male_head<male_num&&female_head<female_num&&
            currentTime>=male[male_head]&&currentTime>=female[female_head]){
                m_total+=currentTime-male[male_head]; 
                f_total+=currentTime-female[female_head];
                male_head++;
                female_head++;
            }
        }
    }

    // for(i=0;i<N-1;++i){
    //     if(male_num!=0||female_num!=0){
    //     while(head<male_num&&head<female_num){
    //         m_t=currentTime-male[head];
    //         f_t=currentTime-female[head];
    //         if(m_t>=0&&f_t>=0){
    //             m_total+=m_t;
    //             f_total+=f_t;
    //             ++head;
    //         }
    //         else
    //             break;
    //     }
    //     }
    //     currentTime+=l[i];
    // }

    // //头指针
    // int male_head=head,female_head=head;

    // while(male_head<male_num){
    //     m_total+=currentTime-male[male_head];
    //     ++male_head;
    // }
    // while(female_head<female_num){
    //     f_total+=currentTime-female[female_head];
    //     ++female_head;
    // }

    float m_avg=(male_num==0?0:m_total/male_num);
    float f_avg=(female_num==0?0:f_total/female_num);

    // cout.setf(ios::fixed);
    // cout<<fixed<<setprecision(2)<<m_avg<<" "<<f_avg<<endl;

    printf("%.2f %.2f",m_avg,f_avg);

    delete[] l;
    delete[] male;
    delete[] female;

    return 0;
}