
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "common.h"
#include "data.h"
//50 channels wide={1,4,10,20}  client=1000 miu=0.2 lamd={0~}

//����������Ҫ�������������
// �ı�miuֵ��Ч��΢�����Ըı�leavetime�ļ��㷽�����ɴ�ֱ�ӷ���ʱ��̶����� ����0.01
double simulate(double lanmd)
{
    double stuck;//������
	//___________________________________________________________________________
	int i,j,c,n;
	//---------------------------
	int block;//ҵ����������
	int block_c=0;
    double miu=0.2;//leavetime ָ���ֲ�����

//1.�ŵ������͵ĳ�ʼ��
//	Channel Public_channel[N_CITY_COUNT][N_CITY_COUNT];//ȫ���ŵ���Ϣ��һ�γ�ʼ�������ɴθ���
	for( i=0;i<N_CITY;i++)
	{
		for(j=0;j<N_CITY;j++)
		{
			Public_channel[i][j].Init();
		}
	}
//2.ҵ�������͵ĳ�ʼ��
	client *Client;//1000��ҵ��lanmd
	Client=(client*)calloc(N_Client,sizeof(client)); 

//2.1ҵ��������lanmd�Ĳ��ɷֲ��������뿪ʱ��

		settable(12345,65435,34221,12345,9983651,95746118); 
		for(c=0;c<N_Client-1;c++)
		{
		   Client[c+1].A_T=Client[c].A_T-(1/lanmd)*log(UNI);  //����ʱ��������ָ���ֲ�
		}        
		settable(12345,65435,34221,12345,9983651,95746118);
		for(c=0;c<N_Client;c++)
		{
		//	Client[c].L_T=Client[c].A_T+0.02; 
			Client[c].L_T=Client[c].A_T+exponential(miu); 
		}
		//for(c=0;c<N_Client-100;c++)
		//Client[c].A_T=Client[c+100].A_T;// ����100��ҵ����ǰ���100��ҵ�񵽴�ʱ����ͬ 
/////��ҵ�������/////////////////////////////////////////////////////////////////////////////////////////////////////

    //2.2 �𲽻�ȡ������
    for(n=1;n<N_Client;n++)
	{
		Client[n].Init();// wide start dest	
	//	printf("the A_T is:%lf\n",Client[n].A_T);
	//	printf("the L_T is:%lf\n",Client[n].L_T);
		block=Client[n].Search();
	//	printf("\n>>>> block =:%d\n",block);

		block_c=block+block_c;//�ռ�block-flag ��1.0��ֵ�����������
	//	printf("\n>>>> block_c =:%d\n",block_c);


	}//for ���������������ʽ���

	stuck=(double)block_c/N_Client;// update ҵ����*************
//	printf("\n>>>>stuck =:%lf\n",stuck);

		//2.3 ���������	cout<<"\n\n we have done yet !!"<<endl;

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
	// ҵ����=lanmd*miu@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	a=0;
	for(i=0;i<30;i++)   //��a��40Ϊ�����Ϊǿ���� ���з���simulate���������һ����Ӧ��������
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
		 


