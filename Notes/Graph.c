
// Graph
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100
#define INFINITY 65535

typedef int Vertex; // 用顶点下标表示顶点,为整形
typedef int WeightType; // 边的权值设为int

/* ********************* MGraph *******************/
typedef char DataType;


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
    WeightType Weight;
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
    Graph ->G[E->V1][E->V2] = E->Weight;
    //若是无向图,还要插入<V2, V1>
    Graph->G[E->V2][E->V1] = E->Weight;
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
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    /* 如果顶点有数据的话，读入数据 
    for (V=0; V<Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));
    */
    return Graph;
}

// 用全局变量建图
int G[MaxVertexNum][MaxVertexNum], Nv, Ne; 
void NBuildGraph()
{ 
    int i,j,v1,v2,w;
    scanf("%d", &Nv);
    /* CreateGraph */
    for (i=0; i<Nv; i++)
        for (j=0; j<Nv; j++)
            G[i][j] = 0; /* 或INFINITY */ 
    scanf("%d", &Ne);
    for (i=0; i<Ne; i++) {
         scanf("%d %d %d", &v1, &v2, &w);
         /* InsertEdge */
        G[v1][v2] = w;
        G[v2][v1] = w;
    }
}


/* ********************* LGraph *******************/
// 边的定义
// typedef struct ENode *PtrENode;
// struct ENode
// {
//     Vertex V1, V2;
//     WeightType Weight;
// };
// typedef PtrENode Edge;

// 邻接点的定义 边表
typedef struct AdjVNode *PtrAdjVNode;
struct AdjVNode
{
    Vertex AdjV; // 邻接点下标
    WeightType Weight; // 边权重
    PtrAdjVNode Next;  // 指向下一个邻接点的致指针
};

// 顶点表头结点的定义 顶点表
struct VNode{
    PtrAdjVNode FirstEdge;  // 边表头指针
    // DataType Data;   // 存顶点数据,一般不用
};
typedef struct VNode AdjList[MaxVertexNum];

// Graph struct
/* 图结点的定义 */
typedef struct GNode * PtrGNode;
struct GNode
{
    int Nv; //顶点数
    int Ne; // 边数
    AdjList G; // 邻接表. 是一个size为MaxVertexNum的数组,每一个元素都是一个结点VNode
};
typedef PtrGNode LGraph;

// 初始化有VertexNum个顶点但没有边的图
LGraph CreateGraph(int VertexNum)
{
    LGraph Graph;
    Vertex v,w;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for(v=0; v<Graph->Nv; v++)
        Graph->G[v].FirstEdge = NULL; // 每一个顶点v的FirstEdge都是空的, 编号从0到 Graph->Nv-1
    return Graph;
}

// 插入一条边
void InsertEdge (LGraph Graph, Edge E)  /* 插入边<V1, V2> */
{
    PtrAdjVNode NewNode;

    /* 为V2建立新的邻接点 */
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode)); 
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头, 在头上插入 */
    NewNode->Next = Graph->G[E->V1].FirstEdge; 
    Graph->G[E->V1].FirstEdge = NewNode;

    /********** 若是无向图，还要插入边 <V2, V1> **********/
    /* 为V1建立新的邻接点 */
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode)); 
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge; 
    Graph->G[E->V2].FirstEdge = NewNode;
}


// 建图
LGraph BuildGraph(){
    LGraph Graph;
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
           /* 读入边,格式为 起点 终点 权重 */
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    /* 如果顶点有数据的话，读入数据 
    for (V=0; V<Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));
    */
    return Graph;
}



/* ********************* DFS *******************/
// 邻接表深度优先DFS遍
bool Visited[MaxVertexNum] = {false};  // 全局变量初始化为false

void Visit( Vertex V )
{
    printf("正在访问顶点%d\n", V);
}
 
void DFS( LGraph Graph, Vertex V, void (*Visit)(Vertex) )
{  
    PtrAdjVNode W;
    Visit( V ); 
    Visited[V] = true; 
    /* 对V的每个邻接点W->AdjV */
    for( W=Graph->G[V].FirstEdge; W; W=W->Next ) 
        if ( !Visited[W->AdjV] )    
            DFS( Graph, W->AdjV, Visit );  
}

// 邻接矩阵深度优先DFS遍
bool IsEdge(MGraph Graph, Vertex V, Vertex W){
    return Graph->G[V][W]<INFINITY? true : false;
}

void DFS( MGraph Graph, Vertex V, void (*Visit)(Vertex) )
{  
    Vertex W;
    Visit( V ); 
    Visited[V] = true; 
    /* 对V的每个邻接点W->AdjV */
    for( W=0; W<Graph->Nv; W++ )  // 对图中的每个顶点遍历
        if ( !Visited[W] && IsEdge(Graph, V, W))    
            DFS( Graph, W, Visit );  
}

/* ********************* BFS *******************/
// // 邻接矩阵深度优先BFS遍
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W]<INFINITY ? true : false;
}
 
/* Visited[]为全局变量，已经初始化为false */
void BFS ( MGraph Graph, Vertex S, void (*Visit)(Vertex) )
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;     
    Vertex V, W;
 
    Q = CreateQueue( MaxSize ); /* 创建空队列, MaxSize为外部定义的常数 */
    Visit( S );
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Q, S); 
     
    while ( !IsEmpty(Q) ) {
        V = DeleteQ(Q);  
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                Visit( W );
                Visited[W] = true; /* 标记W已访问 */
                AddQ(Q, W); /* W入队列 */
            }
    } /* while结束*/
}











