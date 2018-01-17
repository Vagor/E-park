
/************************************************
这个文件是液晶LCD12864的驱动函数，采用的是串行接法
这个文件的函数大家都是可以通用的，就是液晶的驱动函数。
所以你可以不必看懂这个文件的函数，当然如果你想自己看懂的话，你可能得借助百度了，
************************************************/

#include "config.h"	


sbit SID=P2^4;//rw		//数据信号
sbit SCLK=P2^5;//en		//时钟信号


/********************************************************************
* 名称 : delay()
* 功能 : 延时,延时时间为 100us * t。这是通过软件延时，有一定误差。
* 输入 : t
* 输出 : 无
***********************************************************************/
void delay(unsigned int t)
{
	unsigned int i,j;
	for(i=0; i<t;  i++)
    for(j=0; j<3; j++);
}
/********************************************************************
* 名称 : sendbyte()
* 功能 : 按照液晶的串口通信协议，发送数据
* 输入 : zdata
* 输出 : 无
***********************************************************************/
void Lsendbyte(unsigned char zdata)
{
	unsigned int i;
	for(i=0; i<8; i++)
	{
		if((zdata << i) & 0x80)
		{
			SID = 1;
		}
		else 
		{
			SID = 0;
		}
		SCLK = 0;
		SCLK = 1;
	}
}
/********************************************************************
* 名称 : write_com()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void v_Lcd12864SendCmd_f(unsigned char cmdcode)
{
	Lsendbyte(0xf8);
	Lsendbyte(cmdcode & 0xf0);
	Lsendbyte((cmdcode << 4) & 0xf0);
	delay(2);
}
/********************************************************************
* 名称 : write_data()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void v_Lcd12864SendData_f(unsigned char Dispdata)
{
	Lsendbyte(0xfa);
	Lsendbyte(Dispdata & 0xf0);
	Lsendbyte((Dispdata << 4) & 0xf0);
	delay(2);
}
/********************************************************************
* 名称 : lcdinit()
* 功能 : 初始化函数
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void Lcd12864_Init()
{  
	delay(2000);
	v_Lcd12864SendCmd_f(0x30);
	delay(50);
	v_Lcd12864SendCmd_f(0x0c);
	delay(50);
}
/********************************************************************
* 名称 : 
* 功能 : 
* 输入 : 无
* 输出 : 无
***********************************************************************/
void v_Lcd12864SetAddress_f( unsigned char x, y )  //地址转换
{
    unsigned char byAddress ;
    switch( x )
    {
        case 0 :    byAddress = 0x80 + y ;
            break;
        case 1 :    byAddress = 0x90 + y ;
            break ;
        case 2 :    byAddress = 0x88 + y ;
            break ;
        case 3 :    byAddress = 0x98 + y ;
            break ;
        default :
            break ;
    }
    v_Lcd12864SendCmd_f( byAddress ) ;
}
/*******************************************************
y为距离最左边位置
x为第几行
******************************************************/
//void Lcd12864_PutChar( unsigned char x, unsigned char y, unsigned char pData )
//{
//    v_Lcd12864SetAddress_f( x, y ) ;
//    {
//        v_Lcd12864SendData_f( pData ) ;
//    }
//}
/*******************************************************
y为距离最左边位置
x为第几行
******************************************************/
void Lcd12864_PutString( unsigned char x, unsigned char y, unsigned char *pData )
{
    v_Lcd12864SetAddress_f( x, y ) ;
    while( *pData != '\0' )
    {
        v_Lcd12864SendData_f( *pData++ ) ;
//		delay(30);
    }
}
/********************************************************************
* 名称 : ClrScreen12864()
* 功能 : 
* 输入 : 
* 输出 : 
***********************************************************************/
void ClrScreen12864()
{ 
   v_Lcd12864SendCmd_f(0x01);
   delay(15);
}
