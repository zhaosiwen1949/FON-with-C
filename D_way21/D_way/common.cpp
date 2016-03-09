#include "common.h"

Channel Public_channel[N_CITY][N_CITY];

/*
int cost[14][14]={
		0,1,1,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
		1,0,1,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,65535,
		1,1,0,65535,65535,1,65535,65535,65535,65535,65535,65535,65535,65535,
		1,65535,65535,0,1,65535,65535,65535,1,65535,65535,65535,65535,65535,
		65535,65535,65535,1,0,1,1,65535,65535,65535,65535,65535,65535,65535,
		65535,65535,1,65535,1,0,65535,65535,65535,65535,1,65535,1,65535,
		65535,65535,65535,65535,1,65535,0,1,65535,65535,65535,65535,65535,65535,
		65535,1,65535,65535,65535,65535,1,0,65535,1,65535,65535,65535,65535,
		65535,65535,65535,1,65535,65535,65535,65535,0,65535,65535,1,65535,1,
		65535,65535,65535,65535,65535,65535,65535,1,65535,0,1,1,65535,1,
		65535,65535,65535,65535,65535,1,65535,65535,65535,1,0,65535,65535,65535,
		65535,65535,65535,65535,65535,65535,65535,65535,1,1,65535,0,1,65535,
		65535,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,1,0,1,
		65535,65535,65535,65535,65535,65535,65535,65535,1,1,65535,65535,1,0	
	};
*/
int cost[21][21]={
	         0,1,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             1,0,1,1,65535,65535,65535,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             1,1,0,65535,65535,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,1,65535,0,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,1,0,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,1,65535,1,0,1,65535,65535,65535,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,1,0,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,1,65535,65535,65535,65535,1,0,1,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,1,0,65535,65535,1,65535,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,1,65535,0,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,1,65535,65535,65535,65535,0,65535,65535,65535,65535,1,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,1,65535,65535,0,1,65535,65535,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,0,1,65535,65535,1,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,0,1,65535,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,65535,65535,1,0,1,65535,65535,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,65535,65535,65535,0,65535,1,65535,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,65535,65535,0,65535,1,65535,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,0,65535,1,65535,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,0,65535,1,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,65535,0,1,
             65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,1,1,0

};
int rnd(int nLow,int nUpper)
{
	
	return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);

}


