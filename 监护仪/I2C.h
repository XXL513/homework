#ifndef __I2C_H_
#define __I2C_H_

#include "STC8A.h"

//------定义使用的IO口-----//
sbit SDA=P1^4;
sbit SCL=P1^5;

//------定义全局函数------//
void Delayus(unsigned int number);
void DelayMs(unsigned int number);
void iic_start();
void iic_stop();
void iic_ack();
void iic_NoAck();
bit iic_testack();
void iic_write8bit(unsigned char input);
unsigned char iic_read8bit();


#endif