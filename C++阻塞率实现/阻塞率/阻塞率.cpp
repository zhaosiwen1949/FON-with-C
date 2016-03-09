#include <stdio.h> 
#include <math.h>
#include <iomanip.h>   //I/O流控制头文件
#include <fstream>   //#include <fstream.h>为原作用法，在vc6中已经更改，用这两行代替
using namespace std;


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


/*---------------------------------------------数组从小到大排序-----//-可能与预约时间有关--------------------------------*/
void paixu(double *a,int i,int j)
{
int m,n;
double k,temp;
m=i;
n=j;
k=a[(i+j)/2];
do 
{
  while(a[m]<k&&m<j) m++; 
  while(a[n]>k&&n>i) n--; 
  if(m<=n) 
  { 
    temp=a[m];
    a[m]=a[n];
    a[n]=temp;
    m++;
    n--;
  }
}while(m<=n);
  if(m<j) paixu(a,m,j); 
  if(n>i) paixu(a,i,n);
}



/*----------------------------produce simulate function----产生仿真函数---返回阻塞率值psim-----------------*/
double simulate(double lanmd)   // lanmd 为参数人（lanmta）
{
    double arrivetime[10100],leavetime[10000],psim,*p,*q;
    int i,count,block,miu=8;
    settable(12345,65435,34221,12345,9983651,95746118); 
	arrivetime[0]=0;
    for(i=0;i<10099;i++)
	{
		arrivetime[i+1]=arrivetime[i]-(1/lanmd)*log(UNI);  //到达时间间隔服从指数分布，数组标号表示到来的请求信号
	}        
     settable(12345,65435,34221,12345,9983651,95746118);
    for(i=0;i<10000;i++)
	{
		leavetime[i]=arrivetime[i]+exponential(miu); // 离开时间=到达时间+服务时间（服从指数分布，参数为miu=8）
	}
	for(i=0;i<1000;i++)
		arrivetime[i]=arrivetime[i+100];// 间隔100个业务具有相同的到达时刻，制造多业务同到达时刻？
        paixu(leavetime,0,9999);
        
		
p=&arrivetime[0];
q=&leavetime[0];
block=0;count=40;
  while(*p!=arrivetime[9999] && *q!=leavetime[9999])
  { if(*p<=*q)   //如果到达时间Tin小于服务后离开时间Tout，则表明服务忙，则验证下一个到达的请求
  {
	 p++;
	 count=count-1;     //count为服务窗口数，因上式请求被拒绝一次说明选择到的某窗口忙，则可服务窗口数减1
	 if(count<0)
		{
			block=block+1;  //当可服务的窗口数为0（即为负），则无法回应服务请求，信号被阻塞，block阻塞数加1
			count=0;  //置服务窗口数为0
		}
	 
  }

		else if(*p>*q) //如果到达时间大于服务后离开的时间，则表明当前空闲，观察下一个服务结束时间
		  {q++;
		     count=count+1; //空闲的服务窗口数增加，计数加1
			 if(count>40)
				 count=40; //保持服务窗口数最大不超过40
		  }
  }
 psim=double(block)/10000;  //阻塞的个数除以总次数1000次 得阻塞率，并返回该值
 return (psim);
}

/*----------------------------produce theory function---理论阻塞率值的产生函数---------------------------------------------*/
/*produce jiecheng function 阶乘运算 f!*/
double jiecheng(int n)
{ 
	double f=1; int i;
    if(n==0||n==1)
	   f=1;
    else 
       for(i=n;i>0;i--)
	   f=f*i;
    return(f);
 }
/*produce theory function-----------通过-Erlang B公式计算阻塞率-----返回理论阻塞率的值pr*/   
double theory(double lanmd)
{
	double a,pr,miu=8,d=0; int k,c=40;
    a=lanmd/miu;
	for (k=0;k<=c;k++)
    d=d+pow(a,k)/jiecheng(k);
	pr=(pow(a,c)/jiecheng(c))/d;     
	return(pr);
}


/*--------------------------------------------main function-------------------------------------------*/
FILE *output;
void main()
{
	int i; double a;
	
	output=fopen("simulate.xls","w");
	a=0;
	for(i=0;i<50;i++)   //以a（40为间隔）为强度人 运行仿真simulate函数，输出一列相应的阻塞率
	{
		a=a+40;
		fprintf(output,"%f\n",simulate(a));
		printf("%f\n",simulate(a));
	}
	printf("\n");
	printf("\n");
	printf("\n");
    fclose(output);  
    
	output=fopen("theory.xls","w");
	a=0;
    for(i=0;i<500;i++)
	{
		a=a+5;
		fprintf(output,"%f\n",theory(a));
		printf("%f\n",theory(a));
	}

}
		 
