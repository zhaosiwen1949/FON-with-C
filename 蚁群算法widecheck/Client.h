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
		//int StartCity;//让他在ant里自由选择吧
		Tsp tsp;
public:
	void Init();//初始化业务属性信道宽度
	int Search();//业务请求函数，寻路结果flag赋值给city的block_flag


};
