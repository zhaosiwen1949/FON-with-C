#include "Ant.h"


Ant::Ant(void)
{
}

Ant::~Ant(void)
{
}
//��ʼ��
void Ant::Init()
{
	int i;
	for (i=0;i<N_CITY_COUNT;i++)
	{
		m_nAllowedCity[i]=1; //����ȫ������Ϊû��ȥ��
		m_nPath[i]=-4; //�����ߵ�·��ȫ������Ϊ0
		m_nLink[i]=0;//����ѡ����ŵ���Ϊ0�ŵ�
	}

	//�����߹���·����������Ϊ0
	m_dbPathLength=0.0; 

	
	//m_nCurCityNo=rnd(0,N_CITY_COUNT);//���ѡ��һ����������
    //m_nDesCityNo=rnd(0,N_CITY_COUNT);//���ѡ��һ���յ����
	//���ó������кͳ�ʼ�ŵ�
	m_nPath[0]=m_nCurCityNo;
	m_nLink[0]=0;
	//��ʶ��������Ϊ�Ѿ�ȥ����
	m_nAllowedCity[m_nCurCityNo]=0; 

	//�Ѿ�ȥ���ĳ�����������Ϊ1
	m_nMovedCityCount=1; 

} 

//ѡ����һ�����У�nSelectedCity
int Ant::ChooseNextCity()
{
	int i;
	int nSelectedCity=-1;//��ʱ��ʾδѡ����һ������
	//_______________________________________________________________________

	//���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
	double dbTotal=0.0;	
	double prob[N_CITY_COUNT]; // ������б�ѡ�еĸ���
    double accumulate=0.0;
	for (i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i]==1&&g_Distance[m_nCurCityNo][i]==1) //����ûȥ��������
		{
			accumulate=accumulate+pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA); //cur���е�i���еĸ���
		//�ۼ���Ϣ�أ��õ��ܺ�  ֻ��Ե�ǰ�����������һ����Ϣ�ص��ۼ�
		}
	}
for (i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i]==1&&g_Distance[m_nCurCityNo][i]==1) //����ûȥ��������
		{prob[i]=(pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA))/accumulate;
         dbTotal=dbTotal+prob[i];
		}
		else
		{
			prob[i]=0.0;
		}
	}

	//����ѡ��
	double dbTemp=0.0;
	if (dbTotal > 0.0) //�ܵ���Ϣ��ֵ����0
	{
		dbTemp=rnd(0.0,dbTotal); //ȡһ�������

		for (i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1&&g_Distance[m_nCurCityNo][i]==1) //****����ûȥ�����˴����ü�&& g_Distance[m_nCurCityNo][i]1=DB_MAX ��Ϊ���ᱻѡ��
			{
				dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
				if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ��������forѭ��
				{
					nSelectedCity=i;
					break;
				}
			}
		}
	}

	//==============================================================================
	//������м����Ϣ�طǳ�С ( С����double�ܹ���ʾ����С�����ֻ�ҪС )
	//��ô���ڸ�����������ԭ���������ĸ����ܺͿ���Ϊ0
	//����־�������������û�г��б�ѡ�����
	//��������������Ͱѵ�һ��ûȥ���ĳ�����Ϊ���ؽ����******�������Ҳ���������ŵ�ѡ�񲻳ɹ��������
	if (nSelectedCity == -1)
	{
		for (int i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1&&g_Distance[m_nCurCityNo][i]==1) //�뵱ǰ�����ٽ���ûȥ��*****
			{  
				nSelectedCity=i;
				break;
			}
		}
	}

	//���ؽ��	
	return nSelectedCity;
}

//���ѡ������һ���Ƿ��п����ŵ�������flag��ʾ�Ƿ�Ҫɱ����ֻ���ϣ����ɱ��flagΪ1
int Ant::Check()
{
	int flag,round;//flag��������1������0��round�����ػ�����
	//int Channel_No;//�����ŵ�����Ϣ������ŵ��޿�����Ҫ����ѡ����һ���򷵻�-1
	int next;//�ݶ���һ��
	for(round=0;round<3;round++)
	{
		next=ChooseNextCity();
		if (next==-1)
			flag=1;
		else
		{
			Small_channel=Public_channel[m_nCurCityNo][next];
			 Channel_No=Small_channel.Check(A_T,L_T,Wide);//�����ŵ����
			if(Channel_No!=-1)//Ѱ�ŵ��ɹ�
			{
				flag=0;
				Move(next,Channel_No);//д����һ�����ŵ�
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


//�������ϵ�Ѱ·����
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

//�����ڳ��м��ƶ�
void Ant::Move(int CityNo ,int c)
{
	m_nPath[m_nMovedCityCount]=CityNo; //�����ߵ�·��
	m_nLink[m_nMovedCityCount]=c;//��Ӧ���ŵ����
	m_nAllowedCity[CityNo]=0;//nCityNo��ŵĳ��б��Ϊ�߹���
	m_nCurCityNo=CityNo; //��ǰ���ڳ��б��
	m_nMovedCityCount++; //�Ѿ�ȥ���ĳ������� ��ʼֵΪ1

}
//���������߹���·������
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
	{	m_dbPathLength=DB_MAX; //��������ϱ�ɱ������������߹�·���
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

