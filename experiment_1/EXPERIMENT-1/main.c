#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char StuID[11];
    int Grade;
    struct node *next;
} StudentLinkedListNode;


/* 创建相交链表 */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2)
{
    // a和b后面若干结点值相同
    // beforeCross1为跳过的a中的个数，从第beforeCross1 + 1个结点开始相交
    // beforeCross2为跳过的b中的个数，从第beforeCross2 + 1个结点开始相交
    // 相交方法是将b中的前一结点指向a中的首个相交结点
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //销毁野指针结点
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

/*销毁相交链表*/
void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode)
{
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode)
    {
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode)
    {
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}


/*打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node)
{
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL)
    {
        printf("->");
    }
    else
    {
        printf("\n");
    }

}


/**
* @brief 输出该表的成绩情况
* @param head 指向头结点的指针
*/
void outputStudentLinkedList(StudentLinkedListNode* head)
{
    StudentLinkedListNode *p;//临时指针变量
    p=head;//一个初始指向头结点的指针p
    //循环遍历整个链表
    while(p!=NULL)
    {
        printLinkedListNode(p);
        p=p->next;//用指针p遍历链表，并用printLinkedListNode函数打印每个节点的数据
    }
    // 用于单个节点输出的函数printLinkedListNode已提供
    //请你实现遍历链表的逻辑
    //TODO
}


/**
* @brief 新建一个链表node并返回
* @param student_id 传入的字符串数组名称
* @param grade 分数
* @return 返回新建成功后链表的结点地址
*/
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade)
{
    StudentLinkedListNode* p=NULL;//一个空指针
    p=(StudentLinkedListNode*)malloc(sizeof(struct node));//分配地址（动态存储）
    strcpy(p->StuID,student_id);//字符串数组的赋值
    p->Grade=grade;
    p->next=NULL;
    return p;
    //tips:malloc的时候记得为转化为结构体指针
    //TODO
}


/**
* @brief 按照降序插入学生的成绩情况,并返回链表头指针
* @param head 指向头结点的指针
* @param node 指向结点的指针 传入要插入的结点
* @return 返回链表头结点地址
*/
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node)
{
    if (node == NULL)
    {
        return head;//防止jie结点为空
    }
    node->next = head;//将node节点插在头节点前
    return node;//返回新的链表头指针
    //TODO
}


/**
* @brief 反转链表
* @param head 指向头结点的指针
* @return 返回反转后链表头结点的地址
*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head)
{
    if(head==NULL)//链表为空的时候
        return NULL;

    /**指向关系为：pPre->pCur->pNext */
    StudentLinkedListNode *pPre=NULL;//pPre代表前一个结点“前一结点”
    StudentLinkedListNode *pCur=head;//pCur当前结点“当前结点”
    StudentLinkedListNode *rhead=NULL;//反转过后链表的新的头指针
    while(pCur!=NULL)
    {
        StudentLinkedListNode *pNext=pCur->next;//将当前结点的下一个结点赋值给*pNext
        if(pNext==NULL)//pNext代表指向的下一个结点“下一结点”，此时为链表只有一个结点
        {
            rhead=pCur;//则当前结点就为头结点
        }
        pCur->next=pPre;//将“前一结点”赋值给当前结点的下一个结点
        pPre=pCur;//将前一个结点设置为当前节点
        pCur=pNext;//将指向的下一个结点赋值给原来的“当前结点”
    }
    return rhead;
    //TODO
}

/**
* @brief 找到相交的第一个结点
* @param class1 指向结点的指针 传入链表class1头结点的地址
* @param class2 指向结点的指针 传入链表class2头结点的地址
* @return 返回第一个相交结点的地址
*/
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2)
{
    if(class1==NULL||class2==NULL)//链表为空的时候
    {
        return NULL;//最好不要用NULL  main函数返回的时候会有问题
    }

    /*当链表不为空的时候*/
    StudentLinkedListNode *pa=class1;//pa指向第一个链表头结点
    StudentLinkedListNode *pb=class2;//pb指向第二个链表头结点
    /*循环遍历两个链表*/
    while(pa->next!=NULL&&pa!=pb)//当第一个链表结点不为空并且两个链表的头结点地址不相等的时候，开始进入循环
        {
        pb=class2;//每次遍历完成之后 需要重新从第二个链表的头结点开始判断 每次在进入下一个循环之前 将pb指向class2的头结点
        while(pb->next!=NULL&&pa!=pb)//当第二个链表下一个结点不为空并且两个链表无相同交点时候
        {
            pb=pb->next;//遍历第二个链表
        }
            //第二个循环跳出来的条件是要么遍历完成 要么pa=pb
            //因此需要判断符合哪个条件跳出循环
        if(pa==pb)
        {
            return pa;//即直接返回第一个相交结点的地址
        }
        pa=pa->next;//遍历class1
    }
    if(pa==pb)
            return pa;

    //class1和class2在后一部分完全重合（结点的内存地址相同），请找出并返回开始相交的第一个结点。
    //请不要简单地通过结点结构体的成员来判断。
    //TODO
}

int main()
{
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2))
    {
        class1 = class2 = NULL;
        // 存储数据到链表
        for(i = 0; i < num1; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0; i < num2; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 反转链表
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 生成相交链表
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // 打印相交结点
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //销毁相交链表
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
