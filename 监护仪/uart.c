#include "uart.h"




/*************************************************************
*��������set_baudrate
*�������ܣ���ʼ�����д��ڣ����ڲ�����һ�£�������ʹ�����ţ�
****************************************************************/
void set_baudrate(float frequency,long int baudrate)
{	
	unsigned int itmp; 	
	unsigned char tlow,thigh;

	IRC24MCR = 0x80;//ʹ���ڲ�24M�߾���IRC����
	
	AUXR |= 0x01;	  //����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//����1ģʽ0���ӱ�
	SCON = 0x50;    //���ڷ�ʽ1��1����ʼλ��1��ֹͣλ��8λ����
	PCON = 0x00;    //�����ʲ��ӱ�,SMOD=0
	S2CON = 0x50;   //�����ڽ������ݣ�ѡ��ʱ��2Ϊ����2�����ʷ�����
	S3CON = 0x10;   //�����ڽ������ݣ�ѡ��ʱ��2Ϊ����3�����ʷ�����
	S4CON = 0x10;   //�����ڽ������ݣ�ѡ��ʱ��2Ϊ����4�����ʷ�����
	
	itmp = (int)(65536-(frequency*1000000)/(baudrate*4));
	thigh = itmp/256; 	
	tlow = itmp%256; 	

	TH2 = thigh; 	
	TL2 = tlow; 	
	//EA = 1;   //�����ж�
	//ES = 1;   //�򿪴���1�ж�
	AUXR |= 0x10;		//������ʱ��2
	//REN = 1;	      //ʹ��SCON���н���λ  

}
/*****************************************************************
*��������TxByte
*�������ܣ����ڷ���һ���ֽ����ݣ�������д��ڣ������Ͳ������ж�
*****************************************************************/
void TxByte(unsigned char dat) 
{
	switch(uart_state){
		case 1:
			SBUF = dat;
			while(!TI);
			TI=0;
			break;
		case 2:
			S2BUF = dat;
			while(!(S2CON & 0x02));
			S2CON &= ~0x02;
			break;
		case 3:
			S3BUF = dat;
			while(!(S3CON & 0x02));
			S3CON &= ~0x02;
			break;
		case 4:
			S4BUF = dat;
			while(!(S4CON & 0x02));
			S4CON &= ~0x02;
			break;
	}
}

/**************************************************
*��������UartSendStr
*�������ܣ������ַ�����������д��ڣ�
***************************************************/
void UartSendStr(unsigned char *p)
{
	while(*p)
	{
		TxByte(*p++);
	}
}
/*******************************************************
*��������Uart1Isr
*�������ܣ�����1���жϺ���(�ֱ���GPS��SD�����)
*******************************************************/
void UartIsr() interrupt 4
{
	unsigned char tmp;  //���ջ���
	if(RI)
	{
		tmp=SBUF;
		switch (P_SW1){
			case 0x40: //RXD_2,SD������
				break;
			case 0x80: //RXD_3,��д���
				if(flag==3){
					if(tmp==0x5A)
						flag++;
					else
						flag=3;
				}
				else if(flag==4){
					if(tmp==0x5A)
						flag++;
					else
						flag=3;
				}
				else if((flag>=5)&&(flag<=11)){
					light[flag-5]=tmp;
					flag++;
					if(flag==11)
						flag=3;receive_ok=1;ES=0;
				}
				else
					flag=3;  //��������洢				
				break;
			case 0xc0: //RXD_4,GPS����
				if(flag==0){
					if(tmp=='$') 
						flag++;
					else 
						flag=0;
				}
				else if(flag==1){
					if(tmp=='R')
						flag++;
					else
						flag=1;
				}
				else if(flag==2){
					if(tmp==','){
						seg_count++;
						byte_count=0;
					}
					else
						switch(seg_count){
							case 2:
								lock=tmp;
								break;
							case 3:
								WD[byte_count++]=tmp;
								break;
							case 4:
								WD_a=tmp;
								break;
							case 5:
								JD[byte_count++]=tmp;
								break;
							case 6:
								JD_a=tmp;flag=0;receive_ok=1;ES=0;
								break;
						}
				}
				else 
					flag=0;  //��������洢
				break;
		}
		RI=0;
	}
}

/*******************************************************
*��������Uart3Isr
*�������ܣ�����3���жϺ���(����)
*******************************************************/
void Uart3Isr() interrupt 17
{
	//unsigned char tmp;
	if(S3CON & 0x01){
		
		S3CON &= ~0x01;
	}
}
