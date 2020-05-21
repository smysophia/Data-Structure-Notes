//11-散列1 电话聊天狂人
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAXNUMBER 100000
#define KEYLENGTH 11
#define MAXD 5 // the last 5 numbers as key

typedef char ElementType[KEYLENGTH+1];

typedef struct LNode *PtrNode;
struct LNode
{
	ElementType Data;
	int Count;
	PtrNode Next;
};
typedef struct LNode* List;
typedef struct LNode* Position;

typedef struct TblNode *HashTable;
struct TblNode
{
	int TableSize;
	List Heads;
};

int GetPrime (int N){
	int i,p = (N%2)? N+2:N+1;
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
	int i;
	H = (HashTable) malloc(sizeof(struct TblNode));
	H->TableSize = GetPrime(TableSize);
	H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
	for (i = 0; i < H->TableSize; i++)
	{
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
		H->Heads[i].Count = 0;
	}
	return H;

}

int Hash(ElementType Key, int TableSize){  // 取手机号码的后5位作为keyword
	return atoi(Key + KEYLENGTH - MAXD) % TableSize;
}

Position Find(HashTable H, ElementType key){
	int pos;
	Position p;
	
	pos = Hash(key, H->TableSize);
	p = H->Heads[pos].Next;
	while(p && strcmp(p->Data, key)){  
		p = p->Next;
	}
	return p;
}


void Insert(HashTable H, ElementType Key){
	Position p, NewNode;
	int pos;

	p = Find(H, Key);
	if (!p){
		pos = Hash(Key, H->TableSize);
		NewNode =(Position)malloc(sizeof(struct LNode));
		strcpy(NewNode->Data, Key);
		NewNode->Count = 1;
		NewNode->Next = H->Heads[pos].Next;
		H->Heads[pos].Next = NewNode;
	}
	else{
		p->Count++;
	}
}

void DestroyTable(HashTable H){
	int i;
	Position p, tmp;

	for(i=0; i< H->TableSize; i++){
		p = H->Heads[i].Next;
		while(p){
			tmp = p->Next;
			free(p);
			p = tmp;
		}
	}
	free(H->Heads);
	free(H);
}


void ScanAndOutput(HashTable H){
	int maxnum=0;
	int i, repeat;
	ElementType maxphone;
	Position p;

	for(i=0; i<H->TableSize; i++){
		p = H->Heads[i].Next;
		while(p)
		{
			if(p->Count > maxnum){
				maxnum = p->Count;
				strcpy(maxphone, p->Data);
				repeat = 1;
			}
			else if(p->Count == maxnum){
				if ( strcmp(p->Data, maxphone) < 0)
					strcpy(maxphone, p->Data);
				repeat++;
			}
			p = p->Next;
		}
	}
	printf("%s %d", maxphone, maxnum);
	if (repeat > 1)
		printf(" %d\n", repeat);
	else
		printf("\n");

}




int main(int argc, char const *argv[])
{
	int n, i;
	ElementType phone;
	HashTable H;

	scanf("%d", &n);
	H = CreateTable(n*2);
	for(i=0; i<2*n; i++){
		scanf("%s", phone);
		Insert(H, phone);
	}
	ScanAndOutput(H);
	DestroyTable(H);
	return 0;
}



