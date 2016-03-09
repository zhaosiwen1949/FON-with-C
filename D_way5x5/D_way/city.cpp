
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "common.h"
#include "data.h"
//1000 channels wide={1,4,10,20}  client=1000 miu=0.2 lamd={0~}

//主函数，主要做输入输出工作
double simulate(double lanmd)
{
    double stuck;//阻塞率
	//___________________________________________________________________________
	int i,j,c,n;
	//---------------------------
	int block;//业务被阻塞数量
	int block_c=0;
    double miu=1.06;//leavetime 指数分布参数

//1.信道类类型的初始化
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
			Client[c].L_T=Client[c].A_T+exponential(miu); 
		}
/////多业务测试用/////////////////////////////////////////////////////////////////////////////////////////////////////

    //2.2 逐步获取阻塞率
    for(n=1;n<N_Client;n++)
	{
		Client[n].Init();// wide start dest	
	//	printf("the A_T is:%lf\n",Client[n].A_T);
	//	printf("the L_T is:%lf\n",Client[n].L_T);
		block=Client[n].Search();
		block_c=block+block_c;//收集block-flag 的1.0等值，获得阻塞数
	}//for 结束，逐步求阻塞率结束

	stuck=(double)block_c*0.1/N_Client;// update 业务量*************
//	printf("\n>>>>stuck =:%lf\n",stuck);

	free(Client);
	return stuck;

}



/*--------------------------------------------main function-------------------------------------------*/
FILE *output;
int main()
{
	int i; 
	double a;
	output=fopen("simulate.txt","w");
	/*/ 单个业务
	a=1000;
	fprintf(output,"%lf\n",simulate(a));
	printf("%lf\n",simulate(a));

	*/
	a=0;
	for(i=0;i<20;i++)   //以a（ xx为间隔）为强度人 运行仿真simulate函数，输出一列相应的阻塞率
	{
		a=a+10;
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
		 


