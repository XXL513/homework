#ifndef __KEY_H_
#define __KEY_H_

#include "STC8A.h"

//------定义使用的IO口-----//
sbit state_default = P2^0;
sbit state_FM = P2^1;
sbit state_SD = P2^2;
sbit state_AN = P2^3;   //模式按键
sbit state_GPRS = P2^4; 

sbit UP = P6^0;   //向上
sbit DOWN = P6^1;  //向下
sbit START = P7^2;  //播放/确定键

sbit time_renew = P6^5; //按键更新时间

//------定义全局函数------//
unsigned char Key_return();  //单刀开关返回值


#endif