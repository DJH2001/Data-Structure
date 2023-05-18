#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000
typedef char vextype[20];
typedef struct
{
    int N, E;//N�Ƕ�������E�Ǳ���
    int **matrix;//�����ڽӾ���
    vextype *vertex;//�洢�ڵ������
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void DFS(Graph g, int v, int visited[]);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
int max(int x,int y);
int min(int x,int y);

/**
 * ����һ���ڵ���Ϊn��ͼ
 * @param n �ڵ����
 * @return �������ͼ
 */
Graph createGraph(int n)
{
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++)
    {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++)
    {
        for (j = 0; j < g.N; j++)
        {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++)
    {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param path ����·��������
 * @param g ͼ
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do
    {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    }
    while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int isConnected(Graph g)
{
    //TODO
    //���������������ֱ�ӻ���ͨ������������ͨ����ô������ͨͼ
    //��˲���������ȱ�������ʱ�������ʹ��Ķ�����Ϊ1����ѭ���������ж��������ǣ���˵����ͼ����ͨ��
    int *visited = (int *)malloc(sizeof(int) * g.N);//�����ж��Ƿ���ʹ�ĳ�����������
    int i;
    for (i = 0; i < g.N; i++)//�Ƚ����еĶ��㶼��ʼ��
    {
        visited[i] = 0;
    }
    DFS(g,0,visited);//������ȱ���
    for (i = 0; i < g.N; i++)
    {
        if (visited[i] == 0)//�����ĳ������û�б����ʹ� ��ô��ͼ����ͨ
        {
            free(visited);//�ͷ�visited�Ĵ洢�ռ�
            return 0;
        }
    }
    free(visited);
    return 1;
}
/**
 * ������ȱ���
 * @param g ͼ
 * @param v �ڵ���
 * @param visited ���ʱ������
 */
void DFS(Graph g, int v, int visited[])
{
    visited[v] = 1;//�����ʹ��Ķ����־Ϊ1
    for (int i = 0; i < g.N; i++)//forѭ������ѭ���ж����еĶ���
    {
        if (g.matrix[v][i] > 0&&g.matrix[v][i] < max_dis&&visited[i] == 0)//������һ������֮���б� ���Ҹö���û�б����ʹ�
            DFS(g,i,visited);//����������ȱ��� ֱ�����еĶ��㶼����ǹ�
    }
}

/**
 * ����ÿ����Ķ�
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 */
void nodeDegree(Graph g, int *node_degree)
{
    //TODO
    int count;//���ڼ�¼����Ķ���
    for(int i=0; i<g.N; i++)//���ѭ������ѭ��ÿһ������
    {
        count=0;
        for(int j=0; j<g.N; j++)//�ڲ�ѭ�������ж�ĳ������Ķ�
        {
            if(g.matrix[i][j]!=0&&g.matrix[i][j]!=max_dis)//���ݴ洢�����������i������ĳ������j�ľ������
            {
                count++;//����Ķ���+1
            }
        }
        node_degree[i]=count;//��node_degree����洢ÿ������Ķ�
    }
}

/**
 * ����ͼ�ľ���ϵ��
 * @param g ͼ
 * @return ���ؾ���ϵ��
 */
double clusteringCoefficient(Graph g)
{
    //TODO
    int fact;//ʵ���붥��i������������֮��ı���
    int theory;//�����붥��i������������֮��ı���
    int i,j,k;
    double clucoe=0;//ÿ������ľ���ϵ��
    int degree[g.N];//���ڴ��涥�����������
    nodeDegree(g,degree);//����nodeDegree��������ÿ������Ķ����洢������degree��
    for(i=0; i<g.N; i++) //for���ѭ������ѭ������ÿһ�����㣬�����ÿһ������ľ���ϵ��
    {
        theory=0;//��ʼ������ֵ
        fact=0;//��ʼ��ʵ��ֵ
        for(j=0; j<g.N; j++)//�ڶ���ѭ������ѭ���������ඥ��
        {
            if(g.matrix[i][j]<max_dis&&g.matrix[i][j]!=0)//�ж����ඥ���Ƿ���ö����������������������һ��ѭ��
            {
                //ѭ���Ƚϵ�ǰ�붥��i�����Ķ���j�Ƿ��������붥��i�����Ķ���k����
                for(k=j+1; k<g.N; k++)
                {
                    //�ж�k��j��������k�붥��iҲ����
                    if(g.matrix[j][k]<max_dis&&g.matrix[j][k]!=0&&g.matrix[k][i]<max_dis&&g.matrix[k][i]!=0)
                    {
                        fact++;//�������Ļ�����ʵ��ֵ+1
                    }
                }
            }
        }
        theory=degree[i]*(degree[i]-1)/2;//����ֵ����
        if(theory)//�������ֵ��Ϊ0
        {
            clucoe+=1.0*fact/theory;//��ǰ����i�ľ���ϵ��
        }
    }
    return clucoe/g.N;//���ظ�ͼ�ľ���ϵ��
}

/**
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    int dis[g.N];//dis���鱣��Դ���㵽���������̾���
    int mark[g.N];//��Ϊ���
    int prior[g.N];//���ĳ�����ǰ������
    for(int i=0; i<g.N; i++)
    {
        mark[i]=0;
        dis[i]=max_dis;//��ʼ��·������Ϊ�����
        prior[i]=0;//��ʼ��ǰ������Ϊ0
    }
    dis[end]=0;//���Դ��

    for(int i=0; i<g.N; i++)//��ѭ����ÿ�����v0��ĳ����������·������v������뵽S����
    {
        int min=max_dis;
        int v;
        for(int j=0; j<g.N; j++)
        {
            if(mark[j]==0&&min>dis[j])//j������G-S�У���j������v0���
            {
                min=dis[j];
                v=j;
            }
        }
        mark[v]=1;//��v0���������v���뵽������ȥ

        for(int u=0; u<g.N; u++)//���µ�ǰ���·��������
        {
            if(u==v)
                continue;
            if(g.matrix[v][u]<0)//����ȨֵΪ�����ģ�����0
            {
                return 0;
            }
            //����v����ֱ�ӵ�����������ͨ���õ㵽��u�����·���Ƿ��Դ����ֱ�ӵ���u�����
            if(mark[u]==0&&dis[u]>dis[v]+g.matrix[v][u])
            {
                dis[u]=dis[v]+g.matrix[v][u];//�������·������
                prior[u]=v;//��u�����ǰ����������Ϊv
            }
        }
    }
    int cur = start;
    int count=0;
    while(cur != end)//����ǰ���������������start��end�����·�������path������ȥ
    {
        path[count++]=cur;
        cur=prior[cur];
    }
    path[count++]=end;
    return dis[start];
}

/**
* �Ƚ�������֮��Ĵ�С����������ֵ�ϴ���Ǹ���
* @param x y
* @return int
*/
 int max(int x,int y)//����������֮��ϴ����һ��
 {
     if(x>y)
     {
         return x;
     }
     else return y;
 }

 /**
* �Ƚ�������֮��Ĵ�С����������ֵ��С���Ǹ���
* @param x y
* @return int
*/
int min(int x,int y)//����������֮���С����һ��
 {
     if(x<y)
     {
          return x;
     }
     else return y;
 }
 /**
 * ����ͼ��ֱ���Ͱ뾶����ʾ: Floyd�㷨
 * @param g ͼ
 * @param diameter ָ��ֱ��������ָ��
 * @param radius ָ��뾶������ָ��
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    //TODO

    int i,j,k;
    int D[g.N][g.N];//����
    //floyd�㷨��ϸ���̣�����forѭ���Ծ���D��ʼ��
    for(i=0; i<g.N; i++)//���ѭ������ÿ������
    {
        for(j=0; j<g.N; j++)//�ڲ�ѭ��
        {
            D[i][j]=g.matrix[i][j];
        }
    }
    //kΪ�м�ĳ������
    for(k=0; k<g.N; k++)
    {
        for(i=0; i<g.N; i++)
        {
            for(j=0; j<g.N; j++)
            {
                if(D[i][j] > (D[i][k] + D[k][j]))
                {
                    D[i][j] = D[i][k] + D[k][j];//������С·��
                }
            }
        }
    }

    int eccen;//���������ʣ�������һ�����㵽���������������
    *diameter=0;//ֱ�������ж��������������Ǹ�
    *radius=max_dis;//�뾶�����ж�����������С���Ǹ�
    for(i=0;i<g.N;i++)
    {
        eccen=0;
        for(j=0;j<g.N;j++)
        {
            eccen=max(eccen,D[i][j]);//��������������
        }
       *diameter=max(eccen,*diameter);//���ͼ��ֱ��
       *radius=min(eccen,*radius);//���ͼ�İ뾶
    }
}


int main()
{
    int node_num;
    int edge_num;
    int ca = 1;
    if (freopen("stu.in", "r", stdin) == NULL)
    {
        printf("There is an error in reading file stu.in");
    }
    while (scanf("%d %d\n", &node_num, &edge_num) != EOF)
    {
        printf("\ncase %d:\n", ca++);
        int start_idx, end_idx, weight;
        Graph g = createGraph(node_num);
        for(int i = 0; i < node_num; i++)
        {
            sprintf(g.vertex[i], "%d", i);
        }
        for (int i = 0; i < edge_num; i++)
        {
            scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        printf("connected: %d\n", isConnected(g));
        int *degree = (int *)malloc(sizeof(int) * g.N);
        nodeDegree(g, degree);
        printf("degree distribution:\n");
        for(int i=0; i<g.N; i++)
        {
            printf("node%s:%d,", g.vertex[i], degree[i]);
        }
        printf("\n");
        free(degree);

        double c = clusteringCoefficient(g);
        printf("clustering coefficient:%f\n", c);

        if(isConnected(g))
        {
            int *short_path = (int *)malloc(sizeof(int) * g.N);
            int dis = dijkstra(g, 1, 3, short_path);
            printf("the shortest path between 1 and 3: %d\n", dis);
            printPath(dis, short_path, g);
            free(short_path);

            int diameter, radius;
            computeEcc(g, &diameter, &radius);
            printf("diameter:%d\n", diameter);
            printf("radius:%d\n", radius);
        }
    }

    return 0;
}
