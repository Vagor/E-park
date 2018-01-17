#include "config.h"
/**************************************
这是独立按键的功能函数
每个按键有不同的功能或者是同一个按键在不同界面下
有不同的功能
*****************************************/	 
sbit IOKEY1 = P3^1;	
sbit IOKEY2 = P3^2;	 
sbit IOKEY3 = P3^3; 
sbit IOKEY4 = P1^6;	
sbit IOKEY5 = P3^0; 
sbit IOKEY6 = P1^7;


void keyDelay_1ms(unsigned int i)  //按键消抖延时
{
 	uint x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=20;x++);
}
/********************************************************************
* 名称 : 
* 功能 : 
* 输入 : 无
* 输出 : 无
***********************************************************************/
uchar KeyScan()	
{
	uint count = 0;
	bit SHORTKEY = 0,LONGKEY = 0;

	if(!IOKEY1)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY1)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY1)//如果确认按下按键等待按键释放，没有释放则一直等待
			{			
				count++;
				keyDelay_1ms(2); 
				if(count >= (150*20*5))	//6S 按住超过6S就算是长按，短按抛弃
				{
					LONGKEY=1;
					SHORTKEY=0;
					ClrScreen12864();
					Lcd12864_PutString(1,2,"请松开手");
					break;		
				}
				else 	//不够6S 算是短按
				{
					SHORTKEY=1;
					LONGKEY=0;
				}								
			}
			while(IOKEY1 == 0);//等待放手
			if(LONGKEY==1)
			{
				memset(QBUFF,0,20);
				while(!x24c02ISendByte(CARDNUMADDR,0));
				while(!x24c02ISendStr(QBUFFADDR,QBUFF,8)); 
				while(!x24c02ISendStr(240,&QBUFF[8],8)); 	
				while(!x24c02ISendByte(FIRSTADDR,0));
				Lcd12864_PutString(2,1,"恢复出厂成功");
				Fdelay1ms(1500);
				ClrScreen12864();
				return KEY_NO;	
			}
			else if(SHORTKEY==1) return KEY_1;	
	   	}
	}
	if(!IOKEY2)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY2)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY2);//如果确认按下按键等待按键释放，没有释放则一直等待
			{
				return KEY_2;					
			}
	   	}
	}
	if(!IOKEY3)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY3)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY3);//如果确认按下按键等待按键释放，没有释放则一直等待
			{
				return KEY_3;					
			}
	   	}
	}
	if(!IOKEY4)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY4)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY4);//如果确认按下按键等待按键释放，没有释放则一直等待
			{
				return KEY_4;					
			}
	   	}
	}
	if(!IOKEY5)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY5)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY5);//如果确认按下按键等待按键释放，没有释放则一直等待
			{
				return KEY_5;					
			}
	   	}
	}
	if(!IOKEY6)  //如果检测到低电平，说明按键按下
    {
		keyDelay_1ms(1); //延时去抖，一般10-20ms
     	if(!IOKEY6)     //再次确认按键是否按下，没有按下则退出
	   	{
			while(!IOKEY6);//如果确认按下按键等待按键释放，没有释放则一直等待
			{
				return KEY_6;					
			}
	   	}
	}

	return KEY_NO;
}
/********************************************************************
* 名称 : 
* 功能 : 
* 输入 : 无
* 输出 : 无
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