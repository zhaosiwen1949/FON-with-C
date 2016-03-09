#include "Tsp.h"
#include "Channel.h"
#include "Ant.h"
#include "Common.h"
using namespace std;



Tsp::Tsp(void)
{
}

Tsp::~Tsp(void)
{
}

//程序首部初始化bigchannel信息  他的初始化在client.init 中调用tsp.c_init实现
void Tsp::C_Init()
{
}

//初始化路径和信息素
void Tsp::Init()
{
	//--------
	int i,j;
	BestAnt.m_dbPathLength=DB_MAX; 

	//初始化环境信息素
	for ( i=0;i<N_CITY_COUNT;i++)
	{
		for ( j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=1;
		}
	}
}


//返回值 有阻塞 返回1，无阻塞，返回0且获取最优蚂蚁的解
int Tsp::Search()
{
	Init();
	int  block_flag;//返回0，1
	int i,j;
	int countflag=0;
	int kill;//接收死亡蚂蚁数，如果kill=ant数，则进行下一个迭代，如果所有迭代完成，每次都蚂蚁被杀死，则返回block-flag值为1

	//1开始蚁群算法
	for (i=0;i<N_IT_COUNT;i++)
	{
	//	printf("\n开始第  %d 次循环\n",i);

		kill=0;
	
		//1.1每只蚂蚁搜索一遍
		for (j=0;j<N_ANT_COUNT;j++)
		{
			//1.1.2承接业务要求
			m_nAnt[j].Wide=Wide;
			m_nAnt[j].A_T=A_T; 
			m_nAnt[j].L_T=L_T;
            m_nAnt[j].m_nCurCityNo=tm_nCurCityNo;
            m_nAnt[j].m_nDesCityNo=tm_nDesCityNo;
			//1.1.3计算蚂蚁自杀数目
			kill+=m_nAnt[j].Search(); 
		}//所有蚂蚁搜完
		//1.2 如果所有蚂蚁都被杀死，则跳出整个程序
		if(kill==N_ANT_COUNT)
		{    
			//block_flag=1;
		//	printf("\n[%d]god damn it!\n",i);
		    //break;
			countflag++;
		}
		else 
		{
			block_flag=0;
		//	printf("\nblock=0--------------and we can cout the best path");


		}
		//1.3 保存最佳结果，留下唯一最优路径
		for (j=0;j<N_ANT_COUNT;j++) 
		{

			if (m_nAnt[j].m_dbPathLength < BestAnt.m_dbPathLength)
			{
				BestAnt=m_nAnt[j];
			}
		}

		//更新环境信息素
		if(BestAnt.m_dbPathLength!=DB_MAX)
		{
			Update();

		}
		//输出结果
		/*
		printf("\n start_city=%d,end_city=%d\n", tm_nCurCityNo,tm_nDesCityNo);
		for(j=0;j<N_CITY_COUNT;j++)
		{	
			printf("%d-->",BestAnt.m_nPath[j]);
		}
		*/

	}//迭代完成


	if(countflag==N_IT_COUNT)
	{
		block_flag=1;
		printf("\n block_flag=1");
	}
	else
	{	
		printf("\n block_flag=0");
		C_arrange();
//	    printf("\n更新");
	}
	return block_flag ;//这里的应该返回break处的1值

}

void Tsp::Update()
{
	int i,j,z;
	//临时保存信息素
	double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
	memset(dbTempAry,0,sizeof(dbTempAry)); //先全部设置为0

	//计算新增加的信息素,保存到临时数组里
	int m=0;
	int n=0;
	for (i=0;i<N_ANT_COUNT;i++) //计算每只蚂蚁留下的信息素
	{int x=0;
			for(z=0;m_nAnt[i].m_nPath[z]!=-4&&z<N_CITY_COUNT;z++)
			 x++;
			for (j=1;j<x;j++)//m_nAnt[i].m_nPat记录每只蚂蚁走到终点的路径
			{ if (m_nAnt[i].kAnt!=1)
				{
					m=m_nAnt[i].m_nPath[j];
					n=m_nAnt[i].m_nPath[j-1];
					dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_nAnt[i].m_dbPathLength;//信息素总量100
					dbTempAry[m][n]=dbTempAry[n][m];
				}
			}

			//最后城市和开始城市之间的信息素
		//	n=m_nAnt[i].m_nPath[0];
		//	dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_nAnt[i].m_dbPathLength;
		//	dbTempAry[m][n]=dbTempAry[n][m];

	}

	//更新环境信息素
	for (i=0;i<N_CITY_COUNT;i++) 
	{
		for (j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j];  
		}
	}


}
//一次蚁群算法后将<最优>蚂蚁走过路径上的信道占用离开时间更新
void Tsp::C_arrange()
{
	int m,n,z;
	int j,k;
	int x=0;
			for(z=0;BestAnt.m_nPath[z]!=-4&&z<N_CITY_COUNT;z++)
			 x++;
		for (j=0;j<x-1;j++)
		{
			n=BestAnt.m_nPath[j];
			m=BestAnt.m_nPath[j+1];
			k=BestAnt.m_nLink[j+1];
			if(Wide==1)
			{
				Public_channel[n][m].L_T[k]=BestAnt.L_T;
				Public_channel[m][n]=Public_channel[n][m];
			}
			if(Wide==2)
			{	
				Public_channel[n][m].L_T[k]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+1]=BestAnt.L_T;
				Public_channel[m][n]=Public_channel[n][m];			
			}
		
            if(Wide==3)
			{
				Public_channel[n][m].L_T[k]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+1]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+2]=BestAnt.L_T;
				Public_channel[m][n]=Public_channel[n][m];			
			}
			if(Wide==4)
			{
				Public_channel[n][m].L_T[k]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+1]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+2]=BestAnt.L_T;
				Public_channel[n][m].L_T[k+3]=BestAnt.L_T;
				Public_channel[m][n]=Public_channel[n][m];			
			
			}

		}

}
