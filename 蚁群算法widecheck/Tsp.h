
//Tsp的头文件
#pragma once

#include "Ant.h"
#include "Channel.h"
#include "Common.h"


class Tsp{
public:
	Tsp(void);
	~Tsp(void);
	public:
		double A_T;
		double L_T;
		int Wide;
		int tm_nCurCityNo;
		int tm_nDesCityNo;
	public:
	//	Channel Big_channel[N_CITY_COUNT][N_CITY_COUNT];
		Ant m_nAnt[N_ANT_COUNT];
		Ant BestAnt;
	public:
		void C_Init();//用于程序首部初始化bigchannel信息  仅仅一次初始化
		int Search();
		void Update();
		void Init();
		//对一次蚁群算法后对信道占用整合一次
		void C_arrange();


};