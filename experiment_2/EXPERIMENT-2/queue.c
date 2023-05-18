#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    return (StackEmpty(Q.stack2));//�ж����ڴ洢Ԫ�ص�stack2�Ƿ�Ϊ��
    //TODO
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    DataType a;//��ʱ�����Ԫ��
    if(StackLength(Q->stack2)==MaxSize)//�ж����ڴ洢��ջ�Ƿ�Ϊ��ջ
        return 0;//��ʱջ�����޷��ٲ���Ԫ��
    //��ջ����ʱ
    else
    {
        while(!StackEmpty(Q->stack2))
        {
            Pop(&Q->stack2,&a);
            Push(&Q->stack1,a);
        }//��ջstack2�е�Ԫ�ص���������д��stack1
        Push(&Q->stack1,e);//��eѹ��ջstack1
        while (!StackEmpty(Q->stack1))
        {
            Pop(&Q->stack1,&a);
            Push(&Q->stack2,a);
        }//��stack1�е�Ԫ�����ε���������ѹ��stack2,ʵ�ֶ��еĴ洢˳��
        return 1;
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    if(QueueEmpty(*Q))//�ж϶����Ƿ�Ϊ��
        return 0;//����Ϊ�յ�ʱ�򷵻�0
    //�����в�Ϊ�յ�ʱ�� ��������Ԫ��
    else
    {
        Pop(&Q->stack2,e);//����Pop������ջ��Ԫ�ص��� ����e����
        return 1;
    }
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
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
        Pop(&Q.stack2,e);//��ȡ����ͷԪ��
        return 1;
    }

}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
    int i =0;
    while (!QueueEmpty(Q))//�����зǿ�ʱ������ȡ����ͷԪ��
    {
        DeQueue(&Q,&seq[i]);
        i++;
    }



}
