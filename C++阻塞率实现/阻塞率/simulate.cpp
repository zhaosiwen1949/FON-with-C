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