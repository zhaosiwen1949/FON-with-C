#include "Ant.h"


Ant::Ant(void)
{
}

Ant::~Ant(void)
{
}
//初始化
void Ant::Init()
{
	int i;
	for (i=0;i<N_CITY_COUNT;i++)
	{
		m_nAllowedCity[i]=1; //设置全部城市为没有去过
		m_nPath[i]=-4; //蚂蚁走的路径全部设置为0
		m_nLink[i]=0;//蚂蚁选择的信道均为0信道
	}

	//蚂蚁走过的路径长度设置为0
	m_dbPathLength=0.0; 

	
	//m_nCurCityNo=rnd(0,N_CITY_COUNT);//随机选择一个出发城市
    //m_nDesCityNo=rnd(0,N_CITY_COUNT);//随机选择一个终点城市
	//设置出发城市和初始信道
	m_nPath[0]=m_nCurCityNo;
	m_nLink[0]=0;
	//标识出发城市为已经去过了
	m_nAllowedCity[m_nCurCityNo]=0; 

	//已经去过的城市数量设置为1
	m_nMovedCityCount=1; 

} 

//选择下一个城市：nSelectedCity
int Ant::ChooseNextCity()
{
	int i;
	int nSelectedCity=-1;//暂时表示未选中下一个城市
	//_______________________________________________________________________

	//计算当前城市和没去过的城市之间的信息素总和
	double dbTotal=0.0;	
	double prob[N_CITY_COUNT]; // 保存城市被选中的概率
    double accumulate=0.0;
	for (i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i]==1&&g_Distance[m_nCurCityNo][i]==1) //城市没去过且相邻
		{
			accumulate=accumulate+pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA); //cur城市到i城市的概率
		//累加信息素，得到总和  只针对当前这个城市做了一次信息素的累加
		}
	}
for (i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i]==1&&g_Distance[m_nCurCityNo][i]==1) //城市没去过且相邻
		{prob[i]=(pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA))/accumulate;
         dbTotal=dbTotal+prob[i];
		}
		else
		{
			prob[i]=0.0;
		}
	}

	//轮盘选择
	double dbTemp=0.0;
	if (dbTotal > 0.0) //总的信息素值大于0
	{
		dbTemp=rnd(0.0,dbTotal); //取一个随机数

		for (i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1&&g_Distance[m_nCurCityNo][i]==1) //****城市没去过，此处不用加&& g_Distance[m_nCurCityNo][i]1=DB_MAX 因为不会被选中
			{
				dbTemp=dbTemp-prob[i]; //这个操作相当于转动轮盘，如果对轮盘选择不熟悉，仔细考虑一下
				if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，跳出最近for循环
				{
					nSelectedCity=i;
					break;
				}
			}
		}
	}

	//==============================================================================
	//如果城市间的信息素非常小 ( 小到比double能够表示的最小的数字还要小 )
	//那么由于浮点运算的误差原因，上面计算的概率总和可能为0
	//会出现经过上述操作，没有城市被选择出来
	//出现这种情况，就把第一个没去过的城市作为返回结果，******或许这个也可以用在信道选择不成功的情况下
	if (nSelectedCity == -1)
	{
		for (int i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1&&g_Distance[m_nCurCityNo][i]==1) //与当前城市临近且没去过*****
			{  
				nSelectedCity=i;
				break;
			}
		}
	}

	//返回结果	
	return nSelectedCity;
}

//检查选定的下一跳是否有可用信道：返回flag表示是否要杀死这只蚂蚁，如果杀则flag为1
int Ant::Check()
{
	int flag,round;//flag返回受阻1或不受阻0，round计数回环次数
	//int Channel_No;//来自信道的信息，如果信道无空闲需要重新选择下一跳则返回-1
	int next;//暂定下一跳
	for(round=0;round<3;round++)
	{
		next=ChooseNextCity();
		if (next==-1)
			flag=1;
		else
		{
			Small_channel=Public_channel[m_nCurCityNo][next];
			 Channel_No=Small_channel.Check(A_T,L_T,Wide);//保存信道标号
			if(Channel_No!=-1)//寻信道成功
			{
				flag=0;
				Move(next,Channel_No);//写入下一跳和信道
				break;
			}
			else
			{
				if(round==2 && Channel_No==-1) flag=1;
		
			}
		}	
	}
	return flag;
}


//单个蚂蚁的寻路过程
int Ant::Search()
{
	//_______________________________
	Init();

	while (m_nMovedCityCount < N_CITY_COUNT)
	{//	printf("wwwwwww=%d",m_nMovedCityCount);
		kAnt=Check();
		if(kAnt==1) 
		break;
		if(m_nPath[m_nMovedCityCount-1]==m_nDesCityNo)
			break;
	}
	if (m_nPath[m_nMovedCityCount-1]!=m_nDesCityNo)
	{  
		kAnt=1;
	}
	CalPathLength();
		return kAnt;


}

//蚂蚁在城市间移动
void Ant::Move(int CityNo ,int c)
{
	m_nPath[m_nMovedCityCount]=CityNo; //蚂蚁走的路径
	m_nLink[m_nMovedCityCount]=c;//对应的信道标号
	m_nAllowedCity[CityNo]=0;//nCityNo编号的城市标记为走过了
	m_nCurCityNo=CityNo; //当前所在城市编号
	m_nMovedCityCount++; //已经去过的城市数量 初始值为1

}
//计算蚂蚁走过的路径长度
void Ant::CalPathLength()
{
	m_dbPathLength=0.0;
	int m=0;
	int n=0;
	int z=0;
	int x=0;
	int s=0;
	for(z=0;m_nPath[z]!=-4&&z<N_CITY_COUNT;z++)
		x++;

	if(kAnt==1)
	{	m_dbPathLength=DB_MAX; //如果该蚂蚁被杀死，则该蚂蚁走过路径最长
	s=1;}
	else
	{
		for (int i=1;i<x;i++)
		{
			m=m_nPath[i];
			n=m_nPath[i-1];
			m_dbPathLength=m_dbPathLength+g_Distance[m][n];
		}

	}
//	printf("ssss=%d",s);
} 

