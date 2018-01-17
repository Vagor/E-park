#ifndef _DISPLAY_H
#define _DISPLAY_H



extern void display_no_id( void );

extern void display_reg( uchar *idbuf );	//ÓÐ¿¨ ×¢²á

extern void display_no_reg( uchar *idbuf );

extern void dis_delay(uchar status);

extern void dis_addmode();
extern void dis_conmode();

#endif

