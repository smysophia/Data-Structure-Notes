// 10-排序4 统计工龄
#include <stdlib.h>
#include <stdio.h>
#define ElementType int
#define MaxSize 100005

/* **************** 基数排序 *********************** */
#define MaxDigit 2  // 最大二位数
#define Radix 10  // 十进制

/* 桶元素结点 */
typedef struct Node *PtrNode;
struct Node
{
    int key;
    PtrNode next;
};

/* 桶头结点 */
struct HeadNode
{
    PtrNode head;
    PtrNode tail;
};
typedef struct HeadNode Bucket[Radix];


/* 返回整型关键字X的第D位数字 */
int GetDigit(int X, int D){
    // 默认次位D=1, 主位 D<= MaxDigit
    int d, i;
    for(i=1; i<=D; i++){
        d = X % Radix;
        X /= Radix;
    }
    return d;
}


// 次位优先(Least Significant Digit)排序
void LSDRadix_Sort(ElementType A[], int N){
    int D, Di, i;
    Bucket B;
    PtrNode tmp, p, List=NULL;

    // 初始化每个桶为空链表
    for(i=0; i<Radix; i++)
        B[i].head = B[i].tail = NULL;

    // 将原始序列A[], 逆序(插在链表头)存入链表List
    for(i=0; i<N; i++){
        tmp = (PtrNode)malloc(sizeof(struct Node));
        tmp->key = A[i];
        tmp->next = List;
        List = tmp;
    }

    // 开始排序
    for (D=1; D<= MaxDigit; D++){  // 对数据的每一位循环处理
        p=List;
        while(p)
        {
            Di = GetDigit(p->key, D);  // 获得当前元素的第D位数字
            // 从链表P中删除结点
            tmp = p;
            p = p->next;
            tmp->next = NULL;
            // 把结点插入到对应的B[Di]桶里
            if (B[Di].head == NULL)
                B[Di].head = B[Di].tail = tmp;
            else{
                B[Di].tail->next = tmp; // 把tmp加在尾部
                B[Di].tail = tmp;  // 尾部指向最后一个结点,即tmp
            }
        }  // while循环结束, 以第D位的分配完毕

        // D位数排完以后开始收集
        List = NULL;
        for(Di=Radix-1; Di >= 0; Di--)  // 将诶个桶的元素顺序收入List, 因为每次插入到List的头部,所以要从9开始收
        {
            if (B[Di].head){
                B[Di].tail->next = List;
                List = B[Di].head;
                B[Di].head = B[Di].tail = NULL;  // 清空桶
            }
        }
    }// 大for循环结束

    // 将List[]导入A[], 并释放空间
    for(i=0; i<N; i++){
        tmp = List;
        List = List->next;
        A[i] = tmp->key;
        free(tmp);
    }
}


/* *************** 插入排序 ****************** */
void Insertion_Sort(ElementType A[], int N){
    ElementType Tmp;
    int P, i;
    for(P=1; P<N; P++){
        Tmp = A[P]; // 摸下一张牌
        for (i = P; i>0; i--)
        {
            if(A[i-1] > Tmp) // 若前一张牌比新摸的牌大
                A[i] = A[i-1]; // 移出空位
            else break;  // 若新摸的牌比前一张牌大,则跳出循环
        }
        A[i] = Tmp; // 新牌落位

    }
}

/* *************** 希尔排序 ****************** */
void Shell_Sort(ElementType A[], int N){
    int D, P,i;

    ElementType Tmp;
    for (D=N/2; D>0; D/=2){ // 希尔排序增量
        for ( P=D; P<N; P++){  // 插入排序
            Tmp = A[P];
            for (i = P; i>=D && A[i-D]>Tmp; i-=D)
                A[i] = A[i-D]; // 移出空位
            A[i] = Tmp; // 新牌落位
        }
    }
}

/* *************** 堆排序 ****************** */
void Swap(ElementType *a, ElementType *b){
    ElementType c;
    c = *a;
    *a = *b;
    *b = c;
}


void PercDown(ElementType A[] , int p, int N)
{// 下滤函数, 将Minheap中以H->Data[p]为根的子堆调整为最小堆
    int parent, child;
    ElementType X;

    X = A[p]; // 取出根节点的值
    for(parent =  p; parent*2+1 <= N-1 ; parent = child)
    {
        child = parent*2+1;
        if( (child != N-1 ) && (A[child] < A[child+1]))
        {
            child++;
        }
        if (X >= A[child]) 
            break;
        else // 将X下滤
            A[parent] = A[child];
    }
    A[parent] = X;
}



