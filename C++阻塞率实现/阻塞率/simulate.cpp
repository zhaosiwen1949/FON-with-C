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