#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 101
#define ElementType int
#define ERROR 999

/* ***************************** MaxHeap ***********************/

// struct
typedef struct HNode *MaxHeap;
struct HNode {
    ElementType *Data; // 存储堆元素的数组
    int Size;   // 堆的当前元素的个数
    int Capacity;  // 堆的最大容量
};



// Create a heap
MaxHeap CreateHeap(int Maxsize)
{
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType)); // 因为这里是一个数组,需要分配空间
    H->Size = 0; // 当前是空的
    H->Capacity = MaxSize;  // 堆的最大容量
    H->Data[0] = MaxSize; /* 定义“哨兵”为大于堆中所有可能元素的值，便于以后操作 */
    return H;
}

// Full
bool IsHeapFull(MaxHeap H){
    return (H->Size == H->Capacity);
}

// Empty
bool IsHeapEmpty(MaxHeap H){
    return (H->Size == 0);
}

// Insert a node to a maxheap
void InsertMaxHeap(MaxHeap H, ElementType item)
{
    int i;
    if (IsHeapFull(H)){
        printf("FULL\n");
        return;
    }
    i = ++H->Size;  // H->Size++; i = H->Size; 把新增元素放在末尾H->Size++的位置上
    for(; H->Data[i/2] < item; i/=2){  // 其父节点小于它
        H->Data[i] = H->Data[i/2]; // 把它的父节点,向下过滤, 插入的item向上过滤
    } 
    // 当它的父结点[i/2]比它大的时候, 跳出循环
    H->Data[i] = item;  // 填上item
}



// Delete the root(the maximum) from a maxheap
ElementType DeleteMax(MaxHeap H)
{
    int parent, child;
    ElementType MaxItem, temp;
    if(IsHeapEmpty(H)){
        printf("Empty\n");
        return ERROR;
    }

    MaxItem = H->Data[1]; // 取出最大值
    /* 用最大堆中最后一个元素从根节点开始向上过滤下层节点 */
    temp = H->Data[H->Size];  // 把堆中最后一个值,交给temp
    H->Size--;

    for(parent=1; parent*2 <= H->Size; parent=child)
    {
        child = parent*2;  // 左儿子

        /* child=左右儿子中大的那个, 当右儿子存在,且右儿子的值比左儿子大时,让child=右儿子 */
        if((child!= H->Size) && 
        (H->Data[child] < H->Data[child+1])) 
            child++;
        
        /* 当temp比child的值大时跳出循环 */
        if (temp >= H->Data[child]) 
            break;
        else 
            H->Data[parent] = H->Data[child]; //当parent < child,这个parent位置上变为child的值
    }
    H->Data[parent] = temp; 
    return MaxItem; 
}


// 堆的排序(建立最大堆) 把一个完全二叉树调整为最大堆
void PercDown( MaxHeap H, int p)
{// 下滤函数, 将Maxheap中以H->Data[p]为根的子堆调整为最大堆
    int parent, child;
    ElementType X;

    X = H->Data[p]; // 取出根节点的值
    for(parent =  p; parent*2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if( (child != H->Size) && (H->Data[child] < H->Data[child+1]))
        {
            child++;
        }
        if (X > H->Data[child]) 
            break;
        else // 将X下滤
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
}

void BuildMaxHeap(MaxHeap H){ // 调整H->Data[]中的元素,使满足最大堆的有序新,这里假设H->Size个元素已经存在H->Data中了
    int i;
    for(i = H->Size/2; i>0; i--) 
    {// 从最后一个结点的父节点(Size/2)开始,到根节点(1)为止
        PercDown(H, i);
    }
}



/* *************************** MinHeap ************************/

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

// Insert a node to a maxheap
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


// 堆的排序(建立最小堆) 把一个完全二叉树调整为最小堆
void PercDown( MinHeap H, int p)
{// 下滤函数, 将Minheap中以H->Data[p]为根的子堆调整为最小堆
    int parent, child;
    ElementType X;

    X = H->Data[p]; // 取出根节点的值
    for(parent =  p; parent*2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if( (child != H->Size) && (H->Data[child] > H->Data[child+1]))
        {
            child++;
        }
        if (X <= H->Data[child]) 
            break;
        else // 将X下滤
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
}

void BuildMinHeap(MinHeap H){ // 调整H->Data[]中的元素,使满足最小堆的有序新,这里假设H->Size个元素已经存在H->Data中了
    int i;
    for(i = H->Size/2; i>0; i--) 
    {// 从最后一个结点的父节点(Size/2)开始,到根节点(1)为止
        PercDown(H, i);
    }
}

/* ********************************************************* */







