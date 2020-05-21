//11-散列4 Hashing - Hard Version
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITY 65535
typedef int ElementType;  	//关键词类型
typedef int Vertex; // 用顶点下标表示顶点,为整形
#define MaxVertexNum 1000
#define MaxSize 1000
#define ERROR -1

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
    /* 将V2插入V1的表头, 在头上插入 */
    NewNode->Next = Graph->G[E->V1].FirstEdge; 
    Graph->G[E->V1].FirstEdge = NewNode;
}

/* ********************* TopSort *******************/
/* 邻接表存储 - 拓扑排序算法 */
 
bool TopSort( LGraph Graph, Vertex TopOrder[], int Cells[] )  // TopOrder[]顺序存储排序后的顶点下标 */
{ 
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    int mini, i;
    int *zeroin, num_in=0;  // num_in 记录indegree为0的顶点有几个
    PtrAdjVNode W;
    
    
    zeroin = malloc(Graph->Nv * sizeof(int));
    
  
    /* 初始化Indegree[], zeroin[] */
    for (V=0; V<Graph->Nv; V++){
        Indegree[V] = 0;
        zeroin[V] = INFINITY;  
    }
         
    /* 遍历图，得到Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */
             
    /* 将所有入度为0的顶点加入zeroin[] */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 ){
            zeroin[V] = Cells[V];
            num_in++;
        }
             
    /* 下面进入拓扑排序 */ 
    cnt = 0; 
    while( num_in != 0){
        // 找出zeroin[]里的最小值,把它变成INFINITY
        mini = INFINITY;
        for (i=0; i<Graph->Nv; i++){
            if (zeroin[i] < mini){
                mini = zeroin[i];
                V = i;
            }
        }
        zeroin[V] = INFINITY;
        num_in--;
        TopOrder[cnt++] = mini; /* 将之存为结果序列的下一个元素 */
        
        /* 对V的每个邻接点W->AdjV */
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
            if ( --Indegree[W->AdjV] == 0 ){/* 若删除V使得W->AdjV入度为0 */
                zeroin[W->AdjV]=Cells[W->AdjV]; /* 则该顶点加入zeroin[] */ 
                num_in++;
        }
    } /* while结束*/
     
    if ( cnt != Graph->Nv )
        return false; /* 说明图中有回路, 返回不成功标志 */ 
    else
        return true;
}



/* ************************************************/

int main(int argc, char const *argv[])
{
	
	int N; 
	scanf("%d", &N);  // 记录散列表TablieSize
	int *c; // 数组c 记录冲突次数
	c = malloc(N * sizeof(int));
	int *Cells; // 记录散列数组
	Cells = malloc(N * sizeof(int));
	
	int i, j;

	// 计算冲突次数
	for (i = 0; i < N; i++)  
	{
		scanf("%d", &Cells[i]);
		if (Cells[i] < 0){
			c[i] = INFINITY;
		}
		else{
			c[i] = i - (Cells[i] % N);
			if (c[i] < 0 )
				c[i] += N;
		}

	}


	// 建立邻接表
	LGraph Graph = CreateGraph(N);
	Edge E;

	for (i = 0; i < N; i++){
		if (c[i] > 0 && c[i]<INFINITY){
			// 插入边
			E = (Edge)malloc(sizeof(struct ENode)); // 创建边结点
			for (j=1; j<=c[i]; j++){
				E->V1 = (i-j)>0? i-j:i-j+N;
				E->V2 = i;
				InsertEdge(Graph, E);
			}
		}
	}

	// 拓扑排序
	Vertex TopOrder[MaxSize];
	TopSort(Graph, TopOrder, Cells);

	//输出
	int flag = 0;
	for (i = 0; i < N; i++){
		if (TopOrder[i] >= 0){  //非负,为有效数据
			if (flag == 0)
				flag = 1;
			else
				printf(" ");
			printf("%d", TopOrder[i]);
		}
	}

	printf("\n");
	return 0;
}




