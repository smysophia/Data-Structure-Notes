// 08-图7 公路村村通 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 1000
#define INFINITY 65535

typedef int Vertex; // 用顶点下标表示顶点,为整形
typedef char DataType;
typedef int WeightType; // 边的权值设为int

/* ********************* LGraph *******************/
// 边的定义与之前相同
typedef struct ENode *PtrENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
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
    Vertex V, V1, V2;
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
            scanf("%d %d %d", &V1, &V2, &E->Weight);
            E->V1 = V1 -1;
            E->V2 = V2 - 1;
            InsertEdge(Graph, E);
        }
    }
    /* 如果顶点有数据的话，读入数据 
    for (V=0; V<Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));
    */
    return Graph;
}

/* ********************* Kruskal ********************* */
typedef Vertex ElementType;  // 默认元素用非负整数表示
typedef Vertex SetName;  // 用根节点下标作为结合名称
typedef ElementType SetType[MaxVertexNum];

// 并查集
// 初始化全为-1
void InitializeVSet(SetType S, int N){
    ElementType X;
    for (X=0; X<N; X++)
        S[X] = -1;
}

void Union(SetType S, SetName Root1, SetName Root2){
    if (S[Root1] > S[Root2]){
        S[Root1] +=  S[Root2];
        S[Root2] = Root1;
    }
    else{
        S[Root2] +=  S[Root1];
        S[Root1] = Root2;
    }
}

SetName Find(SetType S, ElementType X){
    if(S[X] < 0)  // 找到集合的根
        return X;
    else
        return S[X] = Find(S,S[X]);
}

bool CheckCycle(SetType VSet, Vertex V1, Vertex V2){
    Vertex Root1, Root2;
    Root1 = Find(VSet, V1);
    Root2 = Find(VSet, V2);

    if (Root1 == Root2)
        return false;
    else{
        Union(VSet, Root1, Root2);
        return true;
    }

}


// 边的最小堆
// 将N个元素的边数组以 ESet[p]为根的子堆调整为关于Weight的最小堆
void PercDown(Edge ESet, int p, int N){  
// 直接用数组,不用heap结构了
    int Parent, Child;
    struct ENode X;

    X =ESet[p];
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (ESet[Child].Weight > ESet[Child+1].Weight) )
            Child++;  
        if( X.Weight <= ESet[Child].Weight ) 
            break; 
        else  /* 下滤X */
            ESet[Parent] = ESet[Child];
    }
    ESet[Parent] = X;
}

/* 将图的边存入数组ESet，并且初始化为最小堆 */ 
void InitializeESet(LGraph Graph, Edge ESet){
    Vertex V;
    PtrAdjVNode W;
    int ECount = 0;

    /* 将图的边存入数组ESet */
    for(V=0; V<Graph->Nv; V++){
        for(W=Graph->G[V].FirstEdge; W; W = W->Next){
            if (V < W->AdjV){  /* 避免重复录入无向图的边，只收V1<V2的边 */
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->AdjV;
                ESet[ECount].Weight = W->Weight;
                ECount++;
            }

        }
    }
    /* 调整为最小堆 从最后一个结点的父节点(Size/2)开始,到根节点(1)为止*/
    for ( ECount=Graph->Ne/2; ECount>=0; ECount-- )
        PercDown( ESet, ECount, Graph->Ne );
}

void Swap(struct ENode *a, struct ENode *b){
    struct ENode c;
    c = *a;
    *a = *b;
    *b = c;
}

 /* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆 */
 int GetEdge(Edge ESet, int CurrentSize){
    Swap(&ESet[0], &ESet[CurrentSize-1]);  /* 将最小边与当前堆的最后一个位置的边交换 */
    PercDown( ESet, 0, CurrentSize-1 );  /* 将剩下的边继续调整成最小堆  */

    return CurrentSize -1; /* 返回最小边所在位置 */
 }


int Kruskal(LGraph Graph, LGraph MST){
    WeightType TotalWeight;
    int ECount, NextEdeg;
    SetType VSet;  // 顶点数组
    Edge ESet;  // 边数组

    InitializeVSet(VSet, Graph->Nv);  // 初始化顶点并查集
    ESet = (Edge)malloc(sizeof(struct ENode) * Graph->Ne);  // 分配边数组空间
    InitializeESet(Graph, ESet);  // 初始化边的最小堆

    // 创建MSV图
    MST = CreateGraph(Graph->Nv);
    TotalWeight = 0;
    ECount = 0;

    NextEdeg = Graph->Ne;  // 原始边集合的规模
    while(ECount < Graph->Nv -1 ){  // 当收集的边小于顶点数-1时
        NextEdeg = GetEdge(ESet, NextEdeg);
        if (NextEdeg < 0) // 边集已经空
            break;
        if(CheckCycle(VSet, ESet[NextEdeg].V1, ESet[NextEdeg].V2))  // 如果不构成回路
        {
            // 插入边到MST中
            InsertEdge(MST, ESet + NextEdeg);  // 相当于 &ESet[NextEdge]
            TotalWeight += ESet[NextEdeg].Weight;
            ECount++;
        }        
    }// while循环结束
    if (ECount < Graph->Nv-1)
        TotalWeight = -1; // 设置错误标志

    return TotalWeight;
}


/* ******************************************** */
int main(int argc, char const *argv[])
{
	LGraph Graph, MST;
	int TotalWeight;
	Graph = BuildGraph();
	// printf("%d %d\n",Graph->G[0].FirstEdge->AdjV, Graph->G[0].FirstEdge->Weight );
	TotalWeight = Kruskal(Graph, MST);

	printf("%d\n", TotalWeight);
	return 0;
}





























