#ifndef	_CONFIG_H_
#define	_CONFIG_H_

#include <reg52.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#include "def.h"

//用户手动添加所需的头文件 
#include "LCD12864.h"
#include "KEY.h"
#include "RC522.h"
#include "CTRL.h"
#include "24C02.h"

sbit LEDRED = P3^5;
sbit LEDGREEN = P3^6;
sbit BEEP = P3^7;

#define LEDON 0
#define LEDOFF 1

#define BEEPOFF 1
#define BEEPON 0

#define NOCARD 0 //无卡
#define NOREG 1	 //未注册
#define HAVEREG 2	 //注册
#define XUEHAOLEN  8  //卡号长度


#define CARDNUMADDR  250	  //IC卡NUM地址

#define QBUFFADDR 232

#define FIRSTADDR 220

#define XUEHAOLEN  8  


#define SYSNORMAL 1
#define ZHUCE 2
#define QIANDAO 3  
#define ZHUXIAO 4
#define QUEQING 5
#define CHIDAO 6

extern uchar Input_pw();
extern void Fdelay1ms(unsigned int t);
extern xdata uchar QBUFF[20];	 //缺勤
extern uchar CBUFF[20];	 //迟到


#endif