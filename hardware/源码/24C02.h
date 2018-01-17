#ifndef _24C02_H
#define _24C02_H

void x24c02_write(uchar address, uchar info);
void x24c02_writestring(uchar sla,uchar address, uchar *info,uchar num);
uchar x24c02_read(uchar address);
uchar x24c02_readstring(uchar sla,uchar address, uchar *info,uchar num);
void x24c02_init(void); 

bit x24c02IRcvStr(unsigned char suba,unsigned char *s,unsigned char no);
bit x24c02ISendStr(unsigned char suba,unsigned char *s,unsigned char no);


bit x24c02IRcvByte(unsigned char sla,unsigned char *c);
bit x24c02ISendByte(unsigned char sla,unsigned char c);

#endif