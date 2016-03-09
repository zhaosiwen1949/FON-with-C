#include <stdio.h> 
#include <math.h>
#include <iomanip.h>   //I/O������ͷ�ļ�
#include <fstream>   //#include <fstream.h>Ϊԭ���÷�����vc6���Ѿ����ģ��������д���
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
/* Use random seeds to reset z,w,jsr,jcong,a,b, and the table t[256] ʹ���������������������ֵ*/
static UL x=0,y=0,bro; 
static unsigned char c=0;


/*--------------------------------------produce U(0,1)-������0��1����̬�ֲ�------------------------------*/
void settable(UL i1,UL i2,UL i3,UL i4,UL i5, UL i6)
{ int i; z=i1;w=i2,jsr=i3; jcong=i4; a=i5; b=i6;
  for(i=0;i<256;i=i+1) t[i]=KISS; 
}

/*----------------------------produce exponential distribution-����ָ���ֲ�-xΪ-------------------------------*/
double exponential(int miu)
{   double x;
	x=-(miu*log(1-UNI));
	return x;
}


/*---------------------------------------------�����С��������-----//-������ԤԼʱ���й�--------------------------------*/
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



/*----------------------------produce simulate function----�������溯��---����������ֵpsim-----------------*/
double simulate(double lanmd)   // lanmd Ϊ�����ˣ�lanmta��
{
    double arrivetime[10100],leavetime[10000],psim,*p,*q;
    int i,count,block,miu=8;
    settable(12345,65435,34221,12345,9983651,95746118); 
	arrivetime[0]=0;
    for(i=0;i<10099;i++)
	{
		arrivetime[i+1]=arrivetime[i]-(1/lanmd)*log(UNI);  //����ʱ��������ָ���ֲ��������ű�ʾ�����������ź�
	}        
     settable(12345,65435,34221,12345,9983651,95746118);
    for(i=0;i<10000;i++)
	{
		leavetime[i]=arrivetime[i]+exponential(miu); // �뿪ʱ��=����ʱ��+����ʱ�䣨����ָ���ֲ�������Ϊmiu=8��
	}
	for(i=0;i<1000;i++)
		arrivetime[i]=arrivetime[i+100];// ���100��ҵ�������ͬ�ĵ���ʱ�̣������ҵ��ͬ����ʱ�̣�
        paixu(leavetime,0,9999);
        
		
p=&arrivetime[0];
q=&leavetime[0];
block=0;count=40;
  while(*p!=arrivetime[9999] && *q!=leavetime[9999])
  { if(*p<=*q)   //�������ʱ��TinС�ڷ�����뿪ʱ��Tout�����������æ������֤��һ�����������
  {
	 p++;
	 count=count-1;     //countΪ���񴰿���������ʽ���󱻾ܾ�һ��˵��ѡ�񵽵�ĳ����æ����ɷ��񴰿�����1
	 if(count<0)
		{
			block=block+1;  //���ɷ���Ĵ�����Ϊ0����Ϊ���������޷���Ӧ���������źű�������block��������1
			count=0;  //�÷��񴰿���Ϊ0
		}
	 
  }

		else if(*p>*q) //�������ʱ����ڷ�����뿪��ʱ�䣬�������ǰ���У��۲���һ���������ʱ��
		  {q++;
		     count=count+1; //���еķ��񴰿������ӣ�������1
			 if(count>40)
				 count=40; //���ַ��񴰿�����󲻳���40
		  }
  }
 psim=double(block)/10000;  //�����ĸ��������ܴ���1000�� �������ʣ������ظ�ֵ
 return (psim);
}

/*----------------------------produce theory function---����������ֵ�Ĳ�������---------------------------------------------*/
/*produce jiecheng function �׳����� f!*/
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
/*produce theory function-----------ͨ��-Erlang B��ʽ����������-----�������������ʵ�ֵpr*/   
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
	for(i=0;i<50;i++)   //��a��40Ϊ�����Ϊǿ���� ���з���simulate���������һ����Ӧ��������
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
		 
