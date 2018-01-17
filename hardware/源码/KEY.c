#include "config.h"
/**************************************
���Ƕ��������Ĺ��ܺ���
ÿ�������в�ͬ�Ĺ��ܻ�����ͬһ�������ڲ�ͬ������
�в�ͬ�Ĺ���
*****************************************/	 
sbit IOKEY1 = P3^1;	
sbit IOKEY2 = P3^2;	 
sbit IOKEY3 = P3^3; 
sbit IOKEY4 = P1^6;	
sbit IOKEY5 = P3^0; 
sbit IOKEY6 = P1^7;


void keyDelay_1ms(unsigned int i)  //����������ʱ
{
 	uint x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=20;x++);
}
/********************************************************************
* ���� : 
* ���� : 
* ���� : ��
* ��� : ��
***********************************************************************/
uchar KeyScan()	
{
	uint count = 0;
	bit SHORTKEY = 0,LONGKEY = 0;

	if(!IOKEY1)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY1)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY1)//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{			
				count++;
				keyDelay_1ms(2); 
				if(count >= (150*20*5))	//6S ��ס����6S�����ǳ������̰�����
				{
					LONGKEY=1;
					SHORTKEY=0;
					ClrScreen12864();
					Lcd12864_PutString(1,2,"���ɿ���");
					break;		
				}
				else 	//����6S ���Ƕ̰�
				{
					SHORTKEY=1;
					LONGKEY=0;
				}								
			}
			while(IOKEY1 == 0);//�ȴ�����
			if(LONGKEY==1)
			{
				memset(QBUFF,0,20);
				while(!x24c02ISendByte(CARDNUMADDR,0));
				while(!x24c02ISendStr(QBUFFADDR,QBUFF,8)); 
				while(!x24c02ISendStr(240,&QBUFF[8],8)); 	
				while(!x24c02ISendByte(FIRSTADDR,0));
				Lcd12864_PutString(2,1,"�ָ������ɹ�");
				Fdelay1ms(1500);
				ClrScreen12864();
				return KEY_NO;	
			}
			else if(SHORTKEY==1) return KEY_1;	
	   	}
	}
	if(!IOKEY2)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY2)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY2);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				return KEY_2;					
			}
	   	}
	}
	if(!IOKEY3)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY3)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY3);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				return KEY_3;					
			}
	   	}
	}
	if(!IOKEY4)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY4)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY4);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				return KEY_4;					
			}
	   	}
	}
	if(!IOKEY5)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY5)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY5);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				return KEY_5;					
			}
	   	}
	}
	if(!IOKEY6)  //�����⵽�͵�ƽ��˵����������
    {
		keyDelay_1ms(1); //��ʱȥ����һ��10-20ms
     	if(!IOKEY6)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	   	{
			while(!IOKEY6);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				return KEY_6;					
			}
	   	}
	}

	return KEY_NO;
}
/********************************************************************
* ���� : 
* ���� : 
* ���� : ��
* ��� : ��
***********************************************************************/
uchar KeyPro(void)
{
	switch(KeyScan())
	{
		case KEY_1:return KEY_A;break;//
		case KEY_2:return KEY_B;break;//
		case KEY_3:return KEY_C;break;//
		case KEY_4:return KEY_D;break;//
		case KEY_5:return KEY_SO;break;//
		case KEY_6:return KEY_MI;break;//
		default:return KEY_NO;break;
	}
}