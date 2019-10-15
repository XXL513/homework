#include "string.h"
#include "uart.h"
#include "I2C.h"
#include "key.h"
#include "FM.h"
#include "ds1302.h"


void main()
{
	unsigned char i;
	set_baudrate(24,9600);
	
	while(1){
		switch(Key_return()){
			case 1:    //FM
				radio_write();   //初始写入（可能会写入重复）
				if(UP==0){       //向上搜索
					DelayMs(1);
					if(UP==0){
						while(UP==0);  //按下完成后修改
						auto_search(1);  
					}
				}
				if(DOWN==0){     //向下搜索
					DelayMs(1);
					if(DOWN==0){
						while(DOWN==0);  //按下完成后修改
						auto_search(0);   
					}
				}
				break;
			case 2:    //SD
				uart_state=1;  //串口使用状态：串口1
				P_SW1=0x40;    //切换为串口RXD_2
				if(START==0){  //播放键
					DelayMs(1);
					if(START==0){
						while(START==0);  //按下完成后修改
						for(i=0;i<4;i++) TxByte(start_SD[i]);
					}
				}
				if(UP==0){       //向上搜索
					DelayMs(1);
					if(UP==0){
						while(UP==0);  //按下完成后修改
						for(i=0;i<4;i++) TxByte(SD_PREV[i]);
					}
				}
				if(DOWN==0){     //向下搜索
					DelayMs(1);
					if(DOWN==0){
						while(DOWN==0);  //按下完成后修改
						for(i=0;i<4;i++) TxByte(SD_NEXT[i]);  
					}
				}	
				break;
			case 3:    //分析
				uart_state=2;  //串口使用状态：串口2 
				break;
			case 4:   //GPRS通讯
				uart_state=4;
				break;
			default:   //时间
				uart_state=2;  //串口使用状态：串口2
				break;	
		}
		if(time_renew==0){  //显示时间更新
			DelayMs(1);
			if(time_renew==0){
				while(time_renew==0);  //按下完成后修改
			}
		}
		if(STAT==1){   //蓝牙接收
			
		}	
		
	}
	
	
}
