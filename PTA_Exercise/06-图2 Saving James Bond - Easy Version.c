// 06-图2 Saving James Bond - Easy Version
include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 101

struct crocodile
{
    int hori;
    int vert;
    bool shore;
    bool jump;
    bool visited;
};
typedef struct crocodile croco[MAX];
croco c;  // 全局变量数组c,每一项都是struct crocodile
int safe = 0; // 全局变量

int Distance(int x1, int y1, int x2, int y2){
    int distance = (int)sqrt( pow((y2-y1), 2) + pow((x2-x1), 2));
    return distance;
}

bool NearShore(int x, int y, int D){
    if((50 -abs(x)) <= D || (50-abs(y)) <= D )
        return true;
    else
        return false;
}

bool FirstJump(int x, int y, int D){
    int dist = (int)sqrt(pow(x,2)+pow(y,2));
    if( dist <= D + 15/2)
        return true;
    else
        return false;
}

// 初始化
void Initial(int N, int D){
    int x, y;
    for(int i=0; i<N; i++){
        scanf("%d %d", &x,&y);
        c[i].hori = x;
        c[i].vert = y;
        c[i].shore = NearShore(x, y, D);
        c[i].jump = FirstJump(x, y, D);
        c[i].visited = false;
    }
}

// DFS遍历
bool DFS(struct crocodile *v, int N, int D){
    int dist;
    v->visited = true;
    if (v->shore)
        safe = 1;
    for(int i=0; i<N; i++){
        dist = Distance(v->hori, v->vert, c[i].hori, c[i].vert);
        if( dist <= D && (c[i].visited == false))
             DFS(&c[i], N, D);
    }
    return safe;
    
}



int main(int argc, char const *argv[])
{
    int N, D, i;
    scanf("%d %d", &N, &D);
    Initial(N, D);
    bool result = false;

    for(i=0; i<N; i++){
        if(c[i].jump){// 找第一跳的鳄鱼
            result = DFS(&c[i], N, D);
            if (result){
                printf("Yes\n");
                return 0;
            }
        }
    }
    printf("No\n");


    return 0;
}

