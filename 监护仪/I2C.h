#ifndef __I2C_H_
#define __I2C_H_

#include "STC8A.h"

//------����ʹ�õ�IO��-----//
sbit SDA=P1^4;
sbit SCL=P1^5;

//------����ȫ�ֺ���------//
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