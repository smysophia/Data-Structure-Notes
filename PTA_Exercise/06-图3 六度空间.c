// 06-图3 六度空间
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 1001
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
            Graph->G[v][w] = INFINITY;
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
MGraph BuildGraph(MGraph Graph){

    Edge E;
    Vertex V;
    int Nv, i, V1, V2;

    
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // 创建边结点
        for (i=0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &V1, &V2);
            E->V1 = V1 - 1;  // 从1开始编号
            E->V2 = V2 - 1;

            InsertEdge(Graph, E);
        }
    }
    return Graph;
}


bool Floyd( MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum] )
{
    Vertex i, j, k;
 
    /* 初始化 */
    for ( i=0; i<Graph->Nv; i++ )
        for( j=0; j < Graph->Nv; j++ ) {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }
 
    for( k=0; k<Graph->Nv; k++ )
        for( i=0; i<Graph->Nv; i++ )
            for( j=0; j<Graph->Nv; j++ )
                if( D[i][k] + D[k][j] < D[i][j] ) {
                    D[i][j] = D[i][k] + D[k][j];
                    if ( i==j && D[i][j]<0 ) /* 若发现负值圈 */
                        return false; /* 不能正确解决，返回错误标记 */
                    path[i][j] = k;
                }
    return true; 
}



/* ********************************************** */

int main(int argc, char const *argv[])
{
    MGraph Graph;
    WeightType D[MaxVertexNum][MaxVertexNum];
    Vertex path[MaxVertexNum][MaxVertexNum];
    int cnt;
    float percent;

    // build graph
    int Nv;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    Graph = BuildGraph(Graph);
    // printf("%d\n", Graph->G[0][1]);
    
    if(Floyd(Graph,D,path))
    {
        for(int i=0; i<Nv; i++){
            cnt = 0;
            for (int j=0; j<Nv; j++){
                // printf("D[%d][%d]=%d\n", i, j,D[i][j]);
                if (D[i][j] < 7)
                    cnt++;
            }
            // printf("cnt=%d Nv=%d\n", cnt, Nv);
            percent = (double)cnt / (double)Nv * 100;
            printf("%d: %.2f%%\n", i+1, percent);
        }
    }
    return 0;
}





/* **************************************** 方法二 BFS遍历 *********************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 1001
#define MaxSize 1001
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



/* ********************* LGraph *******************/
// 边的定义
typedef struct ENode *PtrENode;
struct ENode
{
    Vertex V1, V2;
};
typedef PtrENode Edge;

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
    //初始化
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
    NewNode->Weight = 1;
    /* 将V2插入V1的表头, 在头上插入 */
    NewNode->Next = Graph->G[E->V1].FirstEdge; 
    Graph->G[E->V1].FirstEdge = NewNode;

    /********** 若是无向图，还要插入边 <V2, V1> **********/
    /* 为V1建立新的邻接点 */
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode)); 
    NewNode->AdjV = E->V1;
    NewNode->Weight = 1;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge; 
    Graph->G[E->V2].FirstEdge = NewNode;
}


// 建图
LGraph BuildGraph(LGraph Graph){
    Edge E;
    Vertex V, V1, V2;
    int Nv, i;
 
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // 创建边结点
        for (i=0; i<Graph->Ne; i++)
        {
           /* 读入边,格式为 起点 终点 权重 */
            scanf("%d %d", &V1, &V2);
            E->V1 = V1 - 1;
            E->V2 = V2 - 1;
            InsertEdge(Graph, E);
        }
    } 

    return Graph;
}
/* ********************* BFS *******************/
void InitializeVisited(int Nv, bool Visited[]){
    Vertex V;
    for(Vertex V=0; V<Nv; V++)
        Visited[V] = false;
}



int SixDegree_BFS(LGraph Graph, Vertex S, bool Visited[]){
    Queue Q;
    Vertex V, Last, Tail;
    int cnt, level;
    PtrAdjVNode W;

    // 访问源头结点S
    Q=CreateQueue();
    Visited[S] = true;
    cnt = 1; // 统计人数从1开始(S本身)
    level = 0;
    Last = S;
    AddQ(Q, S);

    while(!IsEmpty(Q)){
        V = DeleteQ(Q);
        for (W=Graph->G[V].FirstEdge; W; W=W->Next){
            if (!Visited[W->AdjV]){
                Visited[W->AdjV] = true;
                cnt++;
                Tail = W->AdjV;  //当前层尾
                AddQ(Q, W->AdjV);
            }
        }
        if ( V == Last){  // 如果上一层最后一个顶点弹出
            level++;
            Last = Tail;  // 更新当前尾层尾该层最后一个呗访问过的顶点
        }

        if(level == 6)
            break;
    }// while循环结束
    return cnt;

}


/* ********************************************** */

int main(int argc, char const *argv[])
{
    LGraph Graph;
    bool Visited[MaxVertexNum];

    int cnt;
    float percent;

    // build graph
    int Nv;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    Graph = BuildGraph(Graph);

    // 对图的每个顶点遍历
    for(Vertex V=0; V<Nv; V++){
        InitializeVisited(Nv, Visited);
        cnt = SixDegree_BFS(Graph, V, Visited);
        percent = (double)cnt / (double)Nv * 100;
        printf("%d: %.2f%%\n", V+1, percent);  // i 是从0开始编的
    }
    

    return 0;
}





















