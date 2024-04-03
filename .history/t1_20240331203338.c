#include<stdio.h>
#include<stdlib.h>

#define MAX_NODES 1000

int main(){
    int i,j,n,m;
    scanf("%d %d",&n,&m);

    int graph[MAX_NODES][MAX_NODES];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            graph[i][j] =0;//0为W，1为R
        }
    }

    for(i=0;i<m;i++){
        int u,v;
        char chr;
        scanf("%d %d %c",&u,&v,&chr);

        u--;
        v--;
        if(chr=='R'){
            graph[u][v]=1;
            graph[v][u]=1;
        }
    }
    int goodCnt=0;
    for(i=0;i<n;i++){
        int hasadj=0;
        for(j=0;j<n;j++){
            if(graph[i][j]==1){
                hasadj=1;
                break;
            }
        }
        if(hasadj==0){
            goodCnt++;
            continue;
        }
        int allRed=1;
        for(j=0;j<n;j++){
            if(graph[i][j]==0){
                allRed=0;
                break;
            }
        }
        if(allRed==1) goodCnt++;
    }
    printf()
}