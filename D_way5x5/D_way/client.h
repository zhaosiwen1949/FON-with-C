#pragma once
#include "D_search.h"


class client{
public:
	client(void);
	~client(void);
public:
		double A_T;
		double L_T;
		int Wide;
		int start_city;
		int dest_city;
public:
		D_search D_try;

public:
	void Init();//��ʼ��ҵ�������ŵ����  ��ʼ��
	int  Search();//ҵ����������Ѱ·���flag��ֵ��city��block_flag

};
