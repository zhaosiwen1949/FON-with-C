
#pragma once


#include <iostream>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include "Channel.h"

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�



//------------------------------------------------------------
const int N_CITY_COUNT=14; //��������
const int N_ANT_COUNT=20; //��������
const int N_IT_COUNT=10; //��������1000
const int N_Client=100; //ҵ���� 1000����arrivetime[]
//const int N_Channel=10;//���ڵ���ŵ���
const int N_LXD=5;

//��Ⱥ�㷨����
const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.5; //��Ϣ�ش��ݲ���

const double DBQ=100.0; //�ܵ���Ϣ��
const double DB_MAX=1000000; //һ����־��


extern double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //�������м���Ϣ��
extern double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //�������м����
extern 	Channel Public_channel[N_CITY_COUNT][N_CITY_COUNT];//ȫ���ŵ���Ϣ��һ�γ�ʼ�������ɴθ���




extern int rnd(int nLow,int nUpper); //�������������
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);
extern double expntl(double x);


//extern double x_Ary[N_CITY_COUNT];
//extern double y_Ary[N_CITY_COUNT];

