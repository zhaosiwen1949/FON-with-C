
#include "D_search.h"



D_search::D_search(void)
{
}

D_search::~D_search(void)
{
}
void D_search::Init()
{
	for(int i=0;i<N_CITY;i++)
	way_link[i]=21;//����ν��ѡ��һ��ȡ������ֵ�Ϳ�����

}


void D_search::Search_way(int n,int start,int cost[N_CITY][N_CITY])
{
	int i,j;
	int s[N_CITY];//����������·���Ľڵ��Ӽ�s
	//��ʼ����С·�����ۺ�ǰһ���ڵ�ֵ------------------------------------------//
	for (i = 0; i < n; i++)
	{
		dist[i] = cost[start][i];//Wi=d_vj ��ȡԴ�ڵ㵽�����ڵ��Ȩֵ����
		s[i] = 0; //�������·����{GP} �Ӽ�����Ϊ��
		if (dist[i] == maxint)  //���i��Vs �ľ���Ϊ��������� �趨������ǰһ�ڵ�Ϊ0��
		{
			prev[i] = 0;
		}
		else      //���i��Vs�ľ��벻Ϊ��������ڣ������ǽ�������VS��������·���Ƚϵĵ㣬�趨���ǵ�ǰһ�ڵ�ΪV��
		{
			prev[i] = start;
		}
	}
	dist[start] = 0;//�趨start��start�ľ���Ϊ0
	s[start] = 1;//���·�ɵ��Ӽ�GP����һ��Ԫ���ˣ����Ǹտ�ʼ��Դ�ڵ�start
  //-------------------------------------------------------------------------------//

	for (i = 0; i < n; i++)
	{
		int temp = maxint;
		int u = start;
		//���������С���۵��ھӽڵ㵽s�Ӽ�
		for (j = 0; j < n; j++)
		{
			if ((!s[j]) && (dist[j] < temp)) //���j�㲻��{GP}�ڣ���start�㵽j��ľ��벻Ϊ����
			{
				u = j;    //����u==j������temp��ֵ�滻Ϊvs��j �ľ��룬��������VS���ڵ�j�㾭������Ƚ�������̵ĸ�u
				temp = dist[j];
			}
		}
		s[u] = 1;//���������ѭ��ѡ����һ�����·���ĵ㣬������д���Ӽ�GP
		//��������µĽڵ�󣬸���·��ʹ��������������**********************
		for (j = 0; j < n; j++)//����һ��ѡ����U�㿪ʼѰ����һ�����Ȩֵ�ĵ�
		{
			if ((!s[j]) && (cost[u][j] < maxint))
			{
				int newdist = dist[u] + cost[u][j];//u��Vs�ľ���+u��j��Ȩֵ
				if (newdist < dist[j])//�����ʽ����С��Vs��j�ľ��룬�������·��Ȩֵ�滻ԭ��VS��j �ľ���
				{
					dist[j] = newdist;
					prev[j] = u;// ������j���ǰһ����Ϊu��
				}
			}
		}
	}
}

//��������ŵ����У���¼��ѡ·������¼block
int D_search::Show_way(int n,int start,int dest)
{

	int j = 0;
	int w = dest;
	int count = 0;
	int block=0;
	int check_first;
	int check_way;

	//����·��
	way[0]=dest;
	while (w != start)
	{
		count++;
		way[count] = prev[w];
		w = prev[w];
	}

	//--------------------�����
	//printf("we select the best path ======\n");

	//	for (j = count; j >= 1; j--)
	//	{
			//printf("%d - ->",way[j]);
	//	}

	//	printf("%d\n",dest);
    //
	//-------------------------

	//A ���--�����˲�������Ҳһ���Ե�������
	check_first=Check_way(count);
	if(check_first==-1)
	{
		block=1;
	//	printf("the first hit is stuck \n");
		return block;
	}
	else
	{

		for (j = count-1; j >= 1; j--)
		{
			check_way=Check_way(j);
			if(check_way!=check_first)
			{
				//printf("������һ�� block ++ \n");
				block=1;
				return block;			
			}
			else
			{

				printf("����һ��\n");
			
			}

		}
	C_arrange(count);


	}

//---------------------------------------
//B ���--�����ǲ���һ���Ե����
/*
	for (j = count; j >= 1; j--)
		{
			check_way=Check_way(j);
			if(check_way==-1)
			{
				//printf("we didn't find free channel between the %d and %d channnel! block ++ \n",j,j-1);
				block=1;
				break;
			}
		}
	if(block!=-1)
		C_arrange(count);
	*/

	return block;


}
//���ڼ���ŵ��Ƿ����~
// return ֵΪ-1����ʾѰ�ŵ�ʧ�ܣ� return ֵΪselect����ʾ�ŵ��У����Ѿ���Ǻ���j->j-1·��ѡ�����ŵ��ױ��
int D_search::Check_way(int num)
{
	int select;
	int fail_flag;
	int m=way[num];
	int n=way[num-1];
	//��ȡ��ѡ�ŵ����׸����
	select=Public_channel[m][n].Check(A_T,L_T, Wide);
		if(select==-1)
		{
			fail_flag=-1;//û�п����ŵ�
		}
		else 
		{
			way_link[num]=select;
			fail_flag=select;		
		}
	
	return fail_flag;

}
//�����ŵ�����
void D_search::C_arrange(int count)
{
	int m,n;
	int j,k;
//	int top;
		for (j = count; j >= 1; j--)
		{
			n=way[j];
			m=way[j-1];
			k=way_link[j];
	//		printf("%d ===(%d)==>",n,k);
			if(Wide==1)
			{				
				//printf("\n���³���Ϊ1���ŵ�ռ��");
				//printf("\n--------------------------\n");

				Public_channel[n][m].L_T[k]=L_T;
				Public_channel[m][n]=Public_channel[n][m];
			}
			if(Wide==4)
			{
				for(int w=0;w<3;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				}
				Public_channel[m][n]=Public_channel[n][m];	
			}
			if(Wide==10)
			{
				for(int w=0;w<9;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				}
				Public_channel[m][n]=Public_channel[n][m];

			}

			if(Wide==20)
			{
				for(int w=0;w<19;w++)
				{
					Public_channel[n][m].L_T[k+w]=L_T;
				//	printf("\n ���³���Ϊ20���ŵ�ռ��");
				}
				Public_channel[m][n]=Public_channel[n][m];			
				//printf("\n--------------------------\n");

			}
		}

}
























