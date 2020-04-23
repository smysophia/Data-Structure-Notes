// minimum spanning tree MST 最小生成树
# define ERROR -1; 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100
#define INFINITY 65535

typedef int Vertex; 
typedef char DataType;
typedef int WeightType; 

/* ********************* Prim ********************* */
/* 返回未被收录顶点中dist最小者 */
Vertex FindMinDist(MGraph Graph, WeightType dist[]){
    Vertex MinV, V;
    WeightType MinDist =  INFINITY;

    for(V=0;, V< Graph->Nv; V++){
        if (dist[v] != 0 && dist[V] < MinDist) /* 若V未被收录，且dist[V]更小 */
        {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if (MinDist < INFINITY)
        return MinV;
    else
        return ERROR;
}


// 用邻接矩阵存储图,用邻接表存储最小生成树(因为是稀疏图)
int Prim(MGraph Graph, LGraph MST){  // 返回最小权重和
    WeightType dist[MaxVertexNum], TotalWeight;
    Vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;

    // 初始化, 默认起点下标为0, 无边定义为INFINITY
    for(V=0; V<Graph->Nv; V++){
        dist[V] = Graph->G[0][V];
        parent[V] = 0; // 暂定所有顶点的父节点为0
    }

    TotalWeight = 0;
    VCount = 0; // 初始收录的定点数

    // 创建MST的邻接表,包含所有顶点,没有边
    MST = CreateGraph(Graph->Nv);
    // 创建空的边结点
    E = (Edge)mallo(sizeof(struct ENode));

    // 将起点0收录MST
    dist[0] = 0;
    VCount++;
    parent[0] = -1;  // 当前树根是起点0

    while(1){
        V = FindMinDist(Graph, dist);  /* V = 未被收录顶点中dist最小者 */
        if (V == ERROR) 
            break;

        /* 将V及相应的边<parent[V], V>收录进MST */
        E->V1 = parent[V];
        E->V2 = V;
        E->Weight = dist[V];
        InsertEdge(MST, E);
        TotalWeight += dist[V];
        dist[V] = 0; 
        VCount++;

        for(W=0; W<Graph->Nv; W++){
            if(dist[W] != 0 && Graph->G[V][W] < INFINITY){.  /* 若W是V的邻接点并且未被收录 */
                if (Graph->G[V][W] < dist[W]) /* 若收录V使得dist[W]变小 */
                {
                    dist[W] = Graph->G[V][W];  /* 更新dist[W] */
                    parent[W] = V;/* 更新树 */
                }
            }
        }
    }/* while结束*/
    if (VCount < Graph->Nv)
    {
        TotalWeight = ERROR;
    }
    return TotalWeight;  /* 算法执行完毕，返回最小权重和或错误标记 */

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
    struct ENode *c;
    c = a;
    a = b;
    b = c;
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


