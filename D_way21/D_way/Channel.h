#pragma once


class Channel{
	public:
		Channel(void);
		~Channel(void);
	public:
	    double L_T[1000]; //���ڼ�¼���ŵ���ռ�ý���ʱ��,����10���ŵ�
		int SelectedChannel; //���ѡ����ŵ����
		int nobusy[1000] ; //��ſ����ŵ�˳����

	public:

		void Init(); //��ʼ���ŵ���Ϣ
		int  Check(double arrive,double leave,int Wide);//��ѯ�Ƿ��п����ŵ����������ŵ����Select
		//void Update(int select ,double leave,int wide);//�����ŵ���Ϣ

};