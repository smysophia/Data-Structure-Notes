// 05-树7 堆中的路径
#include <stdio.h>
#include <stdlib.h>
#define MAXN 1001
#define MAXH -10001

int H[MAXN], size;
void Create();
void Insert (int x);

int main(int argc, char const *argv[])
{
    int n, m, x, k;
    scanf("%d", &n);
    scanf("%d", &m);
    Create();
    for (int i=0; i<n; i++){
        scanf("%d", &x);
        Insert(x);
    }

    for(int j=0; j<m; j++){
        scanf("%d", &k);
        printf("%d", H[k]);
        while(k>1){
            k = k/2;
            printf(" %d", H[k]);
        }
        printf("\n");
    }

    return 0;
}

void Create(){
    size = 0;
    H[0] = MAXH;
}

void Insert (int x){
    if(size > MAXN-1){
        printf("FULL\n");
        return;
    }

    size++;
    int i = size;
    for(; H[i/2] > x; i/=2)
        H[i] = H[i/2];
    H[i] = x;
}









