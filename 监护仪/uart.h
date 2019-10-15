#ifndef _UART_H_
#define _UART_H_
//-----包含头文件-----//
#include "STC8A.h"
#include "GPS.h"
#include "light.h"
#include "BLUE.h"
#include "SD.h"

//-----定义全局函数---//
void set_baudrate(float frequency,long int baudrate);
void TxByte(unsigned char dat);
void UartSendStr(unsigned char *p);

//-----定义全局变量----//
extern unsigned char uart_state;  //串口使用状态,1、2、3、4

extern unsigned char	flag;  //标志位
extern unsigned char	seg_count;  //逗号计数器
extern unsigned char	byte_count;  //内部位数计数器
extern bit receive_ok;
#endif