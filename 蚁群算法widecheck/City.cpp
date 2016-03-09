
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
    double stuck=0;//������
	int block_c=0;//ҵ����������
	int flag;//��ʱ�洢������
	//----------------------------------

	int miu=2;//leavetime ָ���ֲ�����
//1.�ŵ������͵ĳ�ʼ��
	for( i=0;i<N_CITY_COUNT;i++)
	{
		for(j=0;j<N_CITY_COUNT;j++)
		{
			Public_channel[i][j].Init();
		}
	}
//2.ҵ�������͵ĳ�ʼ��
	Client *client;
	client=( Client*) calloc(N_Client,sizeof ( Client)); 

//2.1ҵ��������lanmd�Ĳ��ɷֲ��������뿪ʱ��

	settable(12345,65435,34221,12345,9983651,95746118); 
		for(c=0;c<N_Client-1;c++)
		{
		   client[c+1].A_T=client[c].A_T-(1/lanmd)*log(UNI);  //����ʱ��������ָ���ֲ�
		}        
	settable(12345,65435,34221,12345,9983651,95746118);
		for(c=0;c<N_Client;c++)
		{
			client[c].L_T=client[c].A_T+exponential(miu); 
		}

	//	for(c=0;c<N_Client-10;c++)
	//	client[c+10].A_T=client[c].A_T;// ���100��ҵ�������ͬ�ĵ���ʱ��  ò��ûЧ��������

//����ҵ��򵥲����� ���ǵ��ӵ�Ŷ

//flag=client[2].Search();
//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
//printf("\n flag=\t %d",flag);
//stuck=(double)flag;

  
/////��ҵ�������/////////////////////////////////////////////////////////////////////////////////////////////////////
    //2.2 �𲽻�ȡ������
    for(n=1;n<N_Client;n++)
	{	
		//2.2.2  �ۼ�������Ŀ______������Ⱥ�㷨_____________________________________________
		//printf("\n-------------------------client [%d]--------------------\n",n);

		flag=client[n].Search();
		block_c+=flag;//�ռ�block-flag ��1.0��ֵ�����������
	}//for ���������������ʽ���

	stuck=(double)block_c*0.1/N_Client;
	printf("\n\n++++++++++++++++ stuck=%f\n",stuck);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//2.3 ���������	cout<<"\n\n we have done yet !!"<<endl;

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
	for(i=0;i<50;i++)   //��a��40Ϊ�����Ϊǿ���� ���з���simulate���������һ����Ӧ��������
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
		 
