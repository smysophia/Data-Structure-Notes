// 01-复杂度3 二分查找
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

List ReadInput(){
    List L;
    int i;
    L = (List)malloc(sizeof(struct LNode));
    L->Data[0] = 0;
    scanf("%d", &L->Last);
    for (i=1; i<=L->Last; i++)
        scanf("%d", &L->Data[i]);
    return L;
}

Position BinarySearch( List L, ElementType X ){
    int Left, Right, Mid;
    Left = 0;
    Right = L->Last;
    while (Left <= Right){
        Mid = (Left + Right) / 2;
        if (X > L->Data[Mid])
            Left = Mid + 1;
        else if (X < L->Data[Mid])
            Right = Mid - 1;
        else // 相等,找到了
            return Mid;
    }
    return NotFound;
}




















