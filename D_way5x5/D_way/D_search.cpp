
#include "D_search.h"



D_search::D_search(void)
{
}

D_search::~D_search(void)
{
}
void D_search::Init()
{
	for(int i=0;i<N_CITY;i++)
	way_link[i]=21;//无所谓，选择一个取不到的值就可以了

}


void D_search::Search_way(int n,int start,int cost[N_CITY][N_CITY])
{
	int i,j;
	int s[N_CITY];//定义具有最短路径的节点子集s
	//初始化最小路径代价和前一跳节点值------------------------------------------//
	for (i = 0; i < n; i++)
	{
		dist[i] = cost[start][i];//Wi=d_vj 获取源节点到各个节点的权值距离
		s[i] = 0; //具有最短路径的{GP} 子集现在为空
		if (dist[i] == maxint)  //如果i到Vs 的距离为无穷，则不相邻 设定的他的前一节点为0空
		{
			prev[i] = 0;
		}
		else      //如果i到Vs的距离不为无穷，即相邻，则他们将是先与VS点进行最短路径比较的点，设定他们的前一节点为V点
		{
			prev[i] = start;
		}
	}
	dist[start] = 0;//设定start到start的距离为0
	s[start] = 1;//最短路由的子集GP中有一个元素了，就是刚开始的源节点start
  //-------------------------------------------------------------------------------//

	for (i = 0; i < n; i++)
	{
		int temp = maxint;
		int u = start;
		//加入具有最小代价的邻居节点到s子集
		for (j = 0; j < n; j++)
		{
			if ((!s[j]) && (dist[j] < temp)) //如果j点不在{GP}内，且start点到j点的距离不为无穷
			{
				u = j;    //则另u==j，并将temp的值替换为vs到j 的距离，当所有与VS相邻的j点经过距离比较留下最短的给u
				temp = dist[j];
			}
		}
		s[u] = 1;//经过上面的循环选出了一个最短路径的点，并将其写入子集GP
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
				}
			}
		}
	}
}

//包括检查信道空闲，记录所选路径，记录block
int D_search::Show_way(int n,int start,int dest)
{

	int j = 0;
	int w = dest;
	int count = 0;
	int block=0;
	int check_first;
	int check_way;

	//回溯路径
	way[0]=dest;
	while (w != start)
	{
		count++;
		way[count] = prev[w];
		w = prev[w];
	}

	//--------------------检查用
	//printf("we select the best path ======\n");

	//	for (j = count; j >= 1; j--)
	//	{
			//printf("%d - ->",way[j]);
	//	}

	//	printf("%d\n",dest);
    //
	//-------------------------

	//A 情况--考虑了波长连续也一致性的阻塞率
	check_first=Check_way(count);
	if(check_first==-1)
	{
		block=1;
	//	printf("the first hit is stuck \n");
		return block;
	}
	else
	{

		for (j = count-1; j >= 1; j--)
		{
			check_way=Check_way(j);
			if(check_way!=check_first)
			{
				//printf("波长不一致 block ++ \n");
				block=1;
				return block;			
			}
			else
			{

				printf("波长一致\n");
			
			}

		}
	C_arrange(count);


	}

//---------------------------------------
//B 情况--不考虑波长一致性的情况
/*
	for (j = count; j >= 1; j--)
		{
			check_way=Check_way(j);
			if(check_way==-1)
			{
				//printf("we didn't find free channel between the %d and %d channnel! block ++ \n",j,j-1);
				block=1;
				break;
			}
		}
	if(block!=-1)
		C_arrange(count);
	*/

	return block;


}
//用于检查信道是否可用~
// return 值为-1，表示寻信道失败， return 值为select，表示信道有，且已经标记好了j->j-1路径选到的信道首标号
int D_search::Check_way(int num)
{
	int select;
	int fail_flag;
	int m=way[num];
	int n=way[num-1];
	//获取可选信道的首个标号
	select=Public_channel[m][n].Check(A_T,L_T, Wide);
		if(select==-1)
		{
			fail_flag=-1;//没有可用信道
		}
		else 
		{
			way_link[num]=select;
			fail_flag=select;		
		}
	
	return fail_flag;

}
//更新信道函数
void D_search::C_arrange(int count)
{
	int m,n;
	int j,k;
//	int top;
		for (j = count; j >= 1; j--)
		{
			n=way[j];
			m=way[j-1];
			k=way_link[j];
	//		printf("%d ===(%d)==>",n,k);
			if(Wide==1)
			{				
				//printf("\n更新长度为1的信道占用");
				//printf("\n--------------------------\n");

				Public_channel[n][m].L_T[k]=L_T;
				Public_channel[m][n]=Public_channel[n][m];
			}
			if(Wide==4)
			{
				for(int w=0;w<3;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				}
				Public_channel[m][n]=Public_channel[n][m];	
			}
			if(Wide==10)
			{
				for(int w=0;w<9;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				}
				Public_channel[m][n]=Public_channel[n][m];

			}

			if(Wide==20)
			{
				for(int w=0;w<19;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				//	printf("\n 更新长度为20的信道占用");
				}
				Public_channel[m][n]=Public_channel[n][m];			
				//printf("\n--------------------------\n");

			}
		}

}
























