#pragma once

#include <math.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>
 
#include "Channel.h"


const int N_CITY=14;
//const int N_CITY=21;
const int N_Client=1000; //业务数 1000用于arrivetime[]
const int N_CHNL=1000;//信道数 slot
const int maxint=65535; //定义一个最大的数值，作为不相连的两个节点的代价权值 相当于无穷

extern int rnd(int nLow,int nUpper); //返回随机数函数
extern int cost[N_CITY][N_CITY];
//extern int cost[N_CITY][N_CITY];
extern 	Channel Public_channel[N_CITY][N_CITY];//全局信道信息，一次初始化，若干次更新

