#ifndef _UART_H_
#define _UART_H_
//-----����ͷ�ļ�-----//
#include "STC8A.h"
#include "GPS.h"
#include "light.h"
#include "BLUE.h"
#include "SD.h"

//-----����ȫ�ֺ���---//
void set_baudrate(float frequency,long int baudrate);
void TxByte(unsigned char dat);
void UartSendStr(unsigned char *p);

//-----����ȫ�ֱ���----//
extern unsigned char uart_state;  //����ʹ��״̬,1��2��3��4

extern unsigned char	flag;  //��־λ
extern unsigned char	seg_count;  //���ż�����
extern unsigned char	byte_count;  //�ڲ�λ��������
extern bit receive_ok;
#endif