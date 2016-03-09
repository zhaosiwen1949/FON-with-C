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
	Wide=rnd(1,4);//随机信道带宽数目
	tsp.A_T=A_T;
	tsp.L_T=L_T;
	tsp.Wide=Wide;

    // CurCityNo=0;
   //  DesCityNo=7;
   CurCityNo=rnd(0,N_CITY_COUNT);//随机选择一个出发城市
   DesCityNo=rnd(0,N_CITY_COUNT);//随机选择一个终点城市

    tsp.tm_nCurCityNo=CurCityNo;
    tsp.tm_nDesCityNo=DesCityNo;

	flag=tsp.Search();//返回阻塞数，每次1 or 0
	return flag;
}