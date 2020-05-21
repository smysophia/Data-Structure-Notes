// KMP 匹配算法
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSTRING 1000001
#define MAXPATTERN 100001
#define NotFound -1

void BuildMatch(char *pattern, int *match){
    int i, j;
    int m = strlen(pattern);
    match[0] = -1;
    for (j=1; j<m; j++){
        i = match[j-1];
        while (i>=0 && (pattern[i+1] != pattern[j]))  // 找到能对上的的pattern为止
            i = match[i];
        if (pattern[i+1] == pattern[j])
            match[j] = i+1;
        else
            match[j] = NotFound;
    }
}

int KMP(char *string, char *pattern){
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p;
    if (n < m) return NotFound;
    // match列表来放pattern的最大匹配值
    int *match;
    match = (int*)malloc(m * sizeof(int));
    BuildMatch(pattern, match);

    s=p=0;
    while(s < n && p < m){
        if (string[s] == pattern[p]){
            s++;
            p++;
        }
        else if(p > 0)  // p回撤到上一个match模块后一位, s不动,继续比较s和回撤后的p
            p = match[p-1] + 1;
        else s++; // p=0 pattern第一个就没有对上,移动s, p不动
    }
    return (p == m)? (s-m):NotFound;
}

int main(int argc, char const *argv[])
{
    char string[MAXSTRING];
    scanf("%s", string);
    char pattern[MAXPATTERN];
    int n;
    int p;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%s", pattern);
        p = KMP(string, pattern);
        if(p == NotFound)
            printf("Not Found\n");
        else
            printf("%s\n", string+p);
    }

    return 0;
}







