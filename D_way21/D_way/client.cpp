#include "client.h"
#include "common.h"

client::client(void)
{
}

client::~client(void)
{
}

void client::Init()
{
	int wide[4]={1,4,10,20};
	//printf("*****************************\n");
	//������������������б��
//	start_city=rnd(0,14);
	start_city=rnd(0,21);
//	start_city=1;
//	printf("the start city number is : %d\n",start_city);
//	dest_city=rnd(0,14);
	dest_city=rnd(0,21);
//	dest_city=12;
//	printf("the dest city number is : %d\n",dest_city);
	//����ŵ�������Ŀ
	int a=rnd(0,4);
	Wide=wide[a];
//	Wide=2;
//	printf("the channel wide  is : %d\n",Wide);


}


int client::Search()
{
	int flag;

	D_try.A_T=A_T;
	D_try.L_T=L_T;
	D_try.Wide=Wide;
	//�������·���㷨���ҵ����������·��
//	D_try.Search_way(14, start_city,cost);
//	flag=D_try.Show_way(14,start_city,dest_city);
	D_try.Search_way(21, start_city,cost);
	flag=D_try.Show_way(21,start_city,dest_city);

//	flag=D_try.block;
	return flag;
}