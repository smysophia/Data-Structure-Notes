// 05-树8 File Transfer
#include <stdio.h>
#include <stdlib.h>
#define MAXN 10001                  /* 集合最大元素个数 */
typedef int ElementType;           /* 默认元素可以用非负整数表示 */
typedef int SetName;               /* 默认用根结点的下标作为集合名称 */
typedef ElementType SetType[MAXN]; /* 假设集合元素下标从0开始 */

void Initial(SetType S, int n);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S,int n);
SetName Find(SetType S, ElementType x);
void Union(SetType S, SetName R1, SetName R2);

int main(int argc, char const *argv[])
{
    SetType S;
    int n;
    char in;
    scanf("%d", &n);
    Initial(S, n); // 都初始化为-1
    do{
        getchar();  // 接收每次多出来的回车 
        scanf("%c",&in);
        switch(in){
            case 'I': Input_connection(S); break;
            case 'C': Check_connection(S); break;
            case 'S': Check_network(S, n); break;
        }
    }while( in != 'S');
    return 0;
}


void Initial(SetType S, int n){
    for (int i=0; i<n; i++)
        S[i] = -1;
}


// 并
void Input_connection(SetType S){
    ElementType u,v;
    scanf("%d %d", &u, &v);
    SetName R1, R2;
    R1 = Find(S, u-1);
    R2 = Find(S, v-1);
    if (R1 != R2)
        Union(S, R1, R2);
}

// 查
void Check_connection(SetType S){
    ElementType u,v;
    scanf("%d %d", &u, &v);
    SetName R1, R2;
    R1 = Find(S, u-1);
    R2 = Find(S, v-1);
    if (R1 == R2)
        printf("yes\n");
    else
        printf("no\n");
}

void Check_network(SetType S, int n){
    int i, count=0;
    for(i=0; i<n; i++){
        if(S[i] < 0)
            count++;
    }
    if(count == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", count);
}

SetName Find(SetType S, ElementType x){
    if (S[x] < 0)
        return x;
    else
        return S[x] = Find(S, S[x]);
}

void Union(SetType S, SetName R1, SetName R2){
    if(S[R1] > S[R2]){  // 集合R2比较大,因为是负数
        S[R2] += S[R1];
        S[R1] = R2;
    }
    else
    {
        S[R1] += S[R2];
        S[R2] = R1;
    }
}




