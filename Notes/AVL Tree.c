// AVL Tree
#define ElementType int

typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(int a, int b){
    return a>b? a:b;
}

// 高度函数
int GetHeight(AVLTree T){
    int HL, HR;
    if(T){
        HL = GetHeight(T->Left);
        HR = GetHeight(T->Right);
        T->Height = Max(HL, HR) + 1;
    }
    else return 0;
    return T->Height;
}

// 左单旋函数LL
AVLTree LL(AVLTree A){
    // 新结点插入在A(Root)的左孩子B的左子树中
    AVLTree B = A->Left;  // 根变成A的左孩子B
    A->Left = B->Right;  // A的左孩子变成B的右孩子
    B->Right = A;   //B的右孩子变成A
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height) + 1;

    return B;
}


// 右单旋函数RR
AVLTree RR(AVLTree A){
    // 新结点插入在A(Root)的右孩子B的右子树中
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max( GetHeight(B->Right), A->Height) + 1;

    return B;
}


// 左右双旋函数LR
AVLTree LR(AVLTree A){
    // 新结点插在A的左子树B的右子树C中
    A->Left = RR(A->Left);  // 对A的左子树B做一次右单旋RR
    return LL(A);  //再对A做一次左单旋LL,返回根节点C
}


// 右左双旋函数RL
AVLTree RL(AVLTree A){
    // 新结点插入在A(Root)的右孩子B的左子树中
    A->Right = LL(A->Right);   // 对A的右孩子B做一次左单旋RR
    return RR(A); //再对A做一次右单旋LL,返回根节点C
}


//将X插入AVL树中,并且返回调整后的平衡树
AVLTree Insert(AVLTree T, ElementType X){
    if(!T)
    {  //若插入空树,就新建包含一个结点的树
        T=(AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Left = T->Right = NULL;
        T->Height = 1;
    }

    else if(X < T->Data)
    {
        T->Left = Insert(T->Left, X);  // 插入左子树
        if((GetHeight(T->Left) - GetHeight(T->Right)) == 2) //需要做LL旋转或LR
        {
            if(X < T->Left->Data) // 新结点插入在A(Root)的左孩子的左子树中
                T = LL(T);
            else        // 新结点插在A的左子树的右子树中
                T = LR(T);
        }
    }

    else if(X > T->Data)
    {
        T->Right = Insert(T->Right, X);  // 插入左子树
        if((GetHeight(T->Right) - GetHeight(T->Left)) == 2) //需要做RR旋转或者RL
        {
            if(X > T->Right->Data)
                T = RR(T);  // 新结点插入在A(Root)的右孩子B的右子树中
            else        // 新结点插入在A(Root)的右孩子B的左子树中
                T = RL(T);
        }
    }

    // else T->Data == X 无需插入
    
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;  // 更新树的高度,左右高度的最大值+1

    return T;
}


