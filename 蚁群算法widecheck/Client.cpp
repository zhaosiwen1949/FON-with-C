#include "Client.h"
#include "Tsp.h"
#include "Channel.h"
#include "Common.h"

Client::Client(void)
{
}

Client::~Client(void)
{
}

void Client::Init()
{
}


int Client::Search()
{
	int flag;
	Wide=rnd(1,4);//����ŵ�������Ŀ
	tsp.A_T=A_T;
	tsp.L_T=L_T;
	tsp.Wide=Wide;

    // CurCityNo=0;
   //  DesCityNo=7;
   CurCityNo=rnd(0,N_CITY_COUNT);//���ѡ��һ����������
   DesCityNo=rnd(0,N_CITY_COUNT);//���ѡ��һ���յ����

    tsp.tm_nCurCityNo=CurCityNo;
    tsp.tm_nDesCityNo=DesCityNo;

	flag=tsp.Search();//������������ÿ��1 or 0
	return flag;
}