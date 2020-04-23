//04-树7 二叉搜索树的操作集
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}


BinTree Insert( BinTree BST, ElementType X ){
    if(!BST){
        // BST空,则创建一个新结点
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else{ 
        //若不空
        if(X > BST->Data)
            BST->Right = Insert(BST->Right, X);
        else if(X < BST->Data)
            BST->Left = Insert(BST->Left, X);
    }

    return BST;
}


BinTree Delete( BinTree BST, ElementType X ){
    BinTree Tmp;

    if(!BST) 
        printf("Not Found\n");
    else
    {
        if(X > BST->Data)
            BST->Right = Delete(BST->Right, X);
        else if(X < BST->Data)
            BST->Left = Delete(BST->Left, X);
        else // (X == BST->Data), 找到了,删除
        {
            if(BST->Left && BST->Right)  // 被删除结点左右两边都有子树
            {
                /* 从右子树中找最小的元素填充删除结点 */
                Tmp = FindMin( BST->Right);
                BST->Data = Tmp->Data;
                /* 从右子树中删除最小元素 */
                BST->Right = Delete(BST->Right, Tmp->Data);
            }
            else  // 删除结点只有一个孩子,或者是叶结点
            {
                Tmp = BST;
                if(BST->Left)  // 左边不空,则BST这个结点变成BST左孩子
                    BST = BST->Left;
                else // 左边空 (右边不空,或者都空)
                    BST = BST->Right;
                free(Tmp);
            }
        }
    }
    return BST;
}


Position Find( BinTree BST, ElementType X ){
    if(!BST)
        return NULL;
    else
    {
        if(BST->Data == X)  // 找到了
            return BST;
        else if(X > BST->Data)
            return Find(BST->Right, X);
        else
            return Find(BST->Left,X);
    }
}


Position FindMin( BinTree BST){
    if(BST) //  根节点不空
    {
        while(BST->Left)  // 有左儿子
            BST = BST->Left;  // 一直往左,直到左儿子为空
    }
    return BST;
}


Position FindMax( BinTree BST ){
    if(BST) //  根节点不空
    {
        while(BST->Right)  // 有右儿子
            BST = BST->Right;  // 一直往右,直到右儿子为空
    }
    return BST;
}


void PreorderTraversal( BinTree BT){
    if(BT){
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}


void InorderTraversal( BinTree BT){
    if(BT){
        InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        InorderTraversal(BT->Right);
    }
}












