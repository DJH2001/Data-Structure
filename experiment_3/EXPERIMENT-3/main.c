#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode
{
    int id;
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode
{
    struct TreeNode *node; // ���е�ֵ�����������ڵ�ָ��
    struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue
{
    ListNodePtr dummyHead;
    ListNodePtr tail;
    int size;
} *QueuePtr;

// ��������Ľڵ�
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next)
{
    ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
    curr->node = node;
    curr->next = next;
    return curr;
}

// �������Ľڵ�
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right)
{
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr->id = TreeId++;
    curr->val = val;
    curr->left = left;
    curr->right = right;
    return curr;
}

// ��������г�ʼ��
QueuePtr InitQueue()
{
    QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
    TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
    queue->size = 0;
    queue->dummyHead = createListNode(dummyTreeNode, NULL);
    queue->tail = queue->dummyHead;
    return queue;
}

// �� queue ��β�����һ��Ԫ�صĸ���
void EnQueue(QueuePtr queue, TreeNodePtr node)
{
    ListNodePtr curr = createListNode(node, NULL);
    queue->tail->next = curr;
    queue->tail = queue->tail->next;
    queue->size++;
}

// ɾ�� queue �еĵ�һ��Ԫ��
void DeQueue(QueuePtr queue)
{
    if (queue->size == 0)
    {
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    ListNodePtr head = queue->dummyHead->next;
    queue->dummyHead->next = head->next;
    queue->size--;
    if (queue->size == 0) queue->tail = queue->dummyHead;
    free(head);
}

// ��� queue ��û��Ԫ��, ���� true
bool QueueEmpty(QueuePtr queue)
{
    return queue->size == 0;
}

// ���� queue �е�һ��Ԫ�ص�����
TreeNodePtr GetHead(QueuePtr queue)
{
    if (QueueEmpty(queue))
    {
        perror("error! the size of queue is zero when call front().");
        return NULL;
    }
    else
    {
        return queue->dummyHead->next->node;
    }
}


int max(int a, int b)
{
    return (a >= b) ? a : b;
}


// ������ת��Ϊ����
void getDigits(char *buff, int *data)
{
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        int num = 0;
        if (buff[i] == '#')
        {
            num = -1;
            i++;
        }
        else
        {
            while (buff[i] != ' ' && buff[i] != '\0')
            {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

// ���� dot ���ӻ��ļ�������Ȥ��ͬѧ����ѧϰ
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize)
{
    FILE *fp = fopen(filename, "w");    // �ļ�ָ��
    if (fp == NULL)     // ΪNULL�򷵻�
    {
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // ��ͷ
    // ���ò�α�������
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int id = 1;
    while (!QueueEmpty(queue))   // �����в��գ��������������򣬱�������
    {
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (curr == NULL) continue;
        fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr->id, curr->val);
        if (curr->left != NULL)   // ��������ӣ��������
        {
            EnQueue(queue, curr->left);
            fprintf(fp, "%d->%d;\n", curr->id, curr->left->id);
        }
        id++;
        // �м�����ڵ�
        fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
        fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr->id, id);
        if (curr->right != NULL)   // ������Һ��ӣ��Һ������
        {
            EnQueue(queue, curr->right);
            fprintf(fp, "%d->%d;\n", curr->id, curr->right->id);
        }
        id++;
    }
    fprintf(fp, "}\n"); // ��β
    fclose(fp); // �ر�IO
}


// ���ƶ�����ͼƬ,���� createDotFile ��ʹ�� system ִ������
void plot(TreeNodePtr tree_root, int i, int size, char *name)
{
    char tree_filename[50], paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);
}


// ɾ��������
void destoryTree(TreeNodePtr root)
{
    if (!root) return;
    if (root->left)
    {
        destoryTree(root->left);
        root->left = NULL;
    }
    if (root->right)
    {
        destoryTree(root->right);
        root->right = NULL;
    }
    free(root);
}

/** TODO:  ����һ������ͨ��������ʵ�ֲ�α��������������������ض�������ͷ��� */
TreeNodePtr createTreeWithLevelOrder(int *data, int size)
{
    int i=0;
    if(data[i]==-1||data[i]=='\0')//�ж����Ƿ���ڣ����������ڵ�ʱ��ֱ�ӷ���
    {
        return NULL;
    }
    TreeNodePtr m=NULL;//һ����ʱָ��
    QueuePtr Q=InitQueue();//��ʼ��һ������
    TreeNodePtr root=createTreeNode(data[i],NULL,NULL);//����һ�������
    EnQueue(Q,root);//���������
    int flag;
    i=1;//��data [0]��Ϊ-1��ʱ��i��1��ʼ
    while(!QueueEmpty(Q))//������Ϊ�յ�ʱ���˳�ѭ��
    {
        flag=0;//����һ����־
        if(data[i]>=0&&i<size)
        {
            m=createTreeNode(data[i],NULL,NULL);//����һ���µ������
            EnQueue(Q,m);//���
            GetHead(Q)->left=m;//�ô�ʱ����������ָ��m
            flag++;
        }
        i++;
        if(data[i]>=0&&i<size)
        {
            m=createTreeNode(data[i],NULL,NULL);
            EnQueue(Q,m);
            GetHead(Q)->right=m;
            flag++;
        }
        i++;
        /*��flag��Ϊ0ʱ����ʱ��������������if���� �ø�������*/
        if(flag!=0||i>size)
        {
            DeQueue(Q);
        }
    }
    return root;//�������ĸ����
}

/**
 * ================================================
 * ||                  ǰ�����                   ||
 * ================================================
 */
void preOrderTraverse(TreeNodePtr root)
{
    if(root!=NULL)//�ж����ĸ��ڵ��Ƿ�Ϊ�� �������Ϊ�յ�ʱ����������
    {
        printf("%d ",root->val);//��ӡ�����
        preOrderTraverse(root->left);//�ݹ�����������
        preOrderTraverse(root->right);//�ݹ��������Һ���

    }
}

/**
 * ================================================
 * ||                  �������                   ||
 * ================================================
 */
void inOrderTraverse(TreeNodePtr root)
{
    if(root!=NULL)//�жϸ�����Ƿ�Ϊ�� �������Ϊ�յ�ʱ����������
    {
        inOrderTraverse(root->left);//�ȵݹ�������е�����
        printf("%d ",root->val);//��ӡ���ֵ
        inOrderTraverse(root->right);//�ٵݹ�����Һ���
    }
}

/**
 * ================================================
 * ||                  �������                   ||
 * ================================================
 */
void postOrderTraverse(TreeNodePtr root)
{
    if(root!=NULL)//�жϸ�����Ƿ�Ϊ�� �������Ϊ�յ�ʱ����������
    {
        postOrderTraverse(root->left);//���ݺ����ȵݹ�������е�����ֱ�����Ϊ��
        postOrderTraverse(root->right);//�ٵݹ�������е��Һ���
        printf("%d ",root->val);//��ӡ���ֵ
    }
}

/** TODO: �����������ͨ��������ȱ�������ȡ�ö����������·���� */
int maxPathSum(TreeNodePtr root, int sum)
{
    int sumr;
    int suml;
    if(root==NULL)//�жϸ�����Ƿ�Ϊ�� �������Ϊ�յ�ʱ����������
    {
        return 0;
    }
    suml=maxPathSum(root->left,suml);//�ݹ���� �����ֵ
    sumr=maxPathSum(root->right,sumr);
    return max(suml,sumr)+root->val;//�ж�
}

/** ToDO: ������������ͨ���ݹ���ȡ�ö���������������ҶȨ��֮�� */
int sumOfLeftLeaves(TreeNodePtr root)
{
    if(root==NULL)//�ж����Ƿ�Ϊ��
    {
        return 0;
    }
    if(root->left!=NULL&&(root->left->left==NULL&&root->left->right==NULL))//�ж��Ƿ�Ϊ��Ҷ�ӽ��
    {
        return root->left->val + sumOfLeftLeaves(root->right);//��Ϊ��Ҷ�ӽ���ʱ��
    }

        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

/** TODO: �����ģ�����ͨ���ݹ���ȡ�����ľ��񣬼���ת�ö����� */
TreeNodePtr invertTree(TreeNodePtr root)
{
    TreeNodePtr temp;//��ʱ����
    if(root==NULL)//�ж����Ƿ�Ϊ��
    {
        return root;
    }
    /*���ڽ������ʵ�ַ�ת*/
    temp=root->left;
    root->left=root->right;
    root->right=temp;
    /*�ݹ����*/
    invertTree(root->left);
    invertTree(root->right);
    return root;
}


int main()
{

    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    char num[MAX_NUM];
    bool use_graphviz = false;
    /**
     * ===============================================================
     * ||                   End Configuration                       ||
     * ===============================================================
     */

    // printf("Read data...\n");
    FILE *fp = fopen("./test.txt", "r");
    if (!fp)
    {
        perror("���ļ�ʱ��������");
        return -1;
    }
    else
    {
        int i = 0;
        // printf("success!\n");
        /**
         * ===============================================================
         * ||                   Read data here                          ||
         * ===============================================================
         */
        while (fgets(num, MAX_NUM, fp) && fgets(buff, SIZE, fp))
        {
            char *nextline = strchr(buff, '\n');          //���һ��з�
            if (nextline)                            //���find��Ϊ��ָ��
                *nextline = '\0';                    //�Ͱ�һ�����ַ���������
            printf("Case %d, data: %s, nodes number: %s", i, buff, num);
            int size = atoi(num);
            int data[size];
            getDigits(buff, data);

            /**
             * ===============================================================
             * ||       ��������������Ȼ��Ҳ���������ⷽʽ�޸ĺ�����ԭ��          ||
             * ===============================================================
             */

            /** ����һ */
            TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);
            printf("Answer for task 1 is: \n");
            printf("preOrderTraverse is:");
            preOrderTraverse(tree_root);
            printf("\n");
            printf("inOrderTraverse is:");
            inOrderTraverse(tree_root);
            printf("\n");
            printf("postOrderTraverse is:");
            postOrderTraverse(tree_root);
            printf("\n");

            /** ͨ�� graphviz ���ӻ�����ɾ�����̲���ʹ�� */
            if (use_graphviz)
            {
                plot(tree_root, i, size, "tree");
            }

            /** ����� */
            int max_path_sum = maxPathSum(tree_root, 0);
            printf("Answer for task 2 is : %d \n", max_path_sum);

            /** ������ */
            int weight_sum = sumOfLeftLeaves(tree_root);
            printf("Answer for task 3 is : %d \n", weight_sum);

            /** ������ */
            TreeNodePtr invert_tree_root = invertTree(tree_root);
            printf("inOrderTraverse for task 4 is:");
            inOrderTraverse(invert_tree_root);
            printf("\n\n");

            /** ͨ�� graphviz ���ӻ�����ɾ�����̲���ʹ�� */
            if (use_graphviz)
            {
                plot(invert_tree_root, i, size, "invert_tree");
            }

            destoryTree(invert_tree_root);
            tree_root = invert_tree_root = NULL;
            i++;

        }

        /**
         * ===============================================================
         * ||                       End read                            ||
         * ===============================================================
         */
    }

    fclose(fp);

}
