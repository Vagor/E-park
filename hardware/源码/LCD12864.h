#ifndef	_LCD12864_H_
#define	_LCD12864_H_

void Lcd12864_Init( void );
void Lcd12864_PutString( unsigned char x, unsigned char y, unsigned char *pData );
void Lcd12864_PutChar( unsigned char x, unsigned char y, unsigned char pData );


void v_Lcd12864SendCmd_f( unsigned char byCmd )  ;    //��������
void v_Lcd12864SendData_f( unsigned char byData ) ;   //��������

void ClrScreen12864();








#endif