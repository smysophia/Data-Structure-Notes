//11-散列2 Hashing
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAXNUMBER 100000

typedef enum{Legitimate, Empty} EntryType;
typedef int ElementType;
typedef int index;

// 散列表单元类型
struct Cell
{
	ElementType Data;
	EntryType Info;

};

// 散列表类型
typedef struct TblNode *HashTable;
struct TblNode
{
	int TableSize;
	struct Cell* Cells;
};


int GetPrime (int N){
	int i,p = (N%2)? N:N+1;  // 若N是偶数N=N+1,若N是奇数N=N
	if(N<=2)
		return 2;
	if (N==3)
		return N;
	while(p<MAXNUMBER){
		for(i =sqrt(p); i>2; i--){
			if(!(p%i))  // 除尽, 不是素数
				break;
		}
		if (i==2)  
			break;
		else
			p += 2;
	}
	return p;
}


HashTable CreateTable(int TableSize){
	HashTable H;
	H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = GetPrime(TableSize);
	H->Cells = (struct Cell*)malloc(H->TableSize * sizeof(struct Cell));
	// Initialize
	for (int i=0; i<H->TableSize; i++){
		H->Cells[i].Data = 0;
		H->Cells[i].Info = Empty;
	}
	return H;
}

int Hash(HashTable H, ElementType Key){
	return Key % H->TableSize;
}

int Find(HashTable H, ElementType Key){
	int CurrentPos, NewPos;
	int CNum=0; // conflict number

	CurrentPos = NewPos = Hash(H, Key);
	while(H->Cells[NewPos].Info != Empty && CNum < 2*H->TableSize &&
		H->Cells[NewPos].Data != Key)
	{
		CNum++;
		NewPos = CurrentPos + CNum * CNum;
		if (NewPos > H->TableSize)
			NewPos %= H->TableSize;
	}
	if (CNum < 2*H->TableSize)
		return NewPos;
	else
		return -1; // 死循环,无位置可以插入
}

int Insert(HashTable H, ElementType Key){
	int pos = Find(H, Key);

	if (pos != -1){
		if (H->Cells[pos].Info != Legitimate){
			H->Cells[pos].Info = Legitimate;
			H->Cells[pos].Data = Key;
		}
	}
	
	return pos;
}



int main(int argc, char const *argv[])
{
	int M, N, i, Key, pos, flag=0;
	HashTable H;
	scanf("%d %d", &M, &N);
	H = CreateTable(M);

	for (i = 0; i < N; i++)
	{
		scanf("%d", &Key);
		pos = Insert(H, Key);
		if (pos != -1){
			if (flag == 0)
				flag = 1;
			else
				printf(" ");
			printf("%d", pos);
		}
		else{
			if (flag == 0)
				flag = 1;
			else
				printf(" ");
			printf("-");
		}
	}
	printf("\n");

	return 0;
}



