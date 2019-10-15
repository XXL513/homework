#ifndef __KEY_H_
#define __KEY_H_

#include "STC8A.h"

//------����ʹ�õ�IO��-----//
sbit state_default = P2^0;
sbit state_FM = P2^1;
sbit state_SD = P2^2;
sbit state_AN = P2^3;   //ģʽ����
sbit state_GPRS = P2^4; 

sbit UP = P6^0;   //����
sbit DOWN = P6^1;  //����
sbit START = P7^2;  //����/ȷ����

sbit time_renew = P6^5; //��������ʱ��

//------����ȫ�ֺ���------//
unsigned char Key_return();  //�������ط���ֵ


#endif