
#pragma once


#include <iostream>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include "Channel.h"

// TODO: 在此处引用程序要求的附加头文件



//------------------------------------------------------------
const int N_CITY_COUNT=14; //城市数量
const int N_ANT_COUNT=20; //蚂蚁数量
const int N_IT_COUNT=10; //迭代次数1000
const int N_Client=100; //业务数 1000用于arrivetime[]
//const int N_Channel=10;//俩节点间信道数
const int N_LXD=5;

//蚁群算法参数
const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.5; //信息素传递参数

const double DBQ=100.0; //总的信息素
const double DB_MAX=1000000; //一个标志数


extern double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间信息素
extern double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间距离
extern 	Channel Public_channel[N_CITY_COUNT][N_CITY_COUNT];//全局信道信息，一次初始化，若干次更新




extern int rnd(int nLow,int nUpper); //返回随机数函数
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);
extern double expntl(double x);


//extern double x_Ary[N_CITY_COUNT];
//extern double y_Ary[N_CITY_COUNT];

