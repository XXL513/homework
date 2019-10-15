#include "I2C.h"

void Delayus(unsigned int number)
{
 while(number--);
}

void DelayMs(unsigned int number)
{
 unsigned char temp;
 for(;number!=0;number--)
 {
  for(temp=112;temp!=0;temp--);
  {}
 }
}
/*************************************************************************
*��������iic_start
*�������ܣ�ģ�⿪ʼʱ��
*************************************************************************/
void iic_start()
{
 SDA=1;
 Delayus(4);
 SCL=1;
 Delayus(4);
 SDA=0;
 Delayus(4);
 SCL=0;
 Delayus(4);
}
/*************************************************************************
*��������iic_stop
*�������ܣ�ģ�����ʱ��
*************************************************************************/
void iic_stop()
{
 SCL=0;
 Delayus(4);
 SDA=0;
 Delayus(4);
 SCL=1;
 Delayus(4);
 SDA=1;
 Delayus(4);
}
/*************************************************************************
*��������iic_ack
*�������ܣ���Ƭ������Ӧ��
*************************************************************************/
void iic_ack()
{
 SDA=0;
 Delayus(4);
 SCL=1;
 Delayus(4);
 SCL=0;
 Delayus(4);
 SDA=1;
 Delayus(4);
}
/*************************************************************************
*��������iic_NoAck
*�������ܣ���Ƭ��������Ӧ��
*************************************************************************/
void iic_NoAck()
{
 SDA=1;
 Delayus(4);
 SCL=1;
 Delayus(4);
 SCL=0;
 Delayus(4);
 SDA=0;
}
/*************************************************************************
*��������iic_testack
*�������ܣ����ģ���Ƿ񷵻�Ӧ�𣨼��Ӧ���źţ�0��Ӧ��1����Ӧ��
*************************************************************************/
bit iic_testack()   
{
 bit ErrorBit;
 SDA=1;
 Delayus(4);
 SCL=1;
 Delayus(4);
 ErrorBit=SDA;
 Delayus(4);
 SCL=0;
 return ErrorBit;
}
/*************************************************************************
*��������iic_write8bit
*�������ܣ���ģ��д��8λ
*************************************************************************/
void iic_write8bit(unsigned char input)
{
 unsigned char temp;
 for(temp=8;temp!=0;temp--)
 {
  SDA=(bit)(input&0x80);  //��ʱȡ����input�����λ
  Delayus(4);
  SCL=1;
  Delayus(4);
  SCL=0;
  Delayus(4);
  input=input<<1;
 }
}
/*************************************************************************
*��������iic_read8bit
*�������ܣ���ȡģ�鷴����8λ
*************************************************************************/
unsigned char iic_read8bit()
{
 unsigned char temp,rbyte=0;
 for(temp=8;temp!=0;temp--)
 {
  SCL=1;
  Delayus(4);
  rbyte=rbyte<<1;
  rbyte=rbyte|((unsigned char)SDA);  //��rbyte��¼SDA��ֵ
  SCL=0;
 }
 return rbyte; 
}

