//散列3 QQ帐户的申请与登陆 - 散列法
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define KEYLENGTH 16  // QQ号和密码的最大长度
#define MAXTABLESIZE 1000000

typedef char ElementType[KEYLENGTH+1]; 
typedef int Index;  // 散列地址类型

// 单链表定义
typedef struct LNode *PtrNode;
struct LNode
{
	ElementType Data;
	ElementType Password;
	PtrNode Next;
};
typedef PtrNode Position;
typedef PtrNode List;

typedef struct TblNode *HashTable;
struct TblNode  // 散列表结点
{
	int TableSize;
	List Heads;  // Heads是由 LNode 组成的一个列表
};

// 生成一个不小于TableSize, 但不大于MAXTABLESIZE的最小素数
int NextPrime(int N){
	int i, p= (N%2)? N+2:N+1; // p=大于N的下一个奇数

	while (p<=MAXTABLESIZE){
		for ( i = sqrt(p); i>2; i--){
			if (! (p % i))  // p被i整除,余数为0的时候
				break;
		}
		if (i==2) break; // for循环正常跳出,没有被i整除过,说明p是素数
		else p+=2;  // p不是素数,试探下一个奇数
	}
	return p;
}

// 构造并初始化HashTable
HashTable CreateTable(int TableSize)
{
	HashTable H;
	int i;


	H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = NextPrime(TableSize);

	// 分配链表头结点的数组Heads的空间
	H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
	// 初始化表头结点
	for(i=0; i<H->TableSize; i++){
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Password[0] = '\0';
		H->Heads[i].Next = NULL;
	}

	return H;
}


// 构造一个Hash函数
Index Hash(ElementType Key, int TableSize){
	unsigned long h = 0;
	char *ptr = Key;
	while (*ptr != '\0'){
		h = (h<<5) + *ptr;
		ptr++;
	}
	int p = (int)(h%TableSize);
	return p;
}

/* insert, 先找关键词,若已经存在就不需要再插入了,
若不存在先申请一个新结点,再插入到Heads[pos]的表头上 */
Position Find(HashTable H, ElementType Key){
	Position p;
	Index pos;

	pos = Hash(Key, H->TableSize);
	p = H->Heads[pos].Next;
	while(p && strcmp(p->Data, Key))  // p 不指向空,且未找到时(strcmp != 0 代表不同)
		p = p->Next;

	return p;  // 没找到是p为空,找到则指向那个LNode
}


void Insert(HashTable H, ElementType Key, ElementType PW){
	Position p, NewCell;
	Index pos;

	p = Find(H, Key);
	if (!p)	// 未找到关键词,可以插入 
	{
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);  // 把Key复制进去
		strcpy(NewCell->Password, PW);  // 把密码复制进去

		pos = Hash(Key, H->TableSize);
		// 插入到表头
		NewCell->Next = H->Heads[pos].Next;
		H->Heads[pos].Next = NewCell;
		printf("New: OK\n");
	}
	else  // 关键字已经存在
		printf("ERROR: Exist\n");

}

// 释放HashTable
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




int main(int argc, char const *argv[])
{
	char QQ[11];
	char PW[20];
	int i, j, N;
	char c;  // 命令符 L OR N
	Position pos;

	scanf("%d", &N);
	int TableSize = N/10;
	HashTable H = CreateTable(TableSize);
	
	for (i = 0; i < N; i++)
	{
		getchar();  // 读掉回车
		c = getchar(); // 读命令符
		scanf("%s %s", QQ, PW);

		if (c == 'N') // 命令N
			Insert(H, QQ, PW);
		else  // 命令L
		{
			pos = Find(H, QQ);
			if (pos){  // found
				if (!strcmp(pos->Password, PW))  // =0 相同
					printf("Login: OK\n");
				else
					printf("ERROR: Wrong PW\n");
			}
			else  // not found
				printf("ERROR: Not Exist\n");
		}
	}

	DestroyTable(H);

	return 0;
}


