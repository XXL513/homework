#ifndef __GPS_H_
#define __GPS_H_

//---包含头文件---//
#include "STC8A.h"


//---加入全局变量--//
extern unsigned char JD[10];  //经度
extern unsigned char JD_a;    //经度方向
extern unsigned char WD[9];   //纬度
extern unsigned char WD_a;    //纬度方向
extern unsigned char lock;    //定位状态

#endif