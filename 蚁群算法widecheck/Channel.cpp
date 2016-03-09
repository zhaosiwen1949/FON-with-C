#include "Channel.h"
#include "Common.h"
using namespace std;

Channel::Channel(void)
{}
Channel::~Channel(void)
{}

//排列连续度集合的函数
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

//初始化信道信息
void Channel::Init()
{
	for(int k=0;k<10;k++)
	{
		L_T[k]=0.0;
	}

}
//查询是否有可用信道，返回信道标号select
//输入：A_T;L_T;wide
//输出：信道搜寻标记 可选 -1（无信道） 0，1,2，……等非负值
int Channel::Check(double arrive,double leave,int wide)
{
	lxd *lx;
	lx=( lxd*) calloc(N_LXD,sizeof (lxd)); 
	int left,right,count;//左右信道标号及空闲波段数量
	int Select=-1;
	int i,k,l;
	int n=0;
	for(k=0;k<10;k++)  
		nobusy[k]=-1;//初始 无空闲信道

   //1.1-----挑出空闲信道
	for(k=0;k<10;k++)
	{
		if( L_T[k]<=arrive) 
		{
			nobusy[n]=k;
			n=n+1;
		}
	}
	/*/-------------------------- 检查用
	printf("\n nobusy[10]:");
	for(n=0;n<10;n++){cout<<" "<<nobusy[n];}
	printf("\n--------------------------------------------------------\n");
	*/
   //-1.2---新信道选择法 生成lx[5]-----------------------------------------------------------------------------
	for(l=0;l<5;l++)//初始化，head=-1，tail=-1,length=1,flag=0
		lx[l].Init();
	//-1.3-----获取连续带集合lx[]--------------------------------------------------------------
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
	//1.4--------- 对连续带按照带宽由小到大重排---------------------------------------------------------------------------
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
//--1.5----- 根据指定带宽寻找合适空闲带，并考虑防止碎片原则，获取被选信道首标号--------------------------------------------------------------------------------------

//	cout<<"the wide is  :"<<wide<<endl;
	for(l=0;l<count;l++)
	{
		if(lx[l].length>wide)
		{
//			cout<<"找到较大空闲带 :"<<"lx["<<l<<"]"<<endl;
			left=lx[l].head-1;
			right=lx[l].tail+1;
			if(lx[l].head==0)
			{
				Select=0;
			//	cout<<"特殊情况，空闲带顶头，所以被选带首标号是： "<<Select<<endl;
				break;
			}

			if(lx[l].tail==9 )
			{
				Select=right-wide;
			//	cout<<"特殊情况，空闲带置尾，所以被选带首标号是： "<<Select<<endl;
				break;
			}
			if(L_T[left]>=L_T[right])
			{
				Select=left+1;
			//	cout<<"普通情况，空闲带富裕，被选带靠左:"<<Select<<endl;
				break;
			}
			else
			{
				Select=right-wide;
			//	cout<<"普通情况，空闲带富裕，被选带靠右:"<<Select<<endl;
			}
			break;
		}//if end
		if(lx[l].length==wide)
		{
		//	cout<<" 找到恰当带宽 :"<<"lx["<<l<<"]"<<"首个被选信道标号是："<<lx[l].head<<endl;
			Select=lx[l].head;
			break;
		}
		if(l==count-1 && lx[l].length<wide )
		{
		//	cout<<"没有合适带宽的空闲信道!"<<endl;
			Select=-1;
		}
	}//for end
	free(lx);

	return Select;
//--------------------------------------------------------------------

}//check() end


/*	
//-一下都是不要的，先扔到函数外面了-------------------------------------------------------------------------------------------------

   //2----按照wide需求搜寻，找到合适大小的信道组-----------返回情况2：Select=0 要一条信道
	int last;
	int w;
	if(wide==1)
	{
		Select=nobusy[0];
		return Select;
	}
	else
	{
		w=1;//从w=1开始搜选非1长信道
	    for( n=0;n<10;n++ )
		{
			if(w==wide)
				{
					last=nobusy[n];//符合信道数的信道组合最后一个信道编号
					Select=last-wide+1;//信道首个标号
					return Select;//-----------返回情况3：Select=某信道头 有若干信道
				}
			else
				{
					if(nobusy[n+1]==nobusy[n]+1 ){w++;}				
					else w=1;			
				}
			if(n==9 && w<wide) 
			{
		//	cout<<"we didn't find the enough channels ,sorry~!"<<endl;//未找到合适的
				Select=-1;
				return Select;//-----------返回情况4：Select=-1 没有合适宽度的信道
			}		
		}//for循环结束
	return Select;	
	}
*/
