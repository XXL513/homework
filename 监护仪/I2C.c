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
*函数名：iic_start
*函数功能：模拟开始时序
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
*函数名：iic_stop
*函数功能：模拟结束时序
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
*函数名：iic_ack
*函数功能：单片机给予应答
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
*函数名：iic_NoAck
*函数功能：单片机不给予应答
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
*函数名：iic_testack
*函数功能：检测模块是否返回应答（检测应答信号，0：应答，1：非应答）
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
*函数名：iic_write8bit
*函数功能：向模块写入8位
*************************************************************************/
void iic_write8bit(unsigned char input)
{
 unsigned char temp;
 for(temp=8;temp!=0;temp--)
 {
  SDA=(bit)(input&0x80);  //此时取的是input的最高位
  Delayus(4);
  SCL=1;
  Delayus(4);
  SCL=0;
  Delayus(4);
  input=input<<1;
 }
}
/*************************************************************************
*函数名：iic_read8bit
*函数功能：读取模块反馈的8位
*************************************************************************/
unsigned char iic_read8bit()
{
 unsigned char temp,rbyte=0;
 for(temp=8;temp!=0;temp--)
 {
  SCL=1;
  Delayus(4);
  rbyte=rbyte<<1;
  rbyte=rbyte|((unsigned char)SDA);  //用rbyte记录SDA的值
  SCL=0;
 }
 return rbyte; 
}

