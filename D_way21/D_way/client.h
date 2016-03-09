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
	void Init();//初始化业务属性信道宽度  起始点
	int  Search();//业务请求函数，寻路结果flag赋值给city的block_flag

};
