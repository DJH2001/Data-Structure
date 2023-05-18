#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000
typedef char vextype[20];
typedef struct
{
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
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
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
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
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g)
{
    //TODO
    //任意两个顶点可以直接或者通过其他顶点走通，那么就是连通图
    //因此采用深度优先遍历可以时将被访问过的顶点标记为1，若循环下来所有顶点均被标记，则说明该图是连通的
    int *visited = (int *)malloc(sizeof(int) * g.N);//用于判断是否访问过某个顶点的数组
    int i;
    for (i = 0; i < g.N; i++)//先将所有的顶点都初始化
    {
        visited[i] = 0;
    }
    DFS(g,0,visited);//深度优先遍历
    for (i = 0; i < g.N; i++)
    {
        if (visited[i] == 0)//如果有某个顶点没有被访问过 那么该图不连通
        {
            free(visited);//释放visited的存储空间
            return 0;
        }
    }
    free(visited);
    return 1;
}
/**
 * 深度优先遍历
 * @param g 图
 * @param v 节点编号
 * @param visited 访问标记数组
 */
void DFS(Graph g, int v, int visited[])
{
    visited[v] = 1;//将访问过的顶点标志为1
    for (int i = 0; i < g.N; i++)//for循环用于循环判断所有的顶点
    {
        if (g.matrix[v][i] > 0&&g.matrix[v][i] < max_dis&&visited[i] == 0)//即到下一个顶点之间有边 并且该顶点没有被访问过
            DFS(g,i,visited);//继续深度优先遍历 直至所有的顶点都被标记过
    }
}

/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree)
{
    //TODO
    int count;//用于记录顶点的度数
    for(int i=0; i<g.N; i++)//外层循环用于循环每一个顶点
    {
        count=0;
        for(int j=0; j<g.N; j++)//内层循环用于判断某个顶点的度
        {
            if(g.matrix[i][j]!=0&&g.matrix[i][j]!=max_dis)//根据存储矩阵如果顶点i到其他某个顶点j的距离存在
            {
                count++;//顶点的度数+1
            }
        }
        node_degree[i]=count;//用node_degree数组存储每个顶点的度
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g)
{
    //TODO
    int fact;//实际与顶点i相连其他顶点之间的边数
    int theory;//理论与顶点i相连其他顶点之间的边数
    int i,j,k;
    double clucoe=0;//每个顶点的聚类系数
    int degree[g.N];//用于储存顶点度数的数组
    nodeDegree(g,degree);//调用nodeDegree函数，将每个顶点的度数存储到数组degree中
    for(i=0; i<g.N; i++) //for外层循环用于循环遍历每一个顶点，计算出每一个顶点的聚类系数
    {
        theory=0;//初始化理论值
        fact=0;//初始化实际值
        for(j=0; j<g.N; j++)//第二层循环用于循环遍历其余顶点
        {
            if(g.matrix[i][j]<max_dis&&g.matrix[i][j]!=0)//判断其余顶点是否与该顶点相连，若相连则进如下一个循环
            {
                //循环比较当前与顶点i相连的顶点j是否与其他与顶点i相连的顶点k相连
                for(k=j+1; k<g.N; k++)
                {
                    //判断k与j相连并且k与顶点i也相连
                    if(g.matrix[j][k]<max_dis&&g.matrix[j][k]!=0&&g.matrix[k][i]<max_dis&&g.matrix[k][i]!=0)
                    {
                        fact++;//若相连的话，则实际值+1
                    }
                }
            }
        }
        theory=degree[i]*(degree[i]-1)/2;//理论值计算
        if(theory)//如果理论值不为0
        {
            clucoe+=1.0*fact/theory;//当前顶点i的聚类系数
        }
    }
    return clucoe/g.N;//返回该图的聚类系数
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    int dis[g.N];//dis数组保存源顶点到各顶点的最短距离
    int mark[g.N];//作为标记
    int prior[g.N];//存放某顶点的前驱顶点
    for(int i=0; i<g.N; i++)
    {
        mark[i]=0;
        dis[i]=max_dis;//初始化路径长度为无穷大
        prior[i]=0;//初始化前驱顶点为0
    }
    dis[end]=0;//标记源点

    for(int i=0; i<g.N; i++)//主循环，每次求出v0到某个顶点的最短路径，将v顶点插入到S集中
    {
        int min=max_dis;
        int v;
        for(int j=0; j<g.N; j++)
        {
            if(mark[j]==0&&min>dis[j])//j顶点在G-S中，且j顶点离v0最近
            {
                min=dis[j];
                v=j;
            }
        }
        mark[v]=1;//离v0顶点最近的v加入到集合中去

        for(int u=0; u<g.N; u++)//更新当前最短路径及距离
        {
            if(u==v)
                continue;
            if(g.matrix[v][u]<0)//若有权值为负数的，返回0
            {
                return 0;
            }
            //顶点v可以直接到达其他顶点通过该点到达u顶点的路径是否比源顶点直接到达u顶点短
            if(mark[u]==0&&dis[u]>dis[v]+g.matrix[v][u])
            {
                dis[u]=dis[v]+g.matrix[v][u];//更新最短路径距离
                prior[u]=v;//将u顶点的前驱顶点设置为v
            }
        }
    }
    int cur = start;
    int count=0;
    while(cur != end)//利用前驱顶点数组求出从start到end的最短路径，存放path数组中去
    {
        path[count++]=cur;
        cur=prior[cur];
    }
    path[count++]=end;
    return dis[start];
}

/**
* 比较两个数之间的大小，并返回数值较大的那个数
* @param x y
* @return int
*/
 int max(int x,int y)//返回两个数之间较大的那一个
 {
     if(x>y)
     {
         return x;
     }
     else return y;
 }

 /**
* 比较两个数之间的大小，并返回数值较小的那个数
* @param x y
* @return int
*/
int min(int x,int y)//返回两个数之间较小的那一个
 {
     if(x<y)
     {
          return x;
     }
     else return y;
 }
 /**
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    //TODO

    int i,j,k;
    int D[g.N][g.N];//矩阵
    //floyd算法详细过程，利用for循环对矩阵D初始化
    for(i=0; i<g.N; i++)//外层循环遍历每个顶点
    {
        for(j=0; j<g.N; j++)//内层循环
        {
            D[i][j]=g.matrix[i][j];
        }
    }
    //k为中间某个顶点
    for(k=0; k<g.N; k++)
    {
        for(i=0; i<g.N; i++)
        {
            for(j=0; j<g.N; j++)
            {
                if(D[i][j] > (D[i][k] + D[k][j]))
                {
                    D[i][j] = D[i][k] + D[k][j];//更新最小路径
                }
            }
        }
    }

    int eccen;//顶点离心率：从任意一个顶点到其他顶点的最大距离
    *diameter=0;//直径：所有顶点离心率最大的那个
    *radius=max_dis;//半径：所有顶点离心率最小的那个
    for(i=0;i<g.N;i++)
    {
        eccen=0;
        for(j=0;j<g.N;j++)
        {
            eccen=max(eccen,D[i][j]);//求出顶点的离心率
        }
       *diameter=max(eccen,*diameter);//求出图的直径
       *radius=min(eccen,*radius);//求出图的半径
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
