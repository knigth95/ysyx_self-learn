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
        scanf("%d %d ",&u,&v);
    }
}