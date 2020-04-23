// 09-排序3 Insertion or Heap Sort 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define ElementType int


bool Identical(int A[],int B[],int N){
    for(int i=0;i<N;i++){
        if(A[i]!=B[i])
            return false;
    }
    return true;
}
/* *************** 插入排序 ****************** */
void Insertion_Sort(ElementType A[], int N, int Round){
    ElementType Tmp;
    int P, i;
    for(P=1; P<Round; P++){
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


int Heap_Sort(ElementType A[], ElementType B[], int N){
    int i;
    for (i=N/2; i>=0; i--)  // Build MaxHeap
        PercDown(A, i, N);
    for (i=N-1; i>0; i--){
        Swap(&A[0], &A[i]);  // DeleteMax
        PercDown(A, 0, i);  // 重新整理成最大堆  
        if (Identical(A, B, N)){  // 如果相同, 则再swap一次

            Swap(&A[0], &A[--i]);  // DeleteMax
            PercDown(A, 0, i);  // 重新整理成最大堆

            return 1;
        } 
             
    }
    return 0;
}


/* *************************************** */
int IsInsertion(ElementType A[], ElementType B[], int N){
	int i, j;
	for (i=0; i<N; i++){
		if (B[i] > B[i+1]) 
			break;
	}
	for(j=i+1; j<N; j++){
		if (A[j] != B[j])
			break;
	}
	if (j!=N)
		return 0;  // 是merge
	else 
		return i+1; // 是insertion,返回执行了几次
}


/* *************************************** */
int main(int argc, char const *argv[])
{
	int N ,i, T, flag=0;
	int *A, *B;
	scanf("%d\n",&N);
	A= malloc(N * sizeof(ElementType));
	B = malloc(N * sizeof(ElementType));
	for(i=0; i<N; i++){
        scanf("%d", &A[i]);
    }

    for(i=0; i<N; i++){
        scanf("%d", &B[i]);
    }

	i = IsInsertion(A, B, N);
	if (i){  // Insertion
		printf("Insertion Sort\n");
		Insertion_Sort(A, N, i+1);
	}
	else{  // Merge
		printf("Heap Sort\n");
		Heap_Sort(A, B, N);	
	}


	for(i=0; i<N; i++){
        	if(flag == 0)
            	flag = 1;
       		else
            	printf(" ");
        	printf("%d", A[i]);
    	}
   		printf("\n");


	return 0;
}
