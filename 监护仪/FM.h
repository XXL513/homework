#ifndef _FM_H_
#define _FM_H_

//-----包含头文件-----//
#include "STC8A.h"
#include "I2C.h"

//---重定义关键词---//
#ifndef max_freq
#define max_freq 108000
#endif


#ifndef min_freq
#define min_freq 87500
#endif

//---定义全局函数---//


//---加入全局变量--//
extern unsigned int max_pll;           //108MHz时的pll,
extern unsigned int min_pll;           //87.5MHz时的pll.

extern unsigned char radio_write_data[5];        //要写入TEA5767的数据
extern unsigned char radio_read_data[5];        //TEA5767读出的状态

extern unsigned long frequency;
extern unsigned int pll;
//---定义全局函数---//
void radio_write(void);  //写入radio_write_data[]
void get_pll(void);  //由频率计算PLL
void get_frequency(void);  //由PLL计算频率
void radio_read(void);   //读TEA5767状态,并转换成频率
void search(bit mode);  //手动设置频率,mode=1,+0.01MHz; mode=0:-0.01MHz ,不用考虑TEA5767用于搜台的相关位:SM,SUD
void auto_search(bit mode);   //自动搜台,mode=1,频率增加搜台; mode=0:频率减小搜台,不过这个好像不能循环搜台


#endif