// 无权图的单源最短路 类似于BFS
/* dist[W]: S到W的最短距离, 初始化为-1;
   path[W]: S到W的路上, W的父顶点, 初始化为-1'
*/
void Unweighted(LGraph Graph, int dist[], int path[], Vertex S){
    Queue Q;
    Vertex V;
    PtrAdjVNode W;

    Q = CreateQueue(Graph->Nv);  // 创建空队列,MaxSize为外部定义的常数
    dist[S] = 0; // 初始化源点
    AddQ(Q, S);

    while (IsEmpty(Q))
    {
        V = DeleteQ(Q);
        for( W = Graph.G[V].FirstEdge; W; W=W->Next)  // 对V的每个邻接点W->AdjV
            if (dist[W->AdjV] == -1)// W->AdjV 未被访问过
            {  
                dist[W->AdjV] =dist[V] + 1;  /* W->AdjV到S的距离更新 */
                path[W->AdjV] = V; /* 将V记录在S到W->AdjV的路径上 */
                AddQ(Q, W->AdjV);
            }
    }
}


// 有权图的单源最短路 Dijkstra算法

/* 返回未被收录顶点中dist最小值 */
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


bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V, W;

    // 初始化dist[], path[]和collected[],邻接矩阵中不存在边的标记为INFINITY
    for(V=0; V<Graph->Nv; V++){
        dist[V] = Graph->G[S][V];
        if (dist[V] < INFINITY)  // S到V有直接路径
            path[V] = S;
        else 
            path[V] = -1;
        collected[V] = false;
    }
    // 先将起点收入到集合中
    dist[S] = 0;
    collected[S] = true;

    while(1)
    {
        V = FindMinDist(Graph, dist, collected); /* V = 未被收录顶点中dist最小者 */
        if (V == ERROR)  /* 若这样的V已经不存在 */
            break; 
        collected[V] = true;
        for(W=0; W < Graph->Nv; W++){ // 对图中的每个顶点W
            if(collected[W] == false && Graph->G[V][W] < INFINITY)  // W未被访问,且边<V,W>存在
            {  
                if ( Graph->G[V][W]<0 ) /* 若有负边 */
                    return false; /* 不能正确解决，返回错误标记 */
                
                /* 若收录V使得dist[W]变小 */
                if ( dist[V]+ Graph->G[V][W] < dist[W] ) {
                    dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
                    path[W] = V; /* 更新S到W的路径 */
                }
            }  
        } // for循环结束, 每个V的邻接点W遍历完
    }// while结束
    return true;
}


// 多源最短路 Floyd算法
/* D[i][j]: Vi 到 Vj的最短路径, 初始值为Graph
   path[i][j]: Vi到Vj的最短路径上Vj的父顶点
*/
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


