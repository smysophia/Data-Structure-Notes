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

/* ************************ MinHeap **********************/

// 数据结构
typedef struct HNode *MinHeap;
struct HNode {
    ElementType *Data; // 存储堆元素的数组
    int Size;   // 堆的当前元素的个数
    int Capacity;  // 堆的最大容量
};


// Create a heap
MinHeap CreateHeap(void)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType)); // 因为这里是一个数组,需要分配空间
    H->Size = 0; // 当前是空的
    H->Capacity = MaxSize;  // 堆的最大容量
    H->Data[0] = - INFINITY; /* 定义“哨兵”为小于堆中所有可能元素的值，便于以后操作 */
    return H;
}

// Full
bool IsHeapFull(MinHeap H){
    return (H->Size == H->Capacity);
}

// Empty
bool IsHeapEmpty(MinHeap H){
    return (H->Size == 0);
}

// Insert a node to a minheap
void InsertMinHeap(MinHeap H, ElementType item)
{
    int i;
    if (IsHeapFull(H)){
        printf("FULL\n");
        return;
    }
    i = ++H->Size;  // H->Size++; i = H->Size; 把新增元素放在末尾H->Size++的位置上
    if (i > 1){
        for(; H->Data[i/2] > item; i/=2){  // 其父节点大于它
            H->Data[i] = H->Data[i/2]; // 把它的父节点,向下过滤, 插入的item向上过滤
        } 
    }
    // 当它的父结点[i/2]比它小的时候, 符合条件,跳出循环
    H->Data[i] = item;  // 填上item
}



// Delete the root(the minimum) from a minheap
ElementType DeleteMin(MinHeap H)
{
    int parent, child;
    ElementType MinItem, temp;
    if(IsHeapEmpty(H)){
        printf("Empty\n");
        return ERROR;
    }

    MinItem = H->Data[1]; // 取出最小值
    /* 用最小堆中最后一个元素从根节点开始向上过滤下层节点 */
    temp = H->Data[H->Size];  // 把堆中最后一个值,交给temp
    H->Size--;

    for(parent=1; parent*2 <= H->Size; parent=child)
    {
        child = parent*2;  // 左儿子

        /* child=左右儿子中小的那个, 当右儿子存在,且右儿子的值比左儿子小时,让child=右儿子 */
        if((child!= H->Size) && 
        (H->Data[child] > H->Data[child+1])) 
            child++;
        
        /* 当temp比child的值小时跳出循环 */
        if (temp <= H->Data[child]) 
            break;
        else 
            H->Data[parent] = H->Data[child]; //当parent < child,这个parent位置上变为child的值
    }
    H->Data[parent] = temp; 
    return MinItem; 
}


/* ********************* TopSort *******************/
/* 邻接表存储 - 拓扑排序算法 */
 
bool TopSort( LGraph Graph, Vertex TopOrder[], int Cells[] )  // TopOrder[]顺序存储排序后的顶点下标 */
{ 
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    int mini;
    PtrAdjVNode W;
    MinHeap H = CreateHeap();
  
    /* 初始化Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;
         
    /* 遍历图，得到Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */
             
    /* 将所有入度为0的顶点插入最小堆 */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 )
            InsertMinHeap(H, Cells[V]);
             
    /* 下面进入拓扑排序 */ 
    cnt = 0; 
    while( !IsHeapEmpty(H) ){
        mini = DeleteMin(H); // 弹出最小值
        TopOrder[cnt++] = mini; /* 将之存为结果序列的下一个元素 */
        for (V=0; V<Graph->Nv; V++){
        	if (Cells[V] == mini)
        		break;
        }
        /* 对V的每个邻接点W->AdjV */
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
            if ( --Indegree[W->AdjV] == 0 )/* 若删除V使得W->AdjV入度为0 */
                InsertMinHeap(H, Cells[W->AdjV]); /* 则该顶点插入最小堆 */ 
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




