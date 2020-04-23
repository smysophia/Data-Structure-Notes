#include <stdio.h>
#include <stdlib.h>
#define ElementType struct TreeNode
#define null -1
#define Tree int
#define MaxTree 10

struct TreeNode
{
    int index;
    Tree left;
    Tree right;
};

int BuildTree(struct TreeNode T[]);

struct QNode
{
    ElementType *Data; 
    int rear;
    int front;
    int Maxsize;
};
typedef struct QNode *Queue;
Queue CreateQueue(int Maxsize);
void AddQ( Queue PtrQ, ElementType item);
ElementType DeleteQ ( Queue PtrQ );
int IsEmptyQ(Queue Q);

void Leaves( struct TreeNode T[], int Root, int Maxsize); 


int main(int argc, char const *argv[])
{
    struct TreeNode T[MaxTree];
    Tree R1;    
    R1 = BuildTree(T);
    // printf("Root=%d\n", T[R1].index);
    // printf("T[0].left=%d\n", T[0].left);
    Leaves(T, R1, MaxTree);

    return 0;
}

Tree BuildTree(struct TreeNode T[])
{
    int N, i;
    Tree Root = null;
    char cl, cr;
    scanf("%d", &N);
    if(N)
    {
         /* 设置一个列表,初始化为0 */
        int check[N];
        for (i=0; i<N; i++) check[i] = 0;  
        
        for(i=0; i<N; i++)
        {
            T[i].index = i;
            scanf("%*c %c %c", &cl, &cr);  // 先以字符读入
            if (cl != '-')
            {
                T[i].left = cl - '0';
                check[T[i].left] = 1; // check列表里,把T[i].left位上设为1
            }else T[i].left = null;  // 设为-1
            
            if (cr != '-')
            {
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }else T[i].right = null;  // 设为-1
        }
        

        // 遍历列表 check
        for (i=0; i<N; i++){
            if (check[i] == 0) break;
        }
        Root = i;

    }
    return Root;

}



void Leaves( struct TreeNode T[], int Root, int Maxsize) 
{
    
    int flag = 0;
    Queue Q; 
    struct TreeNode TN;
    if ( Root == null ) return; /* 若是空树则直接返回 */ 
    Q = CreateQueue( Maxsize ); /*创建并初始化队列Q*/ 
    AddQ( Q, T[Root] ); // 把根节点放到队列里去
    while ( !IsEmptyQ( Q ) ) {
        T[Root] = DeleteQ( Q );  // pop出一个元素,产生的元素赋给 T指针
        if ((T[Root].left == null) &&( T[Root].right == null))
            {
                if (flag == 0) flag = 1;
                else printf(" ");
                printf("%d", T[Root].index); /*访问取出队列的结点*/ 
            }
        if ( T[Root].left != null ) AddQ( Q, T[T[Root].left] );
        if ( T[Root].right != null ) AddQ( Q, T[T[Root].right] );
    }
    printf("\n"); 
}

Queue CreateQueue(int Maxsize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(Maxsize * sizeof(ElementType));
    Q->front = Q->rear = 0;
    Q->Maxsize = Maxsize;
    return Q;
}

void AddQ( Queue PtrQ, ElementType item) {
    // if (IsFull(Q))
    if ( (PtrQ->rear+1) % PtrQ->Maxsize == PtrQ->front ) 
    { 
        printf("FULL");
        return;
    }
    PtrQ->rear = (PtrQ->rear+1)% PtrQ->Maxsize; 
    PtrQ->Data[PtrQ->rear] = item;
}

int IsEmptyQ(Queue Q)
{
    return(Q->front ==  Q->rear);
}


ElementType DeleteQ ( Queue PtrQ ) // front和rear相同
{
    // if (IsEmpty(Q))
    if ( PtrQ->front == PtrQ->rear ) 
    { 
        printf("EMPTY");
        return (ElementType){};
    } 
    else 
    {
        PtrQ->front = (PtrQ->front+1)% PtrQ->Maxsize; // front往后移一位指向第一个元素
        return PtrQ->Data[PtrQ->front];
    } 
}



    
