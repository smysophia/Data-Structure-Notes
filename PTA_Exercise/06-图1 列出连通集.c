// 06-图1 列出连通集
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 10
#define MaxSize 11
#define INFINITY 65535
#define ElementType int
#define ERROR -1

typedef int Vertex; // 用顶点下标表示顶点,为整形
typedef int WeightType; // 边的权值设为int

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

/* *********************************** */


/* ********************* MGraph *******************/
// Graph struct
typedef struct GNode * PtrGNode;
struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    // DataType Data[MAX]; // 存顶点的数据
};
typedef PtrGNode MGraph;

// Edge struct
typedef struct ENode *PtrENode;
struct ENode
{
    Vertex V1, V2;
};
typedef PtrENode Edge;

// 初始化有VertexNum个顶点但没有边的图
MGraph CreateGraph(int VertexNum)
{
    MGraph Graph;
    Vertex v,w;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for(v=0; v<VertexNum; v++){
        for(w=0; w<VertexNum; w++){
            Graph->G[v][w] = 0;
        }
    }
    return Graph;
}


// 插入边
void InsertEdge(MGraph Graph, Edge E){
    // 插入<V1, V2>
    Graph ->G[E->V1][E->V2] = 1;
    //若是无向图,还要插入<V2, V1>
    Graph->G[E->V2][E->V1] = 1;
}

// 建图
MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));

    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // 创建边结点
        for (i=0; i<Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}


/* ********************* DFS *******************/
// 邻接矩阵深度优先DFS遍

bool IsEdge(MGraph Graph, Vertex V, Vertex W){
    return Graph->G[V][W]>0? true : false;
}



void DFS( MGraph Graph, Vertex V, bool Visited[], Queue Q)
{
    Vertex W;
    AddQ(Q, V);
    Visited[V] = true;
    /* 对V的每个邻接点W */
    for( W=0; W < Graph->Nv; W++ )  // 对图中的每个顶点遍历
        if ( !Visited[W] && IsEdge(Graph, V, W))
            DFS( Graph, W, Visited, Q);
}

/* ********************* BFS *******************/
void BFS ( MGraph Graph, Vertex S, bool Visited[],Queue Q)
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Que;     
    Vertex V, W;
    AddQ(Q, S);
    Que = CreateQueue(); /* 创建空队列, MaxSize为外部定义的常数 */
    
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Que, S); 
     
    while ( !IsEmpty(Que) ) {
        V = DeleteQ(Que);  
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                AddQ(Q, W);
                Visited[W] = true; /* 标记W已访问 */
                AddQ(Que, W); /* W入队列 */
            }
    } /* while结束*/
}


int main(int argc, char const *argv[])
{
    int i;
    Vertex V;
    MGraph Graph;
    Graph = BuildGraph();
    // printf("%d\n", Graph->G[0][4]);


    bool Visited[MaxVertexNum] = {false};
    Queue Q = CreateQueue();

    for( V=0; V < Graph->Nv; V++){
        if (Visited[V] == false){
            DFS(Graph, V, Visited, Q);
            printf("{ ");
            while (!IsEmpty(Q))
            {
                printf("%d ", DeleteQ(Q));
            }
            printf("}\n");
        }
    }

    
    for (i=0; i<Graph->Nv; i++)
        Visited[i] = false;
     for( V=0; V < Graph->Nv; V++){
        if (Visited[V] == false){
            BFS(Graph, V, Visited, Q);
            printf("{ ");
            while (!IsEmpty(Q))
            {
                printf("%d ", DeleteQ(Q));
            }
            printf("}\n");
        }
    }

    return 0;
}