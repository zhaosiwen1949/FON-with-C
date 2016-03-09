#include "Channel.h"
#include "Common.h"
using namespace std;

Channel::Channel(void)
{}
Channel::~Channel(void)
{}

//���������ȼ��ϵĺ���
void Channel::paixu(lxd *a,int i,int j)
{
	int m,n;
	lxd k ,temp;
	m=i;
	n=j;
	k=a[(i+j)/2];
	do 
	{
	  while(a[m].length<k.length&&m<j) m++; 
	 while(a[n].length>k.length&&n>i) n--; 
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
//-----------------------------------------------------------------

//��ʼ���ŵ���Ϣ
void Channel::Init()
{
	for(int k=0;k<10;k++)
	{
		L_T[k]=0.0;
	}

}
//��ѯ�Ƿ��п����ŵ��������ŵ����select
//���룺A_T;L_T;wide
//������ŵ���Ѱ��� ��ѡ -1�����ŵ��� 0��1,2�������ȷǸ�ֵ
int Channel::Check(double arrive,double leave,int wide)
{
	lxd *lx;
	lx=( lxd*) calloc(N_LXD,sizeof (lxd)); 
	int left,right,count;//�����ŵ���ż����в�������
	int Select=-1;
	int i,k,l;
	int n=0;
	for(k=0;k<10;k++)  
		nobusy[k]=-1;//��ʼ �޿����ŵ�

   //1.1-----���������ŵ�
	for(k=0;k<10;k++)
	{
		if( L_T[k]<=arrive) 
		{
			nobusy[n]=k;
			n=n+1;
		}
	}
	/*/-------------------------- �����
	printf("\n nobusy[10]:");
	for(n=0;n<10;n++){cout<<" "<<nobusy[n];}
	printf("\n--------------------------------------------------------\n");
	*/
   //-1.2---���ŵ�ѡ�� ����lx[5]-----------------------------------------------------------------------------
	for(l=0;l<5;l++)//��ʼ����head=-1��tail=-1,length=1,flag=0
		lx[l].Init();
	//-1.3-----��ȡ����������lx[]--------------------------------------------------------------
	l=0;
	for(i=0;i<9;i++)
	{
		if( nobusy[i+1]==nobusy[i]+1 )
		{
			if(i!=8)
			{			
				lx[l].flag=1;
				lx[l].tail=nobusy[i+1];
				lx[l].length++;
			}
			if(i==8)
			{			
				lx[l].tail=nobusy[i+1];
				lx[l].length++;
				lx[l].head=lx[l].tail-lx[l].length+1;
				break;
			}
		}
		else
		{
			if(lx[l].flag==1)
			{
				lx[l].tail=nobusy[i];
				lx[l].head=nobusy[i]-lx[l].length+1;
				l++;
			}
		}
	}
/*
	//1.4--------- �����������մ�����С��������---------------------------------------------------------------------------
        cout<<"we have select the free bands of the nobusy[] :"<<endl;
    	cout<<"------head\t tail\t length\t"<<endl;
*/
	count=0;
	for(l=0;lx[l].flag!=0;l++)
	{
	//	cout<<"lx["	<<l<<"]= "<<lx[l].head<<"\t"<<lx[l].tail<<"\t"<<lx[l].length<<endl;
	//   cout<<count<<endl;
				count++;
	}
	paixu(lx,0,count-1);
/*	cout<<"we have rearrange the bands :"<<endl;
	cout<<"------head\t tail\t length\t"<<endl;
	for(l=0;l<count;l++)
	{
		cout<<"lx["	<<l<<"]= "
			<<lx[l].head<<"\t"
			<<lx[l].tail<<"\t"
			<<lx[l].length<<endl;
	}
*/
//--1.5----- ����ָ������Ѱ�Һ��ʿ��д��������Ƿ�ֹ��Ƭԭ�򣬻�ȡ��ѡ�ŵ��ױ��--------------------------------------------------------------------------------------

//	cout<<"the wide is  :"<<wide<<endl;
	for(l=0;l<count;l++)
	{
		if(lx[l].length>wide)
		{
//			cout<<"�ҵ��ϴ���д� :"<<"lx["<<l<<"]"<<endl;
			left=lx[l].head-1;
			right=lx[l].tail+1;
			if(lx[l].head==0)
			{
				Select=0;
			//	cout<<"������������д���ͷ�����Ա�ѡ���ױ���ǣ� "<<Select<<endl;
				break;
			}

			if(lx[l].tail==9 )
			{
				Select=right-wide;
			//	cout<<"������������д���β�����Ա�ѡ���ױ���ǣ� "<<Select<<endl;
				break;
			}
			if(L_T[left]>=L_T[right])
			{
				Select=left+1;
			//	cout<<"��ͨ��������д���ԣ����ѡ������:"<<Select<<endl;
				break;
			}
			else
			{
				Select=right-wide;
			//	cout<<"��ͨ��������д���ԣ����ѡ������:"<<Select<<endl;
			}
			break;
		}//if end
		if(lx[l].length==wide)
		{
		//	cout<<" �ҵ�ǡ������ :"<<"lx["<<l<<"]"<<"�׸���ѡ�ŵ�����ǣ�"<<lx[l].head<<endl;
			Select=lx[l].head;
			break;
		}
		if(l==count-1 && lx[l].length<wide )
		{
		//	cout<<"û�к��ʴ���Ŀ����ŵ�!"<<endl;
			Select=-1;
		}
	}//for end
	free(lx);

	return Select;
//--------------------------------------------------------------------

}//check() end


/*	
//-һ�¶��ǲ�Ҫ�ģ����ӵ�����������-------------------------------------------------------------------------------------------------

   //2----����wide������Ѱ���ҵ����ʴ�С���ŵ���-----------�������2��Select=0 Ҫһ���ŵ�
	int last;
	int w;
	if(wide==1)
	{
		Select=nobusy[0];
		return Select;
	}
	else
	{
		w=1;//��w=1��ʼ��ѡ��1���ŵ�
	    for( n=0;n<10;n++ )
		{
			if(w==wide)
				{
					last=nobusy[n];//�����ŵ������ŵ�������һ���ŵ����
					Select=last-wide+1;//�ŵ��׸����
					return Select;//-----------�������3��Select=ĳ�ŵ�ͷ �������ŵ�
				}
			else
				{
					if(nobusy[n+1]==nobusy[n]+1 ){w++;}				
					else w=1;			
				}
			if(n==9 && w<wide) 
			{
		//	cout<<"we didn't find the enough channels ,sorry~!"<<endl;//δ�ҵ����ʵ�
				Select=-1;
				return Select;//-----------�������4��Select=-1 û�к��ʿ�ȵ��ŵ�
			}		
		}//forѭ������
	return Select;	
	}
*/
