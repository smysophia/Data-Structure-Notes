// 10-排序5 PAT Judge
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define ElementType int
#define MaxUser 10005
#define MaxProb 6

struct NScore
{
    int ID;
    int s[MaxProb];
    int total_score;
    int perfect;
    int rank;
    bool enable;
};
struct NScore Student[MaxUser];

int compare3keys(const void *a, const void *b){
    int k;
    // 对total_score做降序排序
    if ( ((const struct NScore*)a)->total_score < ((const struct NScore*)b)->total_score)
        k = 1;
    else if(((const struct NScore*)a)->total_score > ((const struct NScore*)b)->total_score)
        k =  -1;
    else
    { // total_score相等, 按perfect降序排序
        if (((const struct NScore*)a)->perfect < ((const struct NScore*)b)->perfect)
            k = 1;
        else if (((const struct NScore*)a)->perfect > ((const struct NScore*)b)->perfect)
            k = -1;
        else  // total_score相等,perfect也相等, 则按ID做升序排序
        { 
            if(((const struct NScore*)a)->ID < ((const struct NScore*)b)->ID)
                k = -1;
            else if (((const struct NScore*)a)->ID > ((const struct NScore*)b)->ID)
                k = 1;
            else
                k = 0;
        }
    }
    return k;
}
    

int main(int argc, char const *argv[])
{
    int N, K, M, i, j, cnt;
    int user_id, problem_id, partial_score;
    int p[MaxProb];
    scanf("%d %d %d", &N, &K, &M);
    for (i=1; i<=K; i++) // 从p[1]到p[K]
        scanf("%d", &p[i]);

   // 初始化Student[]
    for (i=1; i<=N; i++){  // 从Student[1] 到 Student[N]
        Student[i].ID = i;
        Student[i].enable = false;  // 初始化为都不可见
        for (j=1; j<=K; j++)  // 从s[1] 到 s[k]
            Student[i].s[j] = -2;
        Student[i].total_score = Student[i].perfect = Student[i].rank = 0;
    }
    Student[0].total_score = -1;  // Student[0]的数据不要,设置为负数

    // 读M次提交
    for (i=0; i<M; i++){
        scanf("%d %d %d", &user_id, &problem_id, &partial_score);
        if (partial_score > -1)
            Student[user_id].enable = true;  // 只要编译通过, 0分也可见
        if (partial_score > Student[user_id].s[problem_id])
            Student[user_id].s[problem_id] = partial_score; 
    }


    // 计算total_score和perfect的数目
    for (i=1; i<=N; i++){  // 从Student[1] 到 Student[N]
        for (j=1; j<=K; j++)  // 从s[1] 到 s[k]
        {
            if (Student[i].s[j]>0){
                Student[i].total_score += Student[i].s[j];
                if(Student[i].s[j] == p[j])
                    Student[i].perfect++;
            }
        }
    }

    // 开始排序
    qsort(Student, N+1, sizeof(struct NScore), compare3keys);   // N+1 因为要排到Student[N],包含[0], 总排数据为N+1个


    // 计算rank
    cnt = 0;
    for (i=0; i<N; i++){
        if(Student[i].total_score != Student[i+1].total_score){
            Student[i].rank = i-cnt+1;
            cnt = 0;  // 无相同项, cnt清零
        }
        else{
            Student[i].rank = i-cnt+1;
            cnt++;
        }

    }


    // 按格式输出
    for (i=0; i<N; i++){
        if (Student[i].enable) // 只输可见的(有题提交且通过编译)
        {
            printf("%d %05d %d", Student[i].rank, Student[i].ID, Student[i].total_score);
            for(j=1; j<=K; j++)
            {
                if(Student[i].s[j] == -2) // 没有提交
                    printf(" -");
                else if (Student[i].s[j] == -1)  // 提交但没通过编译
                    printf(" 0");
                else  //有分的
                    printf(" %d", Student[i].s[j]);
            }
            printf("\n");
        }    
    }

    return 0;
}