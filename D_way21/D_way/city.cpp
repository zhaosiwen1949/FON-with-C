
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "common.h"
#include "data.h"
//50 channels wide={1,4,10,20}  client=1000 miu=0.2 lamd={0~}

//主函数，主要做输入输出工作
// 改变miu值收效甚微，尝试改变leavetime的计算方法，干脆直接服务时间固定好了 比如0.01
double simulate(double lanmd)
{
    double stuck;//阻塞率
	//___________________________________________________________________________
	int i,j,c,n;
	//---------------------------
	int block;//业务被阻塞数量
	int block_c=0;
    double miu=0.2;//leavetime 指数分布参数

//1.信道类类型的初始化
//	Channel Public_channel[N_CITY_COUNT][N_CITY_COUNT];//全局信道信息，一次初始化，若干次更新
	for( i=0;i<N_CITY;i++)
	{
		for(j=0;j<N_CITY;j++)
		{
			Public_channel[i][j].Init();
		}
	}
//2.业务类类型的初始化
	client *Client;//1000个业务单lanmd
	Client=(client*)calloc(N_Client,sizeof(client)); 

//2.1业务流服从lanmd的泊松分布到达与离开时间

		settable(12345,65435,34221,12345,9983651,95746118); 
		for(c=0;c<N_Client-1;c++)
		{
		   Client[c+1].A_T=Client[c].A_T-(1/lanmd)*log(UNI);  //到达时间间隔服从指数分布
		}        
		settable(12345,65435,34221,12345,9983651,95746118);
		for(c=0;c<N_Client;c++)
		{
		//	Client[c].L_T=Client[c].A_T+0.02; 
			Client[c].L_T=Client[c].A_T+exponential(miu); 
		}
		//for(c=0;c<N_Client-100;c++)
		//Client[c].A_T=Client[c+100].A_T;// 最后的100个业务与前面的100个业务到达时刻相同 
/////多业务测试用/////////////////////////////////////////////////////////////////////////////////////////////////////

    //2.2 逐步获取阻塞率
    for(n=1;n<N_Client;n++)
	{
		Client[n].Init();// wide start dest	
	//	printf("the A_T is:%lf\n",Client[n].A_T);
	//	printf("the L_T is:%lf\n",Client[n].L_T);
		block=Client[n].Search();
	//	printf("\n>>>> block =:%d\n",block);

		block_c=block+block_c;//收集block-flag 的1.0等值，获得阻塞数
	//	printf("\n>>>> block_c =:%d\n",block_c);


	}//for 结束，逐步求阻塞率结束

	stuck=(double)block_c/N_Client;// update 业务量*************
//	printf("\n>>>>stuck =:%lf\n",stuck);

		//2.3 输出阻塞率	cout<<"\n\n we have done yet !!"<<endl;

	free(Client);

	return stuck;

}



/*--------------------------------------------main function-------------------------------------------*/
FILE *output;
int main()
{
	int i; 
	double a;
	//printf("************************************************************* \n");
	output=fopen("simulate.txt","w");
	/*/
	a=1000;
	fprintf(output,"%lf\n",simulate(a));
	printf("%lf\n",simulate(a));

	*/
	//x ray=lamd * 0.2  0,5,10,....100
	// 业务量=lanmd*miu@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	a=0;
	for(i=0;i<30;i++)   //以a（40为间隔）为强度人 运行仿真simulate函数，输出一列相应的阻塞率
	{
		a=a+25;
		fprintf(output,"%lf\n",simulate(a));
		printf("[%d]==%lf\n",i,simulate(a));
	}
	printf("\n");
	printf("\n");
	printf("\n");
    fclose(output);
	//
	system("pause");

	return 0;

}
		 


