// 02-线性结构4 Pop Sequence
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 1005
#define ERROR -1
typedef int ElementType;

/**************** Stack ******************/

typedef struct SNode *Stack;  //结构指针
struct SNode{
    ElementType *Data;  //数组
    int Top; // 栈顶位置的数组下标
    int Capacity;
};


// 创建堆栈
Stack CreateStack(int M)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(M * sizeof(ElementType));  // Data 从 0 到 M-1
    S->Top = -1;
    S->Capacity = M;

    return S;
}

bool IsStackFull(Stack PtrS){
    if (PtrS->Top == PtrS->Capacity-1 )
        return true;
    else return false;
}

// 入栈
void Push( Stack PtrS, ElementType item )  // stack这个类型的指针
{
    if ( IsStackFull(PtrS) ) // 判断满不满。从 0 到 M-1
    { 
        printf("堆栈满\n"); 
        return;
    }
    else 
    {
        PtrS->Data[++(PtrS->Top)] = item; 
        /* 相当于：
        (PtrS->Top)++;
        PtrS->Data[PtrS->Top] = item;
        */
        return;
    }
}

// 空
bool IsStackEmpty(Stack PtrS){
    if ( PtrS->Top == -1 )
        return true;
    else return false;
}

// 出栈
ElementType Pop( Stack PtrS ) 
{
    if ( IsStackEmpty(PtrS) ) {
         printf("堆栈空\n");
         return ERROR;  
    } 
    else 
        return ( PtrS->Data[(PtrS->Top)--] ); // return 出下标为top的这个值，同时Top-1
}

/* ************************** */

void ReadList(int List[], int N){
    for (int i=1; i<=N; i++)
        scanf("%d", &List[i]);
}

void CheckList(int List[], int Sequence[], int M, int N){
    Stack S = CreateStack(M);
    int j;
    int cur = 1;
    for (j=1; j<=N; j++){
        if (!IsStackFull(S))
            Push(S, Sequence[j]);
        while (!IsStackEmpty(S) && S->Data[S->Top] == List[cur]){
            Pop(S);
            cur++;
        }
        if (IsStackFull(S))
            break;
    }
    if (M && IsStackEmpty(S))
        printf("YES\n");
    else
        printf("NO\n");

}


int main(int argc, char const *argv[])
{
    int M, N, K,i;
    int List[MaxSize];

    scanf("%d %d %d", &M, &N, &K);
    int Sequence[MaxSize];
    for (i = 1; i<=N; i++){
        Sequence[i] = i;
    }
    for (i=0; i<K; i++){
        ReadList(List, N);
        CheckList(List, Sequence, M, N);
    }
    return 0;
}










