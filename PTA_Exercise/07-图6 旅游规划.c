// 07-图6 旅游规划
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 501
#define INFINITY 65535
#define ERROR 999
typedef int Vertex; // 用顶点下标表示顶点,为整形
typedef int DataType;
typedef int WeightType;

/* ********************* MGraph *******************/
// Graph struct
typedef struct GNode * PtrGNode;
struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];	// 放distance
    WeightType C[MaxVertexNum][MaxVertexNum];  // 放cost
    // DataType Data[MAX]; // 存顶点的数据
};
typedef PtrGNode MGraph;

// Edge struct 边
typedef struct ENode *PtrENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
    WeightType Cost;
};
typedef PtrENode Edge;

// 初始化有VertexNum个顶点但没有边的图
MGraph CreateGraph(int VertexNum, int EdgeNum)
{
    MGraph Graph;
    Vertex v,w;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = EdgeNum;

    for(v=0; v<VertexNum; v++){
        for(w=0; w<VertexNum; w++){
            Graph->G[v][w] = INFINITY;
            Graph->C[v][w] = INFINITY;
        }
    }
    return Graph;
}


// 根据读入的数据建图
void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
    Graph->C[E->V1][E->V2] = E->Cost;
    Graph->C[E->V2][E->V1] = E->Cost;
}

// 建图
MGraph BuildGraph(int VertexNum, int EdgeNum){
    MGraph Graph;
    Edge E;
    int i;

    Graph = CreateGraph(VertexNum, EdgeNum);
    
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // 创建边结点
        for (i=0; i<Graph->Ne; i++)
        {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->Weight, &E->Cost);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}


/* ********************* Dijkstra *******************/
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]){
    Vertex MinV, V;
    int MinDist = INFINITY;

    for(V=0; V < Graph->Nv; V++){
        if (collected[V] == false && dist[V]< MinDist){  /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V];
            MinV = V;  /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else 
    	return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}


bool Dijkstra(MGraph Graph, int dist[], int cost[], int path[], Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V, W;

    // 初始化dist[], path[], cost[], collected[],邻接矩阵中不存在边的标记为INFINITY
    for(V=0; V < Graph->Nv; V++){
        dist[V] = Graph->G[S][V];
        cost[V] = Graph->C[S][V];
        if (dist[V] < INFINITY)  // S到V有直接路径
            path[V] = S;
        else 
            path[V] = -1;
        collected[V] = false;
    }
    // 先将起点收入到集合中
    dist[S] = 0;
    cost[S] = 0;
    collected[S] = true;

    while(1)
    {
        V = FindMinDist(Graph, dist, collected); /* V = 未被收录顶点中dist最小者 */
        if (V == ERROR)  /* 若这样的V已经不存在 */
            break; 
        collected[V] = true;
        for(W=0; W < Graph->Nv; W++){ // 对图中的每个顶点W
            if(collected[W] == false && Graph->G[V][W] < INFINITY)  // V的每个未被访问过的邻接点W
            {  
                if ( Graph->G[V][W] < 0 ) /* 若有负边 */
                    return false; /* 不能正确解决，返回错误标记 */
                
                /* 若收录V使得dist[W]变小 */
                if ( dist[V]+ Graph->G[V][W] < dist[W] ) {
                    dist[W] = dist[V]+ Graph->G[V][W]; // 更新dist[W]
                    path[W] = V; // 更新S到W的路径
                    cost[W] = cost[V] + Graph->C[V][W];  // 更新cost[w]
                }else if (dist[V]+ Graph->G[V][W] == dist[W] 
                		&& cost[V] + Graph->C[V][W] < cost[W])  // 距离一样但是费用更低,则更新费用
                {
                	cost[W] = cost[V] + Graph->C[V][W];
                	path[W] = V; 
                }
            }  
        } // for循环结束, 每个V的邻接点W遍历完
    }// while结束
    return true;
}

/* ********************************** */


int main(int argc, char const *argv[])
{
	int N,M,S,D;
	int dist[MaxVertexNum], cost[MaxVertexNum], path[MaxVertexNum];
	scanf("%d %d %d %d", &N, &M,&S, &D);
	MGraph Graph = BuildGraph(N, M);
	if(Dijkstra(Graph, dist, cost, path, S))
		printf("%d %d\n", dist[D], cost[D]);
	else
		printf("Error\n");

	return 0;
}




















