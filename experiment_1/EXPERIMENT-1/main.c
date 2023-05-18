#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char StuID[11];
    int Grade;
    struct node *next;
} StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2)
{
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

/*�����ཻ����*/
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


/*��ӡ�����ڵ� */
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
* @brief ����ñ�ĳɼ����
* @param head ָ��ͷ����ָ��
*/
void outputStudentLinkedList(StudentLinkedListNode* head)
{
    StudentLinkedListNode *p;//��ʱָ�����
    p=head;//һ����ʼָ��ͷ����ָ��p
    //ѭ��������������
    while(p!=NULL)
    {
        printLinkedListNode(p);
        p=p->next;//��ָ��p������������printLinkedListNode������ӡÿ���ڵ������
    }
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
    //TODO
}


/**
* @brief �½�һ������node������
* @param student_id ������ַ�����������
* @param grade ����
* @return �����½��ɹ�������Ľ���ַ
*/
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade)
{
    StudentLinkedListNode* p=NULL;//һ����ָ��
    p=(StudentLinkedListNode*)malloc(sizeof(struct node));//�����ַ����̬�洢��
    strcpy(p->StuID,student_id);//�ַ�������ĸ�ֵ
    p->Grade=grade;
    p->next=NULL;
    return p;
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
    //TODO
}


/**
* @brief ���ս������ѧ���ĳɼ����,����������ͷָ��
* @param head ָ��ͷ����ָ��
* @param node ָ�����ָ�� ����Ҫ����Ľ��
* @return ��������ͷ����ַ
*/
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node)
{
    if (node == NULL)
    {
        return head;//��ֹjie���Ϊ��
    }
    node->next = head;//��node�ڵ����ͷ�ڵ�ǰ
    return node;//�����µ�����ͷָ��
    //TODO
}


/**
* @brief ��ת����
* @param head ָ��ͷ����ָ��
* @return ���ط�ת������ͷ���ĵ�ַ
*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head)
{
    if(head==NULL)//����Ϊ�յ�ʱ��
        return NULL;

    /**ָ���ϵΪ��pPre->pCur->pNext */
    StudentLinkedListNode *pPre=NULL;//pPre����ǰһ����㡰ǰһ��㡱
    StudentLinkedListNode *pCur=head;//pCur��ǰ��㡰��ǰ��㡱
    StudentLinkedListNode *rhead=NULL;//��ת����������µ�ͷָ��
    while(pCur!=NULL)
    {
        StudentLinkedListNode *pNext=pCur->next;//����ǰ������һ����㸳ֵ��*pNext
        if(pNext==NULL)//pNext����ָ�����һ����㡰��һ��㡱����ʱΪ����ֻ��һ�����
        {
            rhead=pCur;//��ǰ����Ϊͷ���
        }
        pCur->next=pPre;//����ǰһ��㡱��ֵ����ǰ������һ�����
        pPre=pCur;//��ǰһ���������Ϊ��ǰ�ڵ�
        pCur=pNext;//��ָ�����һ����㸳ֵ��ԭ���ġ���ǰ��㡱
    }
    return rhead;
    //TODO
}

/**
* @brief �ҵ��ཻ�ĵ�һ�����
* @param class1 ָ�����ָ�� ��������class1ͷ���ĵ�ַ
* @param class2 ָ�����ָ�� ��������class2ͷ���ĵ�ַ
* @return ���ص�һ���ཻ���ĵ�ַ
*/
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2)
{
    if(class1==NULL||class2==NULL)//����Ϊ�յ�ʱ��
    {
        return NULL;//��ò�Ҫ��NULL  main�������ص�ʱ���������
    }

    /*������Ϊ�յ�ʱ��*/
    StudentLinkedListNode *pa=class1;//paָ���һ������ͷ���
    StudentLinkedListNode *pb=class2;//pbָ��ڶ�������ͷ���
    /*ѭ��������������*/
    while(pa->next!=NULL&&pa!=pb)//����һ�������㲻Ϊ�ղ������������ͷ����ַ����ȵ�ʱ�򣬿�ʼ����ѭ��
        {
        pb=class2;//ÿ�α������֮�� ��Ҫ���´ӵڶ��������ͷ��㿪ʼ�ж� ÿ���ڽ�����һ��ѭ��֮ǰ ��pbָ��class2��ͷ���
        while(pb->next!=NULL&&pa!=pb)//���ڶ���������һ����㲻Ϊ�ղ���������������ͬ����ʱ��
        {
            pb=pb->next;//�����ڶ�������
        }
            //�ڶ���ѭ����������������Ҫô������� Ҫôpa=pb
            //�����Ҫ�жϷ����ĸ���������ѭ��
        if(pa==pb)
        {
            return pa;//��ֱ�ӷ��ص�һ���ཻ���ĵ�ַ
        }
        pa=pa->next;//����class1
    }
    if(pa==pb)
            return pa;

    //class1��class2�ں�һ������ȫ�غϣ������ڴ��ַ��ͬ�������ҳ������ؿ�ʼ�ཻ�ĵ�һ����㡣
    //�벻Ҫ�򵥵�ͨ�����ṹ��ĳ�Ա���жϡ�
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
        // �洢���ݵ�����
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

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
