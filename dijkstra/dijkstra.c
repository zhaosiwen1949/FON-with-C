/*
readme:
first,you need to input the node number, the cost matrix and the source node;
then the program will compute the best path.
finally,the program will output the lowest distance to the destination node, the pre-node and show the best path.
首先你需要输入 节点个数， 最高费用和源节点
然后输出到达目的节点的最短路径，头一个节点和最优路径
*/


#include <stdio.h>
#include <stdlib.h>
//Dijkstra算法实现函数****************************************************************************
//直到s[]中所有节点都为1之后循环就结束了
void Dijkstra(int n,int v,int dist[],int prev[],int cost[14][14])//v为源节点 
{
	int i;
	int j;
    int maxint = 65535;//定义一个最大的数值，作为不相连的两个节点的代价权值 相当于无穷
	int *s ;//定义具有最短路径的节点子集s
	s = (int *)malloc(sizeof(int) * n);// s其实是一个n大小的数组，节点被用，则为1，反之为0
	//初始化最小路径代价和前一跳节点值------------------------------------------//
	for (i = 0; i < n; i++)
	{
		dist[i] = cost[v][i];//Wi=d_vj 获取源节点到各个节点的权值距离
		s[i] = 0; //具有最短路径的{GP} 子集现在为空 从1~n 节点未被选 取0
		if (dist[i] == maxint)  //如果i到Vs 的距离为无穷，则不相邻 设定的他的前一节点为0空
		{
			prev[i] = 0;
		}
		else      //如果i到Vs的距离不为无穷，即相邻，则他们将是先与VS点进行最短路径比较的点，设定他们的前一节点为V点
		{
			prev[i] = v;
		}
	}
	dist[v] = 0;//设定V到V的距离为0
	s[v] = 1;//最短路由的子集GP中有一个元素了，就是刚开始的源节点V
	printf("s[v]=1\n");//test
  //-------------------------------------------------------------------------------//

	for (i = 0; i < n; i++)
	{
		int temp = maxint;
		int u = v;
		//加入具有最小代价的邻居节点到s子集
		printf("第%d轮-----------\n",i);//test

		for (j = 0; j < n; j++)
		{
			if ((!s[j]) && (dist[j] < temp)) //如果j不点在{GP}内，且V点到j点的距离不为无穷
			{
					printf("%d不在GP集合中\n",j);//test

				u = j;    //则另u==j，并将temp的值替换为vs到j 的距离，当所有与VS相邻的j点经过距离比较留下最短的给u
				temp = dist[j];
			}
		}
		s[u] = 1;//经过上面的循环选出了一个最短路径的点，并将其写入子集GP
		printf("s[%d]=1\n",u);//test

		//计算加入新的节点后，更新路径使得其产生代价最短**********************
		for (j = 0; j < n; j++)//从上一个选出的U点开始寻找下一个最短权值的点
		{
			if ((!s[j]) && (cost[u][j] < maxint))
			{
				int newdist = dist[u] + cost[u][j];//u到Vs的距离+u到j的权值
				if (newdist < dist[j])//如果上式距离小于Vs到j的距离，则用最短路的权值替换原有VS到j 的距离
				{
					dist[j] = newdist;
					prev[j] = u;// 并设置j点的前一个点为u点
					printf("%d-->%d\n",u,j);//test

				}
			}
		}
	}
}
//展示最佳路径函数************************************************************************
void ShowPath(int n,int v,int u,int *dist,int *prev)
{


	int j = 0;
	int w = u;
	int count = 0;
	int *way ;
	way=(int *)malloc(sizeof(int)*(n+1));
	//回溯路径
	while (w != v)
	{
		count++;
		way[count] = prev[w];
		w = prev[w];
	}
	//输出路径
	printf("the best path is:\n");
	for (j = count; j >= 1; j--)
	{
		printf("%d --> ",way[j]);
	}
	printf("%d\n",u);


}
//主函数，主要做输入输出工作
int main()
{
//	int i;
	int v;//源节点
	int d;//目的节点
	int n=14;

//	int **cost;//代价矩阵
	int *dist;//最短路径代价
	int *prev;//前一跳节点空间
//	cost=(int **)malloc(sizeof(int)*(n+1));

	int	cost[14][14]={
		0,1,1,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
		1,0,1,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,65535,
		1,1,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
		65535,65535,65535,0,1,65535,65535,65535,1,65535,65535,65535,65535,65535,
		65535,65535,65535,1,0,1,1,65535,65535,65535,65535,65535,65535,65535,
		65535,65535,65535,65535,1,0,65535,65535,65535,65535,1,65535,1,65535,
		65535,65535,65535,65535,1,65535,0,1,65535,65535,65535,65535,65535,65535,
		65535,1,65535,65535,65535,65535,1,0,65535,65535,65535,65535,65535,65535,
		65535,65535,65535,1,65535,65535,65535,65535,0,65535,65535,1,65535,1,
		65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,1,65535,1,
		65535,65535,65535,65535,65535,1,65535,65535,65535,65535,0,65535,65535,65535,
		65535,65535,65535,65535,65535,65535,65535,65535,1,1,65535,0,1,65535,
		65535,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,1,0,1,
		65535,65535,65535,65535,65535,65535,65535,65535,1,1,65535,65535,1,0
		
	};

//	printf("please input the node number: ");
//	scanf("%d",&n);
//	printf("please input the cost status:\n");
/*
	cost=(int **)malloc(sizeof(int)*(n+1));


	for (i = 1; i <= n; i++)
	{
		cost[i]=(int *)malloc(sizeof(int)*(n+1));
	}
	//输入代价矩阵
	for (j = 1; j <= n; j++)
	{
		for (t = 1; t <= n; t++)
		{
			scanf("%d",&cost[j][t]);
		}
	}
	*/

	dist = (int *)malloc(sizeof(int)*n);
	prev = (int *)malloc(sizeof(int)*n);


	printf("please input the source node(1~14): ");
	scanf("%d",&v);
	printf("please input the dest node(1~14) : ");
	scanf("%d",&d);
	//调用dijkstra算法  
	Dijkstra(n, v,dist, prev, cost);
	printf("*****************************\n");
	printf("have confirm the best path\n");
	printf("*****************************\n");
	
			printf("the distance cost  from node %d to node %d is %d\n",v,d,dist[d]);
			ShowPath(n,v,d, dist, prev);
/*
	for(i = 1; i <= n ; i++)
	{
		if(i!=v)
		{
			printf("the distance cost  from node %d to node %d is %d\n",v,i,dist[i]);
			printf("the pre-node of node %d is node %d \n",i,prev[i]);
			ShowPath(n,v,i, dist, prev);
		}
	}
*/
	
	system("pause");
	return 0;
}

