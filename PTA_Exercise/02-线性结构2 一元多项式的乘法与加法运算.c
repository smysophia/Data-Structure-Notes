#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct PolyNode *Polynomial;
struct PolyNode {
    ElementType coef;
    ElementType expon;
    Polynomial link;
};
typedef Polynomial List;

List Read(); 
void Print( List L ); 
Polynomial Add(Polynomial P1, Polynomial P2);
Polynomial Multi(Polynomial P1, Polynomial P2);

int main()
{
    Polynomial L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Multi(L1, L2);
    Print(L);
    L = Add(L1, L2);
    Print(L);
    return 0;
}

void attach(int c, int e, Polynomial *pRear){
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->coef = c;
    p->expon = e;
    p->link = NULL;
    (*pRear)->link = p; // 连上p
    *pRear = p;  //pRear往后移一位指向p
}



List Read(){
    int N, c, e;
    scanf("%d", &N);
    Polynomial P, Rear, t;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); // 插入一个空结点
    P->link = NULL;
    Rear = P;
    while(N--){
        scanf("%d %d", &c, &e);
        attach(c, e, &Rear);
    }
    // 释放掉空结点
    t = P;
    P = P->link;
    free(t);
    return P;
    
}


void Print( List L ){
    Polynomial temp;
    // 如果链表为空,打印0 0
    if (L == NULL){
        printf("0 0\n");
        return;
    }
    int tag = 0; //控制开头的空格

    // 打印每一项
    for (temp = L; temp != NULL; temp = temp->link){
        if (tag == 0){
            tag = 1;
        }else
        {
            printf(" ");
        }
        printf("%d %d", temp->coef, temp->expon);
    }
    printf("\n");
}

Polynomial Add(Polynomial P1, Polynomial P2){
    Polynomial P, Rear, t1, t2, t;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); // 插入一个空结点
    P->link = NULL;
    Rear = P;
    t1 = P1;
    t2 = P2;
    while (t1 && t2){
        if(t1->expon == t2->expon) // expon相同
        {
            int sum;
            sum = t1->coef + t2->coef;
            if (sum != 0) attach(sum, t1->expon, &Rear);
            t1 = t1->link;
            t2 = t2->link;
        }
        else if(t1->expon > t2->expon) // t1的expon大
        {
            attach(t1->coef, t1->expon, &Rear);
            t1 = t1->link;
        }
        else // t2的expon大
        {
            attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }
    while(t1){
        attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while(t2){
        attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }
    // 释放空结点
    t = P;
    P = P->link;
    free(t);
    return P;
}

Polynomial Multi(Polynomial P1, Polynomial P2)
{
    Polynomial P, Rear, t1, t2, t;
    int c, e;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    t1 = P1;
    t2 = P2;
    // 若P1或P2为空,则返回null
    if(!t1||!t2) return NULL;

    // P1第一项乘以P2每一项, 放入P
    while(t2){
        c = t1->coef * t2->coef; //系数相乘,指数相加
        e = t1->expon + t2->expon;
        attach(c, e, &Rear); 
        t2 =  t2->link;
    }
    t1 = t1->link;// 从t1第二项开始,遍历t1和t2,得到结果与P比较,插入
    while(t1){
        t2 = P2;
        Rear = P;
        while(t2)
        {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon > e)
            {// Rear一直移到 Rear所指的Node 的link所指的Node 的expon不大于e
                Rear =  Rear->link;  
            }
            if(Rear->link && Rear->link->expon == e)
            { // 下一项的expon和e相等;
                if(Rear->link->coef + c != 0)
                {  // 指数相加不为0
                    Rear->link->coef += c;  // 原指数加上新指数
                }
                else
                { // 指数相加等于0, 释放掉Rear->link所指的Node
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }else
            {  // 小于e时,插入到Rear的后面,下一个Node的前面
                t= (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;  // t的link指向Rear指向的后一个结点
                Rear->link = t;     // 连上t
                Rear = Rear->link; // Rear往后移
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    // 释放空结点
    t = P;
    P = P->link;
    free(t);
    return P;
}



