#pragma once

#include <math.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>
 
#include "Channel.h"


//const int N_CITY=14;
const int N_CITY=21;
const int N_Client=1000; //ҵ���� 1000����arrivetime[]
const int maxint=65535; //����һ��������ֵ����Ϊ�������������ڵ�Ĵ���Ȩֵ �൱������

extern int rnd(int nLow,int nUpper); //�������������
//extern int cost[14][14];
extern int cost[21][21];
extern 	Channel Public_channel[N_CITY][N_CITY];//ȫ���ŵ���Ϣ��һ�γ�ʼ�������ɴθ���

