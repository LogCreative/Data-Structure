//4229. Paper Citation
#include<iostream>
#include<cstring>
#include<string>
#define MAXLINE 50001
#define OPMAXLINE 1000001
using namespace std;

int main() {
    
    int N;
    cin >> N;

    int paper[MAXLINE] = { 0 };
    int max_paper=0,max_cit=0;

    char op[7];
    int i, j;
    int output1[OPMAXLINE];
    int output2[OPMAXLINE];
    int quenum = 0;

    while(true) {
        scanf("%s",op);
        if (strcmp(op,"add")==0) {
            scanf("%d %d",&i,&j);
            ++paper[j];
            if(paper[j]==max_cit){
                if(j<max_paper)
                    max_paper=j;
            }
            if(paper[j]>max_cit){
                max_cit = paper[j];
                max_paper = j;
            }
        } else if (strcmp(op,"query")==0) {
            output1[quenum] = max_paper;
            output2[quenum] = max_cit;
            ++quenum;
        } else if (strcmp(op,"finish")==0)
            break;
    }

    for(int i=0;i<quenum;++i)
        printf("%d %d\n",output1[i],output2[i]);

    return 0;

}