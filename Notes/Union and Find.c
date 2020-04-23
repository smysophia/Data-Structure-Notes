// Union and Find
# define MAXN 1000
typedef int ElementType;  // 默认元素为非负整数0,1,2,3,...
typedef int SetName; // 默认用根节点的下标作为集合的名称


// 查找某个元素所在的集合,用根节点表示
// 方法一 直接用数组
typedef ElementType SetType[MAXN];  // 下标从0开始

SetName Find(SetType S, ElementType X){
	for(; S[X]>=0; X=S[X]);  // 跳出时 S[X] = -1, X为根节点下标
	return X;
}

// 方法二, 定义一个数据结构
typedef struct { 
    ElementType Data; 
    int Parent;  // 其父节点的下标
} SetType;

int Find(SetType S[], ElementType X)
{
    /* 在数组S中查找值为X的元素所属的集合, MAXN为数组最大长度 */
    int i;
    for(i=0; i<MAXN && S[i].Data != X; i++)
    if (i >= MAXN) // 未找到
        return -1;
    for(; S[i].Parent >= 0; i = s[i].Parent);  // 向上找它的父节点
    return i;
}

// 方法三, 路径压缩
SetName Find( SetType S, ElementType X )
{ 
    if ( S[X] < 0 ) /* 找到集合的根 */
        return X;
    else
        return S[X] = Find( S, S[X] ); /* 路径压缩 */
}




// 并
void Union( SetType S[], ElementType X1, ElementType X2 ) 
{
    int Root1, Root2;
    Root1 = Find(S, X1);
    Root2 = Find(S, X2);
    if( Root1 != Root2 )
        S[Root2].Parent = Root1;
}

//// 并(按秩)  按方法一实现
void Union( SetType S, SetName Root1, SetName Root2 )
{ /* 这里默认Root1和Root2是不同集合的根结点 */
    /* 保证小集合并入大集合 */
    if ( S[Root2] < S[Root1] ) { /* 如果集合2比较大 */
        S[Root2] += S[Root1];     /* 集合1并入集合2  */
        S[Root1] = Root2;
    }
    else {                         /* 如果集合1比较大 */
        S[Root1] += S[Root2];     /* 集合2并入集合1  */
        S[Root2] = Root1;
    }
}