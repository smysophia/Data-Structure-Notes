
#include "stack.h"

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