#include "config.h"	//�û���Ҫ��ӵ�ͷ�ļ�
#include <reg52.h>               //51?????????
#define uchar unsigned char     //?????????char??
#define uint unsigned int       //?????????int??



xdata const INT8U KeyABuf[] = { 0x20, 0x12, 0x10, 0x01, 0x00, 0x00 };	 //ע��д�������
xdata const INT8U DefaultKeyABuf[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };	//��ƬĬ�ϵ�A���� Ҳ����ע��ʱд�������
xdata INT8U CardRevBuf[16] = { 0 }; //���������
xdata INT8U const CardKeyABlockBuf[16] = {
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0xff,0x07,0x80,0x69,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
								};
									
xdata uchar QBUFF[20]={0};	 //ȱ��
uchar CBUFF[20]={0};	 //�ٵ�

uchar SYS_STATUS,presystatus=0xff;
uchar xuehaobuff[XUEHAOLEN];
uchar quecount=0,maxcount=0,yecount=0,hang=0;
uchar shangke=0,chicount=0;



/********************************************************************
* ���� : 
* ���� : 
* ���� : ��
* ��� : ��
***********************************************************************/
void Fdelay1ms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	   for(j=0;j<120;j++)
	   ;
}
/********************************************************************
* ���� : 
* ���� : 
* ���� : 
* ��� : 
***********************************************************************/
uchar board_process( void )
{
	if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
	{
		if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
		{
			return NOCARD;
		}	
	}

	if( PcdAnticoll( &CardRevBuf[2] ) != MI_OK ) //����ײ�����ؿ������к� 4�ֽ� 
	{
		return NOCARD;	
	}

	if( PcdSelect( &CardRevBuf[2] ) != MI_OK )//ѡ��
	{
		return NOCARD;
	}

	if( PcdAuthState( PICC_AUTHENT1A, CARDPASSWARD_ADDR, KeyABuf, &CardRevBuf[2] ) != MI_OK )// ��֤����	  
	{
		return NOREG;	 //δע��
	}
	else   
	{
		return HAVEREG;  //��ע��
	}
}
/********************************************************************
* ���� : 
* ���� : 
* ���� : ��
* ��� : ��
***********************************************************************/
INT8U * getcardid( INT8U * SrcBuf)	//������ת�����ַ���
{
	char DisplayBuf[10];
	char *pDisplayChar;
	INT8U Tmp, i;

	pDisplayChar = DisplayBuf;

	for( i = 0; i < 4; i++ )
	{
		Tmp = ( ( *SrcBuf ) >> 4 ) & 0x0F;	
		if( ( Tmp >=0 ) && ( Tmp <= 9 )	)
		{
			*pDisplayChar ++ = '0' + Tmp;	
		}
		else
		{
			*pDisplayChar ++ = 'A' + Tmp - 10;
		}

		Tmp = ( *SrcBuf ) & 0x0F;	
		if( ( Tmp >=0 ) && ( Tmp <= 9 )	)
		{
			*pDisplayChar ++ = '0' + Tmp;	
		}
		else
		{
			*pDisplayChar ++ = 'A' + Tmp - 10;
		}

		SrcBuf ++;
	}
	*pDisplayChar ++ = '\0';

	return DisplayBuf;
	
}
INT32U 	getnum(uchar block)
{
	INT32U cardnum;
	uchar CardReadBuf[16];

	if( PcdRead( block, CardReadBuf ) != MI_OK )// ������
	{
		
	}
	memcpy( ( uchar * )&cardnum, CardReadBuf, 4 ); 
	
	return cardnum;		
}
uchar WriteCardNum()
{
	uchar icstatus;
	uchar SaveNumber;
	uchar CardWriteBuf[16];
	INT32U CardNUM=0;
	INT8U *buff;

	memset( CardWriteBuf, 0, 16 );

	while(!x24c02IRcvByte(CARDNUMADDR,&SaveNumber));
	
	icstatus = board_process();	//��ȡ����״̬

	if(icstatus == HAVEREG)	//��ע��Ŀ�Ƭ
	{				
		SaveNumber++;
		while(!x24c02ISendByte(CARDNUMADDR,SaveNumber));
			
		CardNUM = SaveNumber;
		memcpy( CardWriteBuf, ( INT8U * )&CardNUM, 4 ); 
		if( PcdWrite( CARDNUMBER_ADDR, CardWriteBuf ) != MI_OK )// д����
		{
			return 0;	
		}				
		buff = getcardid(&CardRevBuf[2]);
		memcpy(xuehaobuff,buff,XUEHAOLEN);
		while(!x24c02ISendStr((SaveNumber-1)*XUEHAOLEN,xuehaobuff,XUEHAOLEN));  //д���ŵ�Flash
		return 1;		
	}
	return 0;
}


