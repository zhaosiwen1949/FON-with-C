#include "Channel.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

//
//50 channels wide={1,4,10,20}  client=1000 miu=0.2 lamd={0~}



Channel::Channel(void)
{
}

Channel::~Channel(void)
{
}
//初始化信道信息
void Channel::Init()
{
	for(int k=0;k<N_CHNL;k++)
	{
		L_T[k]=0.0;
	}
}
//查询是否有可用信道，返回信道标号select
//输入：A_T;L_T;wide
//输出：信道搜寻标记 可选 -1（无信道） 0，1,2，……等非负值
int Channel::Check(double arrive,double leave,int wide)
{
	
	int Select=-1;
	int k,w;
	int n=0;
	int last;//返回最后的信道标号
	for(k=0;k<N_CHNL;k++)  
		nobusy[k]=-1;//初始 无空闲信道

   //1.1-----挑出空闲信道
	for(k=0;k<N_CHNL;k++)
	{
		if(L_T[k]<=arrive) 
		{
			nobusy[n]=k;
			n=n+1;
		}
	}
	//-------------------------- 检查用
//	printf("\n nobusy:\n");

//	for(k=0;k<1000;k++)
//	{
//		printf("%d\t",nobusy[k]);
//	}
//-----------------------------------------

   //2----按照wide需求搜寻，找到合适大小的信道组-----------返回情况2：Select=0 要一条信道
		
	if(wide==1)
	{
		Select=nobusy[0];
		return Select;
	}
	else
	{
		w=1;//从w=1开始搜选非1长信道
	    for( n=0;n<N_CHNL-1;n++ )
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
			if(n==N_CHNL-2 && w<wide) 
			{
			//	cout<<"we didn't find the enough channels ,sorry~!"<<endl;未找到合适的
				Select=-1;
				return Select;//-----------返回情况4：Select=-1 没有合适宽度的信道
			}		
		}//for循环结束
	return Select;	
	}
}