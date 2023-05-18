#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    return (StackEmpty(Q.stack2));//判断用于存储元素的stack2是否为空
    //TODO
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //TODO
    DataType a;//临时保存的元素
    if(StackLength(Q->stack2)==MaxSize)//判断用于存储的栈是否为满栈
        return 0;//此时栈满，无法再插入元素
    //当栈不满时
    else
    {
        while(!StackEmpty(Q->stack2))
        {
            Pop(&Q->stack2,&a);
            Push(&Q->stack1,a);
        }//将栈stack2中的元素弹出，依次写入stack1
        Push(&Q->stack1,e);//将e压入栈stack1
        while (!StackEmpty(Q->stack1))
        {
            Pop(&Q->stack1,&a);
            Push(&Q->stack2,a);
        }//将stack1中的元素依次弹出，依次压入stack2,实现队列的存储顺序
        return 1;
    }
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO
    if(QueueEmpty(*Q))//判断队列是否为空
        return 0;//队列为空的时候返回0
    //当队列不为空的时候 即队列中元素
    else
    {
        Pop(&Q->stack2,e);//利用Pop函数将栈顶元素弹出 并用e接受
        return 1;
    }
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    if(QueueEmpty(Q))
    {
        return 0;
    }
    else
    {
        Pop(&Q.stack2,e);//获取队列头元素
        return 1;
    }

}

/**
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
    */
    //TODO
    int i =0;
    while (!QueueEmpty(Q))//当队列非空时，不断取出其头元素
    {
        DeQueue(&Q,&seq[i]);
        i++;
    }



}