void sendString(uchar *s)
{
  while(*s != '\0') //???????'\0',???????????
  {
		SBUF = *s;
		while(!TI);
		TI=0;
    s++;
  }
}

//ʹ��Ƭ����115200�Ĳ�����ͨ��
void init_com_115200( void ) //??115200???
{ 
    SCON=0x50; //??????1,8?UART,?????  
    TH2=0xFF;           
    TL2=0xFD;   //???:115200 ??=11.0592MHz 
    RCAP2H=0xFF;   
    RCAP2L=0xFD; //16??????? 
    TCLK=1;   
    RCLK=1;   
    C_T2=0;   
    EXEN2=0; //??????????

    TR2=1 ; //???2??
		Fdelay1ms(2000);
		sendString("AT+RST\r\n");
		Fdelay1ms(10000);
		sendString("AT+CIPSTART=\"TCP\",\"192.168.137.167\",4001\r\n");
	
} 

void main(void)
{
							uchar str[20];
	uchar num;
	uchar icstatus;
	INT32U readiiccardnum;
	uchar usercount;

	LEDRED = LEDOFF;
	LEDGREEN = LEDON;
	BEEP = BEEPOFF;

	Lcd12864_Init();	//Һ����ʼ��
	ClrScreen12864();	//����

	SYS_STATUS = SYSNORMAL;

	memset(CBUFF,1,20);	//void *memset(void *s,int c,size_t n)���ѿ����ڴ�ռ� s ���� n ���ֽڵ�ֵ��Ϊֵ c��
	                    //CBUFF���������Ԫ��ֵĬ��Ϊ1����ʾ�ǳٵ�

	init_rc522(); //ˢ��ģ���ʼ��
	init_com_115200(); //ʹ��Ƭ����115200�Ĳ�����ͨ��

	while(!x24c02IRcvByte(FIRSTADDR,&usercount));
	if(usercount == 9)
	{
		while(!x24c02IRcvStr(QBUFFADDR,QBUFF,8));
		while(!x24c02IRcvStr(240,&QBUFF[8],8));		
	}
	else 
	{
		while(!x24c02ISendStr(QBUFFADDR,QBUFF,8)); 
		while(!x24c02ISendStr(240,&QBUFF[8],8)); 		 
	}
	while(1)
		{
			ClrScreen12864();
			Lcd12864_PutString( 1, 2, "��λ��A01");
			icstatus = board_process(); //��ȡ����״̬
			switch(icstatus)
				{
				case NOREG:
				Fdelay1ms(500);
				if(updata_key(0)==1) 
					{
						Lcd12864_PutString( 2, 1, "  ͣ���ɹ�  ");
						Lcd12864_PutString(3, 2, getcardid(&CardRevBuf[2]) ); //��ʾ����
						sendString("AT+CIPSEND=8\r\n");
						Fdelay1ms(3000);
						sendString(getcardid(&CardRevBuf[2]));
						Fdelay1ms(300);
						LEDRED = LEDON;
						LEDGREEN = LEDOFF;
						BEEP = BEEPOFF;	
					}
					Fdelay1ms(3000);
					break;
				
				case HAVEREG:
				while(!x24c02IRcvByte(CARDNUMADDR,&num)); //��ȡע��Ŀ����� Ҳ����������
				hang=0;
				icstatus = board_process();			
				Fdelay1ms(500);
				if(updata_key(1)==1)
					{
						LEDRED = LEDOFF;
						LEDGREEN = LEDON;
						BEEP = BEEPOFF;		
						Lcd12864_PutString( 2, 1, "  �뿪�ɹ�  ");	
						Lcd12864_PutString(3, 2, getcardid(&CardRevBuf[2]) ); //��ʾ����
						sendString("AT+CIPSEND=8\r\n");
						Fdelay1ms(3000);
						sendString(getcardid(&CardRevBuf[2]));
						Fdelay1ms(300);
						readiiccardnum = getnum(CARDNUMBER_ADDR); //��ȡ�ÿ���Ӧ����ֵ����һ�ſ�����1���ڶ��ſ�����2���Դ�����
						while(!x24c02ISendByte(FIRSTADDR,9));
						QBUFF[readiiccardnum-1] = 1;
						while(!x24c02ISendByte(QBUFFADDR+readiiccardnum-1,1));
						if(readiiccardnum >= 8)
							{
								//while(!x24c02IRcvStr(240,&QBUFF[8],8));
								}
							else
								{						
						//while(!x24c02IRcvStr(QBUFFADDR,QBUFF,8));
									}
					}
					Fdelay1ms(3000);
					break;
				}
		}
}
