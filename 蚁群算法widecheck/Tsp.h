
//Tsp��ͷ�ļ�
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
		void C_Init();//���ڳ����ײ���ʼ��bigchannel��Ϣ  ����һ�γ�ʼ��
		int Search();
		void Update();
		void Init();
		//��һ����Ⱥ�㷨����ŵ�ռ������һ��
		void C_arrange();


};