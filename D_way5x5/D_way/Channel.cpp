#include "Channel.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

//
//50 channels wide={1,4,10,20}  client=1000 miu=0.2 lamd={0~}



Channel::Channel(void)
{
}

Channel::~Channel(void)
{
}
//��ʼ���ŵ���Ϣ
void Channel::Init()
{
	for(int k=0;k<N_CHNL;k++)
	{
		L_T[k]=0.0;
	}
}
//��ѯ�Ƿ��п����ŵ��������ŵ����select
//���룺A_T;L_T;wide
//������ŵ���Ѱ��� ��ѡ -1�����ŵ��� 0��1,2�������ȷǸ�ֵ
int Channel::Check(double arrive,double leave,int wide)
{
	
	int Select=-1;
	int k,w;
	int n=0;
	int last;//���������ŵ����
	for(k=0;k<N_CHNL;k++)  
		nobusy[k]=-1;//��ʼ �޿����ŵ�

   //1.1-----���������ŵ�
	for(k=0;k<N_CHNL;k++)
	{
		if(L_T[k]<=arrive) 
		{
			nobusy[n]=k;
			n=n+1;
		}
	}
	//-------------------------- �����
//	printf("\n nobusy:\n");

//	for(k=0;k<1000;k++)
//	{
//		printf("%d\t",nobusy[k]);
//	}
//-----------------------------------------

   //2----����wide������Ѱ���ҵ����ʴ�С���ŵ���-----------�������2��Select=0 Ҫһ���ŵ�
		
	if(wide==1)
	{
		Select=nobusy[0];
		return Select;
	}
	else
	{
		w=1;//��w=1��ʼ��ѡ��1���ŵ�
	    for( n=0;n<N_CHNL-1;n++ )
		{
			if(w==wide)
				{
					last=nobusy[n];//�����ŵ������ŵ�������һ���ŵ����
					Select=last-wide+1;//�ŵ��׸����
					return Select;//-----------�������3��Select=ĳ�ŵ�ͷ �������ŵ�
				}
			else
				{
					if(nobusy[n+1]==nobusy[n]+1 ){w++;}				
					else w=1;			
				}
			if(n==N_CHNL-2 && w<wide) 
			{
			//	cout<<"we didn't find the enough channels ,sorry~!"<<endl;δ�ҵ����ʵ�
				Select=-1;
				return Select;//-----------�������4��Select=-1 û�к��ʿ�ȵ��ŵ�
			}		
		}//forѭ������
	return Select;	
	}
}