#pragma once


class Channel{
	public:
		Channel(void);
		~Channel(void);
	public:
	    double L_T[1000]; //用于记录该信道的占用结束时间,共有10个信道
		int SelectedChannel; //存放选择的信道标号
		int nobusy[1000] ; //存放空闲信道顺序标号

	public:

		void Init(); //初始化信道信息
		int  Check(double arrive,double leave,int Wide);//查询是否有可用信道，并返回信道标号Select
		//void Update(int select ,double leave,int wide);//更新信道信息

};