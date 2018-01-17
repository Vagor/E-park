
/************************************************
这个文件的函数就是注册和注销的函数
当执行注销或者注册的时候，单片机就会调用这个函数，传不同的值判断是注册还是注销。
当注册的时候单片机就将当前卡片的A区的密码改成0x20, 0x12, 0x10, 0x01, 0x00, 0x00，
当注销的时候单片机就将当前卡片的A区的密码改成0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF，
单片机就是通过读取这个A区的密码来判断卡片是注册过的还是没有注册过的。
************************************************/

#include "config.h"


extern const INT8U KeyABuf[];	 //注册写入的密码
extern const INT8U DefaultKeyABuf[];
extern INT8U const CardKeyABlockBuf[16];
/********************************************************************
* 名称 : 
* 功能 : 
* 输入 : 无
* 输出 : 无
***********************************************************************/
uchar updata_key(uchar res)	 //更改卡片密码
{
	uchar CardKeyABuf[6]; //读到的ID号
	uchar CardKeyABufNew[6];	//注销前ID号
	uchar CardKeyABufMatch[6]; //默认的ID号

	if(res)	 //注销
	{
		memcpy( CardKeyABufNew, &DefaultKeyABuf[0], 6 );
		memcpy( CardKeyABufMatch, &KeyABuf[0], 6 );
	}
	else  //注册
	{
		memcpy( CardKeyABufNew, &KeyABuf[0], 6 );
		memcpy( CardKeyABufMatch, &DefaultKeyABuf[0], 6 );
	}
	
	if( PcdRequest( PICC_REQIDL, &CardKeyABuf[0] ) != MI_OK )//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节	
	{  
		if( PcdRequest( PICC_REQIDL, &CardKeyABuf[0] ) != MI_OK )
		{
			return FALSE;
		}
	}
	if( PcdAnticoll( &CardKeyABuf[2] ) != MI_OK ) //防冲撞，返回卡的序列号 4字节 
	{
		return FALSE;	
	}

	if( PcdSelect( &CardKeyABuf[2] ) != MI_OK )//选卡
	{
		return FALSE;
	}

	if( PcdAuthState( PICC_AUTHENT1A, CARDPASSWARD_ADDR, CardKeyABufMatch, &CardKeyABuf[2] ) != MI_OK )// 验证密码
	{
		return FALSE;	
	}

	memcpy( CardKeyABlockBuf, &CardKeyABufNew[0], 6 );

	if( PcdWrite( CARDPASSWARD_ADDR, CardKeyABlockBuf ) != MI_OK )// 写卡
	{
		return FALSE;
	}
	return TRUE;
}


