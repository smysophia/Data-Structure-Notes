// 09-排序2 Insert or Merge
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define ElementType int


/* *************** 插入排序 ****************** */
void Insertion_Sort(ElementType A[], int N, int Round){ // Round 执行了几次
    ElementType Tmp;
    int P, i;
    for(P=0; P < Round; P++){
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

/* *************** 归并排序 ****************** */
void Merge(ElementType A[], ElementType TempA[],
    int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Tmp = L;  // 存放结果的数组的初始位置
    int Num = RightEnd - L + 1; // 一共有几个数据
    while (L <= LeftEnd && R <= RightEnd){  // 左和右都不为空
        if (A[L] <= A[R])
            TempA[Tmp++] = A[L++];
        else
            TempA[Tmp++] = A[R++];
    }
    // 跳出循环时左边还有剩下的
    while (L <= LeftEnd)
        TempA[Tmp++] = A[L++];
    // 跳出循环时右边还有剩下的
    while (R <= RightEnd)
        TempA[Tmp++] = A[R++];

    // 把TmpA倒回到A, 从RightEnd倒着复制回去
    for(int i=0; i<Num; i++){  // 重复Num次
        A[RightEnd] = TempA[RightEnd];
        RightEnd--;
    }
}

// 非递归算法
void Merge_Pass(ElementType A[], ElementType TmpA[],
    int N, int length)  // lenght =  当前有序子列的长度
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


bool Identical(int A[],int B[],int N){
	for(int i=0;i<N;i++){
		if(A[i]!=B[i])
			return false;
	}
	return true;
}

int Merge_sort(ElementType A[], ElementType B[], int N){
    int length = 1;
    ElementType *TmpA;  // 临时数组
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL){  // 分配空间成功
        while (length < N){
            Merge_Pass(A, TmpA, N, length);
            length *= 2;
            if (Identical(A, B, N)){  // 如果A B一样了, 则再做一次归并就退出
            	Merge_Pass(A, TmpA, N, length);
            	free(TmpA);
            	return 1;
            }
        }
        free(TmpA);
        return 1;
    }
    else
        return 0;
}

// 算法二
// void Merge_sort(ElementType A[], int N, int T){  // T为已Merge完成的次数
//     int length = pow(2,T);  // 有序子列长度
//     ElementType *TmpA;  // 临时数组
//     TmpA = malloc(N * sizeof(ElementType));
//     if (TmpA != NULL){  // 分配空间成功
//         Merge_Pass(A, TmpA, N, length);
//         free(TmpA);
//     }
//     else
//         printf("空间不足\n");
// }



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

// 算法二 返回已做了几次Merge
// int N_Merge(ElementType B[], int N)
// {
//  int i, j;
//  for (i=2; i<N; i*=2){
//      for (j=i; j<N; j+=2*i){
//          if (B[j-1]>B[j])
//              break;
//      }
//      if (j<N)
//          break;
//  }
//  return log(i)/log(2);
// }




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
		printf("Merge Sort\n");
		Merge_sort(A, B, N);	
	}

    // 算法二 Merge
    // else{  
    //     printf("Merge Sort\n");
    //     T = N_Merge(B, N);
    //     Merge_sort(B, N, T); // 对B再做一次Merge

    //     for(i=0; i<N; i++){
    //         if(flag == 0)
    //             flag = 1;
    //         else
    //             printf(" ");
    //         printf("%d", B[i]);
    //     }
    //     printf("\n");   
    // }




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
