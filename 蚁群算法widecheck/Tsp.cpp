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

//�����ײ���ʼ��bigchannel��Ϣ  ���ĳ�ʼ����client.init �е���tsp.c_initʵ��
void Tsp::C_Init()
{
}

//��ʼ��·������Ϣ��
void Tsp::Init()
{
	//--------
	int i,j;
	BestAnt.m_dbPathLength=DB_MAX; 

	//��ʼ��������Ϣ��
	for ( i=0;i<N_CITY_COUNT;i++)
	{
		for ( j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=1;
		}
	}
}


//����ֵ ������ ����1��������������0�һ�ȡ�������ϵĽ�
int Tsp::Search()
{
	Init();
	int  block_flag;//����0��1
	int i,j;
	int countflag=0;
	int kill;//�������������������kill=ant�����������һ��������������е�����ɣ�ÿ�ζ����ϱ�ɱ�����򷵻�block-flagֵΪ1

	//1��ʼ��Ⱥ�㷨
	for (i=0;i<N_IT_COUNT;i++)
	{
	//	printf("\n��ʼ��  %d ��ѭ��\n",i);

		kill=0;
	
		//1.1ÿֻ��������һ��
		for (j=0;j<N_ANT_COUNT;j++)
		{
			//1.1.2�н�ҵ��Ҫ��
			m_nAnt[j].Wide=Wide;
			m_nAnt[j].A_T=A_T; 
			m_nAnt[j].L_T=L_T;
            m_nAnt[j].m_nCurCityNo=tm_nCurCityNo;
            m_nAnt[j].m_nDesCityNo=tm_nDesCityNo;
			//1.1.3����������ɱ��Ŀ
			kill+=m_nAnt[j].Search(); 
		}//������������
		//1.2 ����������϶���ɱ������������������
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
		//1.3 ������ѽ��������Ψһ����·��
		for (j=0;j<N_ANT_COUNT;j++) 
		{

			if (m_nAnt[j].m_dbPathLength < BestAnt.m_dbPathLength)
			{
				BestAnt=m_nAnt[j];
			}
		}

		//���»�����Ϣ��
		if(BestAnt.m_dbPathLength!=DB_MAX)
		{
			Update();

		}
		//������
		/*
		printf("\n start_city=%d,end_city=%d\n", tm_nCurCityNo,tm_nDesCityNo);
		for(j=0;j<N_CITY_COUNT;j++)
		{	
			printf("%d-->",BestAnt.m_nPath[j]);
		}
		*/

	}//�������


	if(countflag==N_IT_COUNT)
	{
		block_flag=1;
		printf("\n block_flag=1");
	}
	else
	{	
		printf("\n block_flag=0");
		C_arrange();
//	    printf("\n����");
	}
	return block_flag ;//�����Ӧ�÷���break����1ֵ

}

void Tsp::Update()
{
	int i,j,z;
	//��ʱ������Ϣ��
	double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
	memset(dbTempAry,0,sizeof(dbTempAry)); //��ȫ������Ϊ0

	//���������ӵ���Ϣ��,���浽��ʱ������
	int m=0;
	int n=0;
	for (i=0;i<N_ANT_COUNT;i++) //����ÿֻ�������µ���Ϣ��
	{int x=0;
			for(z=0;m_nAnt[i].m_nPath[z]!=-4&&z<N_CITY_COUNT;z++)
			 x++;
			for (j=1;j<x;j++)//m_nAnt[i].m_nPat��¼ÿֻ�����ߵ��յ��·��
			{ if (m_nAnt[i].kAnt!=1)
				{
					m=m_nAnt[i].m_nPath[j];
					n=m_nAnt[i].m_nPath[j-1];
					dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_nAnt[i].m_dbPathLength;//��Ϣ������100
					dbTempAry[m][n]=dbTempAry[n][m];
				}
			}

			//�����кͿ�ʼ����֮�����Ϣ��
		//	n=m_nAnt[i].m_nPath[0];
		//	dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_nAnt[i].m_dbPathLength;
		//	dbTempAry[m][n]=dbTempAry[n][m];

	}

	//���»�����Ϣ��
	for (i=0;i<N_CITY_COUNT;i++) 
	{
		for (j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j];  
		}
	}


}
//һ����Ⱥ�㷨��<����>�����߹�·���ϵ��ŵ�ռ���뿪ʱ�����
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
