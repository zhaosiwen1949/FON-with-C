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
		int dist[N_CITY];//���·������
		int prev[N_CITY];//ǰһ���ڵ�ռ�
		//int block;

	public:
		void Init();
		//void Search_way(int n,int start,int cost[14][14]);//���Ѱ·����
		void Search_way(int n,int start,int cost[21][21]);//���Ѱ·����

		int Show_way(int n,int start,int dest);//���� block��ɼȶ��ĳ������е�Ŀ�ĳ��е�way[]�γ������
		int Check_way(int count);//���ڼ���ŵ��Ƿ����~
		void C_arrange(int count);//���ڸ����ŵ�ռ��ʱ��
};
