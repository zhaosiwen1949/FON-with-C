
#include "Tsp.h"
#include "Ant.h"
#include "Channel.h"
#include "Common.h"
#include "Client.h"
#include "Data.h"
using namespace std;



double Simulate(double lanmd)
{
	int i,j,c,n;
	//---------------------------
    double stuck=0;//阻塞率
	int block_c=0;//业务被阻塞数量
	int flag;//临时存储阻塞数
	//----------------------------------

	int miu=2;//leavetime 指数分布参数
//1.信道类类型的初始化
	for( i=0;i<N_CITY_COUNT;i++)
	{
		for(j=0;j<N_CITY_COUNT;j++)
		{
			Public_channel[i][j].Init();
		}
	}
//2.业务类类型的初始化
	Client *client;
	client=( Client*) calloc(N_Client,sizeof ( Client)); 

//2.1业务流服从lanmd的泊松分布到达与离开时间

	settable(12345,65435,34221,12345,9983651,95746118); 
		for(c=0;c<N_Client-1;c++)
		{
		   client[c+1].A_T=client[c].A_T-(1/lanmd)*log(UNI);  //到达时间间隔服从指数分布
		}        
	settable(12345,65435,34221,12345,9983651,95746118);
		for(c=0;c<N_Client;c++)
		{
			client[c].L_T=client[c].A_T+exponential(miu); 
		}

	//	for(c=0;c<N_Client-10;c++)
	//	client[c+10].A_T=client[c].A_T;// 间隔100个业务具有相同的到达时刻  貌似没效果，算了

//单个业务简单测试用 最后记得扔掉哦

//flag=client[2].Search();
//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
//printf("\n flag=\t %d",flag);
//stuck=(double)flag;

  
/////多业务测试用/////////////////////////////////////////////////////////////////////////////////////////////////////
    //2.2 逐步获取阻塞率
    for(n=1;n<N_Client;n++)
	{	
		//2.2.2  累计阻塞数目______调用蚁群算法_____________________________________________
		//printf("\n-------------------------client [%d]--------------------\n",n);

		flag=client[n].Search();
		block_c+=flag;//收集block-flag 的1.0等值，获得阻塞数
	}//for 结束，逐步求阻塞率结束

	stuck=(double)block_c*0.1/N_Client;
	printf("\n\n++++++++++++++++ stuck=%f\n",stuck);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//2.3 输出阻塞率	cout<<"\n\n we have done yet !!"<<endl;

	free(client);

	return stuck;



}



/*--------------------------------------------main function-------------------------------------------*/
FILE *output;
int main()
{
	int i; 
	double a;
//	cout<<"the result is :"<<Simulate(a)<<endl;
	
	output=fopen("simulate.txt","w");
	a=0;
	for(i=0;i<50;i++)   //以a（40为间隔）为强度人 运行仿真simulate函数，输出一列相应的阻塞率
	{
		a=a+20;
	fprintf(output,"%f\n",Simulate(a));
		printf("%f\n",Simulate(a));
	}
//	a=50;
//	fprintf(output,"%f\n",Simulate(a));
	printf("\n");
	printf("\n");
	printf("\n");
    fclose(output);  
	//int stay;
	//cin>>stay;
	return 0;

}
		 
