//10-排序6 Sort with Swap(0, i)
#include <stdio.h>
#include <stdlib.h>
#define MaxN 100001

int main(int argc, char const *argv[])
{
    int A[MaxN];
    int N;
    int i, j, p,S=0, K=0;

    scanf("%d", &N);

    for(i=0; i<N; i++){
        scanf("%d", &A[i]);
        if (A[i] == i)
            S++;  // 计算单元环
    }

    int initial = A[0];  // 把A[0]保存起来

    // 计算多圆环
    for (i=0; i<N; i++){
        if(A[i] != i){
            j = i;
            while(A[j] != j){
                p = j;  // 把j保存在p里
                j = A[j];  // 更新j=A[j]
                A[p] = p;  //原始第j位=j
            }
            K++;  
        }
    }
    
    if (initial == 0)
        printf("%d\n", N-S+K);   // 当包含0的多元环不存在的特殊情况
    else
        printf("%d\n", N-S+K-2);   // 包含0的多元环, 交换次数=N-2+K-2




    return 0;
}