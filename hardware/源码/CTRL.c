
/************************************************
����ļ��ĺ�������ע���ע���ĺ���
��ִ��ע������ע���ʱ�򣬵�Ƭ���ͻ�����������������ͬ��ֵ�ж���ע�ỹ��ע����
��ע���ʱ��Ƭ���ͽ���ǰ��Ƭ��A��������ĳ�0x20, 0x12, 0x10, 0x01, 0x00, 0x00��
��ע����ʱ��Ƭ���ͽ���ǰ��Ƭ��A��������ĳ�0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF��
��Ƭ������ͨ����ȡ���A�����������жϿ�Ƭ��ע����Ļ���û��ע����ġ�
************************************************/

#include "config.h"


extern const INT8U KeyABuf[];	 //ע��д�������
extern const INT8U DefaultKeyABuf[];
extern INT8U const CardKeyABlockBuf[16];
/********************************************************************
* ���� : 
* ���� : 
* ���� : ��
* ��� : ��
***********************************************************************/
uchar updata_key(uchar res)	 //���Ŀ�Ƭ����
{
	uchar CardKeyABuf[6]; //������ID��
	uchar CardKeyABufNew[6];	//ע��ǰID��
	uchar CardKeyABufMatch[6]; //Ĭ�ϵ�ID��

	if(res)	 //ע��
	{
		memcpy( CardKeyABufNew, &DefaultKeyABuf[0], 6 );
		memcpy( CardKeyABufMatch, &KeyABuf[0], 6 );
	}
	else  //ע��
	{
		memcpy( CardKeyABufNew, &KeyABuf[0], 6 );
		memcpy( CardKeyABufMatch, &DefaultKeyABuf[0], 6 );
	}
	
	if( PcdRequest( PICC_REQIDL, &CardKeyABuf[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
	{  
		if( PcdRequest( PICC_REQIDL, &CardKeyABuf[0] ) != MI_OK )
		{
			return FALSE;
		}
	}
	if( PcdAnticoll( &CardKeyABuf[2] ) != MI_OK ) //����ײ�����ؿ������к� 4�ֽ� 
	{
		return FALSE;	
	}

	if( PcdSelect( &CardKeyABuf[2] ) != MI_OK )//ѡ��
	{
		return FALSE;
	}

	if( PcdAuthState( PICC_AUTHENT1A, CARDPASSWARD_ADDR, CardKeyABufMatch, &CardKeyABuf[2] ) != MI_OK )// ��֤����
	{
		return FALSE;	
	}

	memcpy( CardKeyABlockBuf, &CardKeyABufNew[0], 6 );

	if( PcdWrite( CARDPASSWARD_ADDR, CardKeyABlockBuf ) != MI_OK )// д��
	{
		return FALSE;
	}
	return TRUE;
}


