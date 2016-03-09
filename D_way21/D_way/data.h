#pragma once



#include <stdio.h> 
#include <math.h>
#include <iomanip>   //I/O流控制头文件
#include <fstream>   //#include <fstream.h>为原作用法，在vc6中已经更改，用这两行代替


#define znew (z=36969*(z&65535)+(z>>16))
#define wnew (w=18000*(w&65535)+(w>>16))
#define MWC ((znew<<16)+wnew )
#define SHR3 (jsr^=(jsr<<17), jsr^=(jsr>>13), jsr^=(jsr<<5))
#define CONG (jcong=69069*jcong+1234567)
#define FIB ((b=a+b),(a=b-a))
#define KISS ((MWC^CONG)+SHR3)
#define LFIB4 (c++,t[c]=t[c]+t[UC(c+58)]+t[UC(c+119)]+t[UC(c+178)])
#define SWB (c++,bro=(x<y),t[c]=(x=t[UC(c+34)])-(y=t[UC(c+19)]+bro))
#define UNI (KISS*2.328306e-10)
#define VNI ((long) KISS)*4.656613e-10
#define UC (unsigned char) 

typedef unsigned long UL;

/* Global static variables: */
static UL z=362436069, w=521288629, jsr=123456789, jcong=380116160;
static UL a=224466889, b=7584631, t[256];
/* Use random seeds to reset z,w,jsr,jcong,a,b, and the table t[256] 使用随机数种子重置以上数值*/
static UL x=0,y=0,bro; 
static unsigned char c=0;



extern void settable(UL i1,UL i2,UL i3,UL i4,UL i5, UL i6);
extern double exponential(double miu);



