#pragma once

#include "Channel.h"
#include "Common.h"



class Ant{
	public:
		Ant(void);
		~Ant(void);
	public:
		double A_T;
		double L_T;
		int Wide;
        int m_nCurCityNo;
		int m_nDesCityNo;
		int kAnt;//记录蚂蚁死 相当于flag
		Channel Small_channel;
	public:
		int m_nPath[N_CITY_COUNT]; //蚂蚁走的路径
		int m_nLink[N_CITY_COUNT];//路径对应的信道标号，首个应该为0
		double m_dbPathLength; //蚂蚁走过的路径长度

		int m_nAllowedCity[N_CITY_COUNT]; //没去过的城市
	//	int m_nCurCityNo; //当前所在城市编号
		int m_nMovedCityCount; //已经去过的城市数量
		int Channel_No;//记录每次找到的合适信道组的首个标号


	public:
		void Init(); //初始化
		int Search(); //搜索路径,带有kill类：返回值kAnt 0 or 1
		int ChooseNextCity(); //选择下一个城市：nSelectedCity
		int Check(); //检查选定的下一跳是佛有可用信道：返回flag表示是否要杀死这只蚂蚁，如果杀则flag为1
		void Move(int CityNo ,int c); //蚂蚁在城市间移动
		void CalPathLength(); //计算蚂蚁走过的路径长度



};