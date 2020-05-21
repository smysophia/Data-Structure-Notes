//散列3 QQ帐户的申请与登陆 - 排序法(会超时)
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct Node* List;
struct Node
{
	unsigned long QQ;
	char PW[20];
};

int compare(const void *a, const void *b)
{ 
    if (((List)a)->QQ > ((const List)b)->QQ)
    	return 1;
    else if(((List)a)->QQ < ((const List)b)->QQ)
    	return -1;
    else
    	return 0;
}

int BinarySearch(List list, unsigned long QQ, int N){
	int Left, Right, Mid;
    Left = 0;
    Right = N-1;

    while (Left <= Right){
        Mid = (Left + Right) / 2;
        if (QQ > list[Mid].QQ)
            Left = Mid + 1;
        else if (QQ < list[Mid].QQ)
            Right = Mid - 1;
        else // 相等,找到了
            return Mid;
    }
    return -1;
}


int main(int argc, char const *argv[])
{
	unsigned long QQ;
	char PW[20];
	int i, j, N, cnt=0;
	char c;  // 命令符 L OR N
	scanf("%d", &N);
	List list  = (List)malloc(sizeof(struct Node) * N);
	for (i = 0; i < N; i++)
	{
		getchar();  // 读掉回车
		c = getchar();
		scanf("%lu %s", &QQ, PW);
		
		list[cnt].QQ = 0;
		list[cnt].PW[0]='\0';


		// 命令N
		if (c == 'N'){
			j = BinarySearch(list, QQ, cnt);
			if (j != -1){ // 找到
				printf("ERROR: Exist\n");
			}
			else  // j=-1 没找到
			{
				printf("New: OK\n");
				list[cnt].QQ = QQ;
				strcpy(list[cnt].PW, PW);
				cnt++;
				qsort(list, cnt, sizeof(struct Node), compare); // 按qq号从小到大排序
			}
		}

		// 命令L
		else
		{
			j = BinarySearch(list, QQ, cnt);
			if (j != -1)  // 找到
			{
				if(!strcmp(list[j].PW, PW))  //strcmp = 0 相等
					printf("Login: OK\n");
				else
					printf("ERROR: Wrong PW\n");
			}
			else  // j=-1 没找到
				printf("ERROR: Not Exist\n");
		}
	}

	return 0;
}


