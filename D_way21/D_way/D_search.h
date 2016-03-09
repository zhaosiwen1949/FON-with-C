#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "Channel.h"



class D_search{

	public:
		D_search(void);
		~D_search(void);
	public:
		double A_T;
		double L_T;
		int Wide;
	public: 
		int way[N_CITY];
		int way_link[N_CITY];
		int dist[N_CITY];//最短路径代价
		int prev[N_CITY];//前一跳节点空间
		//int block;

	public:
		void Init();
		//void Search_way(int n,int start,int cost[14][14]);//完成寻路过程
		void Search_way(int n,int start,int cost[21][21]);//完成寻路过程

		int Show_way(int n,int start,int dest);//返回 block完成既定的出发城市到目的城市的way[]形成与输出
		int Check_way(int count);//用于检查信道是否可用~
		void C_arrange(int count);//用于更新信道占用时间
};
