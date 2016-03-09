//#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"


int poissrnd(double lambda)
{
double rnd=(rand()+0.0)/RAND_MAX;
double p=exp(-lambda);
double pos=p;
int k=0;
    while(1)
	{
	if(pos>rnd)
		return k;
	k++;
	p*=lambda/k;
	pos+=p;
	
	}

}

int main(int argc,TCHAR* argv[])
{
srand(time(NULL));
for(int i=0;i<200;i++)
{
printf("%d\n",poissrnd(5));
getchar();

}
}