#include "uart.h"




/*************************************************************
*函数名：set_baudrate
*函数功能：初始化所有串口（串口波特率一致，不开启使能引脚）
****************************************************************/
void set_baudrate(float frequency,long int baudrate)
{	
	unsigned int itmp; 	
	unsigned char tlow,thigh;

	IRC24MCR = 0x80;//使能内部24M高精度IRC振荡器
	
	AUXR |= 0x01;	  //串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//串口1模式0不加倍
	SCON = 0x50;    //串口方式1，1个起始位，1个停止位，8位数据
	PCON = 0x00;    //波特率不加倍,SMOD=0
	S2CON = 0x50;   //允许串口接收数据，选择定时器2为串口2波特率发生器
	S3CON = 0x10;   //允许串口接收数据，选择定时器2为串口3波特率发生器
	S4CON = 0x10;   //允许串口接收数据，选择定时器2为串口4波特率发生器
	
	itmp = (int)(65536-(frequency*1000000)/(baudrate*4));
	thigh = itmp/256; 	
	tlow = itmp%256; 	

	TH2 = thigh; 	
	TL2 = tlow; 	
	//EA = 1;   //打开总中断
	//ES = 1;   //打开串口1中断
	AUXR |= 0x10;		//启动定时器2
	//REN = 1;	      //使能SCON串行接收位  

}
/*****************************************************************
*函数名：TxByte
*函数功能：串口发送一个字节数据（针对所有串口），发送不进入中断
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
*函数名：UartSendStr
*函数功能：发送字符串（针对所有串口）
***************************************************/
void UartSendStr(unsigned char *p)
{
	while(*p)
	{
		TxByte(*p++);
	}
}
/*******************************************************
*函数名：Uart1Isr
*函数功能：串口1的中断函数(分别处理GPS、SD、光感)
*******************************************************/
void UartIsr() interrupt 4
{
	unsigned char tmp;  //接收缓存
	if(RI)
	{
		tmp=SBUF;
		switch (P_SW1){
			case 0x40: //RXD_2,SD卡处理
				break;
			case 0x80: //RXD_3,光感处理
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
					flag=3;  //消除记忆存储				
				break;
			case 0xc0: //RXD_4,GPS处理
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
					flag=0;  //消除记忆存储
				break;
		}
		RI=0;
	}
}

/*******************************************************
*函数名：Uart3Isr
*函数功能：串口3的中断函数(蓝牙)
*******************************************************/
void Uart3Isr() interrupt 17
{
	//unsigned char tmp;
	if(S3CON & 0x01){
		
		S3CON &= ~0x01;
	}
}
