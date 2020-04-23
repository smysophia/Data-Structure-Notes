// 06-图2 Saving James Bond - Hard Version
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MaxSize 101
#define ElementType int
#define ERROR 999

/**************** Queue ******************/
struct QNode {
    ElementType *Data; 
    int rear;
    int front;
};
typedef struct QNode *Queue;

// 创建队
Queue CreateQueue(void)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType));
    Q->front = Q->rear = 0;
    return Q;
}

// 空
bool IsEmpty(Queue Q)
{
    return(Q->front ==  Q->rear);
}

// 满
bool IsFull(Queue Q)
{
    return ((Q->rear+1) % MaxSize == Q->front );
}

// 入队
void AddQ( Queue PtrQ, ElementType item) {
    // if (IsFull(Q))
    if ( (PtrQ->rear+1) % MaxSize == PtrQ->front ) 
    { 
        printf("队列满");
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1)% MaxSize; 
    PtrQ->Data[PtrQ->rear] = item;
}

// 出队
ElementType DeleteQ ( Queue PtrQ ) // front和rear相同
{
    // if (IsEmpty(Q))
    if ( PtrQ->front == PtrQ->rear ) 
    { 
        printf("队列空");
        return ERROR;
    } 
    else 
    {
        PtrQ->front = (PtrQ->front+1)% MaxSize; // front往后移一位指向第一个元素
        return PtrQ->Data[PtrQ->front];
    } 
}

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
        printf("堆栈满"); 
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
         printf("堆栈空");
         return ERROR;  
    } 
    else 
        return ( PtrS->Data[(PtrS->Top)--] ); // return 出下标为top的这个值，同时Top-1
}
/**************** Stack ******************/

struct crocodile
{
    int hori;
    int vert;
    bool shore;
    bool jump;
} c[MaxSize]; // 全局变量,每一个数记录一个鳄鱼的结构

struct Dist
{
    int dist[MaxSize];
} Dist[MaxSize]; // 全局变量,记录要跳几下

struct Path
{
    int path[MaxSize];
}Path[MaxSize];  // 全局变量,记录路径


int Distance(int x1, int y1, int x2, int y2){
    int distance = (int)sqrt( pow((y2-y1), 2) + pow((x2-x1), 2));
    return distance;
}

bool NearShore(int x, int y, int D){
    if((50 -abs(x)) <= D || (50-abs(y)) <= D )
        return true;
    else
        return false;
}

bool FirstJump(int x, int y, int D){
    int distance = (int)sqrt(pow(x,2)+pow(y,2));
    if( distance <= D + 15/2)
        return true;
    else
        return false;
}

// 初始化, 读入数据
void Initial(int N, int D){
    int x, y;
    for(int i=0; i<N; i++){
        scanf("%d %d", &x,&y);
        c[i].hori = x;
        c[i].vert = y;
        c[i].shore = NearShore(x, y, D);
        c[i].jump = FirstJump(x, y, D);
    }
}



// 无权图的单源最短路
void Unweighted(int S, int N, int D){
    Queue Q;
    int V, W, distance, i, j;
    // 初始化
    for(i=0; i<N; i++)
            Dist[S].dist[i] = Path[S].path[i] = -1;
    
    
    Q = CreateQueue();
    Dist[S].dist[S] = 0; // 源点
    AddQ(Q,S); // 入队

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q); // 非空, 出队
        for(W=0; W<N; W++)
        {
            distance = Distance(c[V].hori, c[V].vert, c[W].hori, c[W].vert);
            if( Dist[S].dist[W] == -1 && distance <= D) // 未被访问过,且可以跳到(即W使V的邻接点)
            {
                 Dist[S].dist[W] = Dist[S].dist[V] + 1;
                 Path[S].path[W] = V;
                 AddQ(Q, W);
            }
    
        }
    }
}

void PrintList(int L[], int N){
    for (int i = 0; i< N; i++){
        printf("%d ", L[i]);
    }
    printf("\n");
}


int main(int argc, char const *argv[])
{
    int N, D, i, j, minj, mini;
    int FirstJumpDistance;
    int min = MaxSize;
    int FistDistance = MaxSize;
    Stack S;
    scanf("%d %d", &N, &D);
    Initial(N, D);
    
    // for(i=0; i<N; i++)
    //     printf("%d %d %d %d\n", c[i].hori, c[i].vert, c[i].shore, c[i].jump);
    
    // 一步跳到岸的情况
    if (D >= (50 - D/2)){
        printf("1\n");
        return 0;
    }

    for(i=0; i<N; i++)
    {
        
        if(c[i].jump) // 找第一跳的鳄鱼
        {
            Unweighted(i, N, D);
            FirstJumpDistance = Distance(c[i].hori, c[i].vert, 0, 0);
            for(j=0; j<N; j++){
                if (c[j].shore && Dist[i].dist[j] > 0){ // 找到可跳上案,并且连通的路径  
                    if(Dist[i].dist[j] < min){   // 找到最小路径
                        min = Dist[i].dist[j];
                        FistDistance = FirstJumpDistance;
                        minj = j;
                        mini = i;
                    }else if((Dist[i].dist[j] = min) && (FirstJumpDistance < FistDistance)){
                        FistDistance = FirstJumpDistance;
                        minj = j;
                        mini = i;
                    }

                }
            }
        }
    } // for循环结束
    if (min == MaxSize)  // 无可连通且跳上岸的鳄鱼
        printf("0\n");
     else
    {
        printf("%d\n", min+2); // 加2跳：从岛上到第一个鳄鱼的和从最后一个鳄鱼到岸上
        S = CreateStack(); 
        while(minj >= 0){
            Push(S, minj); // 入栈
            minj = Path[mini].path[minj];
        }
        while(!IsStackEmpty(S)){
            minj = Pop(S); // 出栈,直到栈空
            printf("%d %d\n", c[minj].hori, c[minj].vert);
        }
    }
    return 0;
}

