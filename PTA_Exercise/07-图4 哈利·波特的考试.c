//07-图4 哈利·波特的考试
#include <stdio.h>
#include <stdlib.h>
#define MAX 101
#define INFINITY 1000

typedef int Graph[MAX][MAX];

// 全局变量
Graph G, D;
int Nv,Ne;

void BuildGraph(void)
{
    int i,j,v1,v2,w;
    scanf("%d", &Nv);
    // 初始化
    for(i=0; i<Nv; i++){
        for(j=0; j<Nv; j++)
            G[i][j] = INFINITY;
    }
    // 填入边
    scanf("%d", &Ne);
    for(i=0; i<Ne; i++){
         scanf("%d %d %d", &v1, &v2, &w);
         v1 --; // 读入数从1开始,矩阵从0开始
         v2 --;
         G[v1][v2] = w;
         G[v2][v1] = w;
    }
}

void PrintGraph(Graph Graph){
    for(int i = 0; i<Nv; i++){
        for(int j=0; j<Nv; j++){
            printf("%d ", Graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void Floyd(void){
    int i,j,k;

    // 初始化
    for(i=0; i<Nv; i++){
        for(j=0; j<Nv; j++)
            D[i][j] = G[i][j];
    }

    // 递归
    for(k=0; k<Nv; k++){
        for(i=0; i<Nv; i++){
            for(j=0; j<Nv; j++){
                if((i!=j)  && (D[i][k] + D[k][j] < D[i][j]))
                    D[i][j] = D[i][k] + D[k][j];
            }
        }
    }
}

void FindAnimal(void){
    int i,j, n,min, maxdist;
    min = INFINITY;
    for(i=0; i<Nv; i++)
    {
        // 找每一行的最大值
        maxdist = -INFINITY;
        for(j=0; j<Nv; j++)
        {
            if ((i!=j) && (D[i][j]> maxdist))
                maxdist = D[i][j];
        }
        // 找最大值中的最小值
        if (maxdist < min)
        {
            min = maxdist;
            n  = i + 1;  // 下标从0开始,+1
        }
    }
    // 如果图不连通
    if (min == INFINITY)
        printf("0\n");
    else
        printf("%d %d\n", n, min );
}


int main(int argc, char const *argv[])
{
    BuildGraph();
    Floyd();
    // PrintGraph(D);
    FindAnimal();
    return 0;
}



