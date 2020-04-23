#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); 
void Print( List L ); 

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

void attach(int c, List* pList){
    PtrToNode p = (PtrToNode)malloc(sizeof(struct Node));
    p->Data = c;
    p->Next = NULL;
    PtrToNode last = *pList;  // last指针指向pList的头指针所指向的
    if (last != 0){  // 如果链表不为空
        while( last-> Next != 0){  //就循环找到最后一个结点
            last = last-> Next;
        }
        last->Next = p;  //跳出循环的时候last指向最后一个结点,接上p
    }
    else
    {
        *pList = p; // 如果本身就是空链表,则pList的头指针 接上p
    }
}



List Read(){
    int N;
    scanf("%d", &N);
    int c;
    List list = NULL;
    
    
    while(N--){
        scanf("%d", &c);
        attach(c, &list);
    }
    return list;
}



void Print( List L ){
    PtrToNode temp;
    if (!L){
        printf("NULL\n");
        return;
    }
    for (temp = L; temp != NULL; temp = temp->Next){
        printf("%d ", temp->Data);
    }
    printf("\n");
}



List Merge( List L1, List L2 ){
    
    List L = NULL;
    while(L1&&L2)
    {
        if (L1->Data <= L2->Data){
            attach(L1->Data, &L);
            L1 = L1->Next;
        }else
        {
            attach(L2->Data, &L);
            L2 = L2->Next;
        }
    }
    
    for(; L1!=0; L1 = L1->Next){
        attach(L1->Data, &L);
    }

    for(; L2!=0; L2 = L2->Next){
        attach(L2->Data, &L);
    }

    return L;

}


// List Merge( List L1, List L2 ){
//     List L=(List)malloc(sizeof(struct Node));
//     List head = L;
//     List tmpL1 = L1->Next;
//     List tmpL2 = L2->Next;
//     while(tmpL1 && tmpL2){
//         if(tmpL1->Data < tmpL2->Data){
//             L->Next=tmpL1;
//             tmpL1=tmpL1->Next;
//         }else{
//             L->Next=tmpL2;
//             tmpL2=tmpL2->Next;
//         }
//         L=L->Next;
//     }
//     if(tmpL1)
//         L->Next=tmpL1;
//     if(tmpL2)
//         L->Next=tmpL2;
//     L1->Next = NULL;
//     L2->Next = NULL;
//     return head;
// } 

