// 03-树3 Tree Traversals Again 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#define ElementType int
#define MaxSize 50
#define ERROR 999

/**************** Stack ******************/

typedef struct SNode *Stack;  //结构指针
struct SNode{
    ElementType *Data;  //数组
    int Top; // 栈顶位置的数组下标
};


// 创建堆栈
Stack CreateStack(void)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(MaxSize* sizeof(ElementType));
    S->Top = -1;

    return S;
}

// 入栈
void Push( Stack PtrS, ElementType item )  // stack这个类型的指针
{
    if ( PtrS->Top == MaxSize-1 ) // 判断满不满。从 0 到 MaxSize-1
    { 
        printf("堆栈满\n"); 
        return;
    }else 
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
/**************** Stack ******************/

int pre[MaxSize], in[MaxSize],post[MaxSize];  // 全局变量
void SolvePost(int preL, int inL, int postL, int n){  // pre的左端, in的左端, post的左端,树的总长度
    int root, i, L, R;
    if(n==0) return;
    if(n==1) {
        post[postL] = pre[preL];
        return;
    }
    root = pre[preL];
    post[postL+n-1] = root;
    for(i =0; i<n; i++){
        if(in[inL+i] == root)
            break;
    }
    L = i; // 左子树长度
    R = n - L -1; // 右子树长度=总长度-左子树-根
    SolvePost(preL+1, inL, postL, L);  // 迭代解决左子树
    SolvePost(preL+1+L, inL+1+L, postL+L, R);  // 迭代解决右子树
}



int main(int argc, char const *argv[])
{
    int N, i, data, flag = 0, pre_i = 0, in_i = 0;
    char catagory[5];
    Stack S;
    scanf("%d", &N);
    S = CreateStack();
    for(i=0; i<2*N; i++){
        scanf("%s", catagory);
        if(!strcmp(catagory, "Push")){
            scanf("%d", &data);
            pre[pre_i++] = data;
            Push(S, data);
        }else if(!strcmp(catagory, "Pop")){
            in[in_i++] = Pop(S);
        }
    }
    // for(i=0; i<N; i++)
    //     printf("%d ", PostL[i]);
    // printf("\n");
    SolvePost(0, 0, 0, N);   
    for(i=0; i<N; i++){
        if(flag == 0)
            flag = 1;
        else
            printf(" ");
        printf("%d", post[i]);
    }
    printf("\n");
        

}
