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
		int kAnt;//��¼������ �൱��flag
		Channel Small_channel;
	public:
		int m_nPath[N_CITY_COUNT]; //�����ߵ�·��
		int m_nLink[N_CITY_COUNT];//·����Ӧ���ŵ���ţ��׸�Ӧ��Ϊ0
		double m_dbPathLength; //�����߹���·������

		int m_nAllowedCity[N_CITY_COUNT]; //ûȥ���ĳ���
	//	int m_nCurCityNo; //��ǰ���ڳ��б��
		int m_nMovedCityCount; //�Ѿ�ȥ���ĳ�������
		int Channel_No;//��¼ÿ���ҵ��ĺ����ŵ�����׸����


	public:
		void Init(); //��ʼ��
		int Search(); //����·��,����kill�ࣺ����ֵkAnt 0 or 1
		int ChooseNextCity(); //ѡ����һ�����У�nSelectedCity
		int Check(); //���ѡ������һ���Ƿ��п����ŵ�������flag��ʾ�Ƿ�Ҫɱ����ֻ���ϣ����ɱ��flagΪ1
		void Move(int CityNo ,int c); //�����ڳ��м��ƶ�
		void CalPathLength(); //���������߹���·������



};