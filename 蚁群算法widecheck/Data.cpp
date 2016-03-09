#include "Data.h"

/*--------------------------------------produce U(0,1)-产生（0，1）正态分布------------------------------*/
void settable(UL i1,UL i2,UL i3,UL i4,UL i5, UL i6)
{ int i; z=i1;w=i2,jsr=i3; jcong=i4; a=i5; b=i6;
  for(i=0;i<256;i=i+1) t[i]=KISS; 
}

/*----------------------------produce exponential distribution-产生指数分布-x为-------------------------------*/
double exponential(int miu)
{   double x;
	x=-(miu*log(1-UNI));
	return x;
}


//------------------------------------------------------------------------------------------------
