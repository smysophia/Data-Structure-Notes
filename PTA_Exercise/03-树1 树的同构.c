#include <stdio.h>
#define ElementType char
#define null -1
#define Tree int
#define MaxTree 10

typedef struct TreeNode tree;
struct TreeNode
{
    ElementType element;
    Tree left;
    Tree right;
}T1[MaxTree], T2[MaxTree];

int BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1, Tree R2);




int main(int argc, char const *argv[])
{
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    // printf("R1=%d\n", R1);
    // printf("R2=%d\n", R2);
    if(Isomorphic(R1,R2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

Tree BuildTree(struct TreeNode T[])
{
    int N, i;
    Tree Root = null;
    char cl, cr;
    scanf("%d", &N);
    if(N)
    {
         /* 设置一个列表,初始化为0 */
        int check[N];
        for (i=0; i<N; i++) check[i] = 0;  
        
        for(i=0; i<N; i++)
        {
            scanf("%*c %c %c %c", &T[i].element, &cl, &cr);  // 先以字符读入
            if (cl != '-')
            {
                T[i].left = cl - '0';
                check[T[i].left] = 1; // check列表里,把T[i].left位上设为1
            }else T[i].left = null;  // 设为-1
            
            if (cr != '-')
            {
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }else T[i].right = null;  // 设为-1
        }
        
        

        // 遍历列表 check
        for (i=0; i<N; i++){
            if (check[i] == 0) break;
        }
        Root = i;

    }
    return Root;

}


int Isomorphic(Tree R1, Tree R2)
{
    // both empty
    if ( (R1==null) && (R2==null) ) return 1;
    // one of them are empty
    if ( ((R1==null) && (R2!=null)) || ((R1!=null) && (R2==null)) ) return 0;
    // root are different
    if ( T1[R1].element != T2[R2].element) return 0;
    // both have no left subtree
    if ( (T1[R1].left == null) && (T2[R2].left == null))
        // compare their right subtree
        return Isomorphic( T1[R1].right, T2[R2].right);
    // both left are not empty AND their left elements are same
    if ( ((T1[R1].left != null) && (T2[R2].left != null)) &&
        ((T1[T1[R1].left].element) == (T2[T2[R2].left].element)))
        // compare letf to left, right to right
        return ( Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right) );
    
    /* else situations:
    1. both left are not empty BUT their left elements are NOT same
    2. lett is emptry, right is not empty
    3. left is not empty, right is empty */
    else
        // need to swap the left and right
        return (Isomorphic(T1[R1].left, T2[R2].right)) && (Isomorphic(T1[R1].right, T2[R2].left));

}

