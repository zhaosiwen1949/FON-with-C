//C����ʵ��PoiSSON�ֲ�����ֵΪ0.2
#include <stdio.h>
#include <math.h>
#define n (pow(2,31)-1)//x��Y����
void u(double m,double b[5000])        //�������ȷֲ�
{   
    int i;
	double z[5000];
	z[0]=m;
	for(i=1;i<5000;i++)
	{    z[i]=fmod((16807*z[i-1]),n);//����x/y��������
	     b[i]=z[i]/n;	
	}	 
	b[0]=m/n;
}
void main()
{
	double a;
	double b;
	double c[5000];
	int d[5000];
	int i,j;
	int k=0;
	a=exp(-0.2);
	FILE *fp;
	fp=fopen("p.txt","w");
	for(i=1;i<5001;i++)                  
	{   b=1;
        u(i*123456789000,c);            //�����Ӻ���
		for(j=0;j<5000;j++)
		{b=b*c[j];
		 if(b<a) 
		 {d[k++]=j;                      //����poisson 
		 break;}
		}
	}
    for(i=0;i<5000;i++)
	{
		printf("%d\n",d[i]);
		fprintf(fp,"%d\n",d[i]);
	}
	fclose(fp);
}