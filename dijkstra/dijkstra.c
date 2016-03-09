/*
readme:
first,you need to input the node number, the cost matrix and the source node;
then the program will compute the best path.
finally,the program will output the lowest distance to the destination node, the pre-node and show the best path.
��������Ҫ���� �ڵ������ ��߷��ú�Դ�ڵ�
Ȼ���������Ŀ�Ľڵ�����·����ͷһ���ڵ������·��
*/


#include <stdio.h>
#include <stdlib.h>
//Dijkstra�㷨ʵ�ֺ���****************************************************************************
//ֱ��s[]�����нڵ㶼Ϊ1֮��ѭ���ͽ�����
void Dijkstra(int n,int v,int dist[],int prev[],int cost[14][14])//vΪԴ�ڵ� 
{
	int i;
	int j;
    int maxint = 65535;//����һ��������ֵ����Ϊ�������������ڵ�Ĵ���Ȩֵ �൱������
	int *s ;//����������·���Ľڵ��Ӽ�s
	s = (int *)malloc(sizeof(int) * n);// s��ʵ��һ��n��С�����飬�ڵ㱻�ã���Ϊ1����֮Ϊ0
	//��ʼ����С·�����ۺ�ǰһ���ڵ�ֵ------------------------------------------//
	for (i = 0; i < n; i++)
	{
		dist[i] = cost[v][i];//Wi=d_vj ��ȡԴ�ڵ㵽�����ڵ��Ȩֵ����
		s[i] = 0; //�������·����{GP} �Ӽ�����Ϊ�� ��1~n �ڵ�δ��ѡ ȡ0
		if (dist[i] == maxint)  //���i��Vs �ľ���Ϊ��������� �趨������ǰһ�ڵ�Ϊ0��
		{
			prev[i] = 0;
		}
		else      //���i��Vs�ľ��벻Ϊ��������ڣ������ǽ�������VS��������·���Ƚϵĵ㣬�趨���ǵ�ǰһ�ڵ�ΪV��
		{
			prev[i] = v;
		}
	}
	dist[v] = 0;//�趨V��V�ľ���Ϊ0
	s[v] = 1;//���·�ɵ��Ӽ�GP����һ��Ԫ���ˣ����Ǹտ�ʼ��Դ�ڵ�V
	printf("s[v]=1\n");//test
  //-------------------------------------------------------------------------------//

	for (i = 0; i < n; i++)
	{
		int temp = maxint;
		int u = v;
		//���������С���۵��ھӽڵ㵽s�Ӽ�
		printf("��%d��-----------\n",i);//test

		for (j = 0; j < n; j++)
		{
			if ((!s[j]) && (dist[j] < temp)) //���j������{GP}�ڣ���V�㵽j��ľ��벻Ϊ����
			{
					printf("%d����GP������\n",j);//test

				u = j;    //����u==j������temp��ֵ�滻Ϊvs��j �ľ��룬��������VS���ڵ�j�㾭������Ƚ�������̵ĸ�u
				temp = dist[j];
			}
		}
		s[u] = 1;//���������ѭ��ѡ����һ�����·���ĵ㣬������д���Ӽ�GP
		printf("s[%d]=1\n",u);//test

		//��������µĽڵ�󣬸���·��ʹ��������������**********************
		for (j = 0; j < n; j++)//����һ��ѡ����U�㿪ʼѰ����һ�����Ȩֵ�ĵ�
		{
			if ((!s[j]) && (cost[u][j] < maxint))
			{
				int newdist = dist[u] + cost[u][j];//u��Vs�ľ���+u��j��Ȩֵ
				if (newdist < dist[j])//�����ʽ����С��Vs��j�ľ��룬�������·��Ȩֵ�滻ԭ��VS��j �ľ���
				{
					dist[j] = newdist;
					prev[j] = u;// ������j���ǰһ����Ϊu��
					printf("%d-->%d\n",u,j);//test

				}
			}
		}
	}
}
//չʾ���·������************************************************************************
void ShowPath(int n,int v,int u,int *dist,int *prev)
{


	int j = 0;
	int w = u;
	int count = 0;
	int *way ;
	way=(int *)malloc(sizeof(int)*(n+1));
	//����·��
	while (w != v)
	{
		count++;
		way[count] = prev[w];
		w = prev[w];
	}
	//���·��
	printf("the best path is:\n");
	for (j = count; j >= 1; j--)
	{
		printf("%d --> ",way[j]);
	}
	printf("%d\n",u);


}
//����������Ҫ�������������
int main()
{
//	int i;
	int v;//Դ�ڵ�
	int d;//Ŀ�Ľڵ�
	int n=14;

//	int **cost;//���۾���
	int *dist;//���·������
	int *prev;//ǰһ���ڵ�ռ�
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
	//������۾���
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
	//����dijkstra�㷨  
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

