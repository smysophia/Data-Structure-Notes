//05-树9 Huffman Codes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 1001
#define ElementType HuffmanTree
#define ERROR NULL
#define INFINITY 1000

/* ********* HuffmanTree ********************/
// 数据结构
typedef struct HTNode *HuffmanTree;
struct HTNode{
    int Weight;  // 结点的权值
    HuffmanTree Left;
    HuffmanTree Right;
};

/* ********* MinHeap ************************/

// 数据结构
typedef struct HNode *MinHeap;
struct HNode {
    ElementType *Data; // 存储堆元素的数组
    int Size;   // 堆的当前元素的个数
    int Capacity;  // 堆的最大容量
};

HuffmanTree mini;


// Create a heap
MinHeap CreateHeap(void)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType)); // 因为这里是一个数组,需要分配空间
    H->Size = 0; // 当前是空的
    H->Capacity = MaxSize;  // 堆的最大容量
    H->Data[0] = mini; /* 定义“哨兵”为小于堆中所有可能元素的值，便于以后操作 */
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

    // if (i > 1){  // 如果哨兵设置为NULL的话,在这里改一下, 当i=1的时候,直接让Data[1] = item;
    for(; H->Data[i/2]->Weight > item->Weight; i/=2){  // 其父节点大于它
        H->Data[i] = H->Data[i/2]; // 把它的父节点,向下过滤, 插入的item向上过滤
    } 
    // }
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
        (H->Data[child]->Weight > H->Data[child+1]->Weight)) 
            child++;
        
        /* 当temp比child的值小时跳出循环 */
        if (temp->Weight <= H->Data[child]->Weight) 
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
        if( (child != H->Size) && (H->Data[child]->Weight > H->Data[child+1]->Weight))
        {
            child++;
        }
        if (X->Weight <= H->Data[child]->Weight) 
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



/* ********* HuffmanTree *************/
// 数据结构
// typedef struct HTNode *HuffmanTree;
// struct HTNode{
//     int Weight;  // 结点的权值
//     HuffmanTree Left;
//     HuffmanTree Right;
// };

// 初始化
HuffmanTree CreateHuffman(){
    HuffmanTree HFT;
    HFT = (HuffmanTree) malloc(sizeof(struct HTNode));
    HFT->Left = NULL;
    HFT->Right = NULL;
    return HFT;
}

// Create
HuffmanTree Huffman(MinHeap H)
{ // 这里最小堆的元素类型ElementType为HuffmanTree  
    // 假设 H->Size个权值已经存在在 H->Data[]->Weight里了
    int i, N;
    HuffmanTree T;
    BuildMinHeap(H); // 将H->Data[]按照权重调整为最小堆
    N = H->Size;
    for(i=1; i < N; i++) // 做size-1次合并
    {
        T = (HuffmanTree)malloc(sizeof(struct HTNode)); // 建立新结点
        
        T->Left = DeleteMin(H);/*从最小堆中删除一个结点，作为新T的左子结点*/
        T->Right = DeleteMin(H);
        /*计算新权值*/
        T->Weight = (T->Left->Weight) + (T->Right->Weight);
        InsertMinHeap( H, T ); /*将新T插入最小堆*/
    }
    T = DeleteMin(H); // 最小堆中的最后一个元素就是指向Huffman树根节点的指针
    return T; 
}
/* ************************************* */

int main(int argc, char const *argv[])
{
    int N, i,f[MaxSize];
    char c[MaxSize];
    HuffmanTree HFT;
    // 设置哨兵,创建最小堆
    mini = CreateHuffman();
    mini->Weight = - INFINITY;
    MinHeap H = CreateHeap();

    scanf("%d", &N);
    H->Size = N;
    

    for(i=1; i<=N; i++){
        getchar();  // 读掉空格和回车
        scanf("%c %d", &c[i], &f[i]);
        HFT = (HuffmanTree) malloc(sizeof(struct HTNode));
        HFT->Left = NULL;
        HFT->Right = NULL;
        HFT->Weight = f[i];
        H->Data[i] = HFT;
    }

    // for(i=1; i<=N; i++){
    //     printf("%d ", H->Data[i]->Weight);
    // }
    // printf("\n");

    HFT = Huffman(H);  // 获得根节点的weight值

    printf("%d\n", HFT->Weight);

    return 0;
}


