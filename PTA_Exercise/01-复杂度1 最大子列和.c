#include <stdio.h>

int MaxSubseqSum4( int A[], int N );

int main(){
	int N;
	scanf("%d", &N);
	int A[N];
	for(int i = 0; i<N; i++){
		scanf("%d", &A[i]);
	}
	
	int MaxSum = 0;
	MaxSum = MaxSubseqSum4( A, N );
	printf("%d\n", MaxSum);

}


int MaxSubseqSum4( int A[], int N )
{ 
	int ThisSum, MaxSum;
	int i;
	ThisSum = MaxSum = 0;
	for( i = 0; i < N; i++ ) {
		ThisSum += A[i]; /* 向右累加 */ 
		if( ThisSum > MaxSum )
			MaxSum = ThisSum; /* 发现更大和则更新当前结果 */ 
		else if( ThisSum < 0 ) /* 如果当前子列和为负 */
			ThisSum = 0; /* 则不可能使后面的部分和增大，抛弃之 */ }
	return MaxSum;
}
