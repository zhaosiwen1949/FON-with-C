#pragma once

#include "Tsp.h"

class Client{
public:
	Client(void);
	~Client(void);
public:
		double A_T;
		double L_T;
		int Wide;
                int CurCityNo;
		int DesCityNo;
		//int StartCity;//������ant������ѡ���
		Tsp tsp;
public:
	void Init();//��ʼ��ҵ�������ŵ����
	int Search();//ҵ����������Ѱ·���flag��ֵ��city��block_flag


};