void Heap_Sort(ElementType A[], int N){
    int i;
    for (i=N/2; i>=0; i--)  // Build MaxHeap
        PercDown(A, i, N);
    for (i=N-1; i>0; i--){
        Swap(&A[0], &A[i]);  // DeleteMax
        PercDown(A, 0, i);  // 重新整理成最大堆
    }
}
/* *************** 快速排序 ************************ */
ElementType Median3(ElementType A[], int Left, int Right){
    int Center = (Left + Right) / 2;
    // 整理成 A[Left] <= A[Center] <= A[Right]
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Right]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);

    // 将基准Pivot藏到右边Right-1处, 则之后只需考虑 A[Left+1] -> A[Right-2]
    Swap(&A[Center], &A[Right-1]);

    return A[Right-1];
}

void Qsort(ElementType A[], int Left, int Right){
    int Pivot, Cutoff, Low, High;
    // 如果序列元素足够多,则进入快排
    Cutoff = 1000;
    if (Cutoff <= Right - Left){
        Pivot = Median3(A, Left, Right);
        Low = Left;
        High = Right-1;
        while(1){
            while(A[++Low] < Pivot);  // 一直循环,直到A[Low] >= Pivot, 停住
            while(A[--High] > Pivot);  // 一直循环,直到A[Hight] <= Pivot, 停住
            if (Low<High)
                Swap(&A[Low], &A[High]);
            else // Low > High 子序列排序结束
                break;
        }
        Swap(&A[Low], &A[Right-1]);  // 将Pivot归位,此时 Low>High, 所以Pivot和Low交换
        Qsort(A, Left, Low-1);   // 递归Pivot左边
        Qsort(A, Low+1, Right);    // 递归Pivot右边
    }
    else // 元素太少,用简单排序
        Insertion_Sort(A+Left, Right-Left+1);  // 待排序列表A从Left开始,即A+Left, 长度是R-L+1
}

void Quick_Sort(ElementType A[], int N){
    Qsort(A, 0 ,N-1);
}

/* *************** 归并排序 ****************** */
void Merge(ElementType A[], ElementType TmpA[],
    int L, int R, int RightEnd)
{
    int LeftEnd, Num, Tmp;
    int i;
    LeftEnd = R - 1;
    Tmp = L;  // 存放结果的数组的初始位置
    Num = RightEnd - L + 1; // 一共有几个数据
    while (L <= LeftEnd && R <= RightEnd){  // 左和右都不为空
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    // 跳出循环时左边还有剩下的
    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++];
    // 跳出循环时右边还有剩下的
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++];

    // 把TmpA倒回到A, 从RightEnd倒着复制回去
    for(i=0; i<Num; i++){  // 重复Num次
        A[RightEnd] = TmpA[RightEnd];
        RightEnd--;
    }
}

void Merge_Pass(ElementType A[], ElementType TmpA[], int N, int length)  // lenght =  当前有序子列的长度
{
    int i,j;
    for (i=0; i <= N-2*length; i+=2*length) // 留两个length,分情况讨论
        Merge(A, TmpA, i, i+length, i+2*length-1); // A TmpA L R RightEnd
    if (i+length < N) // 归并最后两个子列
        Merge(A, TmpA, i, i+length, N-1);
    else  // 最后只剩一个子列, 则复制过来
        for (j=i; j<N; j++)
            TmpA[j] = A[j];
}

void Merge_sort(ElementType A[], int N){
    int length = 1;
    ElementType *TmpA;  // 临时数组
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL){  // 分配空间成功
        while (length < N){  // 有序子列长度等于N,则完成,跳出循环
            Merge_Pass(A, TmpA, N, length);
            length *= 2;
            Merge_Pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else
        printf("空间不足\n");
}

/* ********************************************* */
int main(int argc, char const *argv[])
{
    int N, i;
    int A[MaxSize];
    scanf("%d", &N);
    for (i=0; i<N; i++){
        scanf("%d", &A[i]);
    }

    // LSDRadix_Sort(A, N);
    // Insertion_Sort(A, N);
    // Shell_Sort(A, N);
    // Heap_Sort(A, N);
    // Quick_Sort(A, N);
    Merge_sort(A,N);

    int cnt =1;
    for(i=0; i<N-1; i++){
        if (A[i] == A[i+1])
            cnt++;
        else{
            printf("%d:%d\n", A[i], cnt);
            cnt = 1;
        }
    }

    printf("%d:%d\n", A[N-1], cnt);
    

    return 0;
}

