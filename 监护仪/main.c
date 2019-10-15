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
				radio_write();   //��ʼд�루���ܻ�д���ظ���
				if(UP==0){       //��������
					DelayMs(1);
					if(UP==0){
						while(UP==0);  //������ɺ��޸�
						auto_search(1);  
					}
				}
				if(DOWN==0){     //��������
					DelayMs(1);
					if(DOWN==0){
						while(DOWN==0);  //������ɺ��޸�
						auto_search(0);   
					}
				}
				break;
			case 2:    //SD
				uart_state=1;  //����ʹ��״̬������1
				P_SW1=0x40;    //�л�Ϊ����RXD_2
				if(START==0){  //���ż�
					DelayMs(1);
					if(START==0){
						while(START==0);  //������ɺ��޸�
						for(i=0;i<4;i++) TxByte(start_SD[i]);
					}
				}
				if(UP==0){       //��������
					DelayMs(1);
					if(UP==0){
						while(UP==0);  //������ɺ��޸�
						for(i=0;i<4;i++) TxByte(SD_PREV[i]);
					}
				}
				if(DOWN==0){     //��������
					DelayMs(1);
					if(DOWN==0){
						while(DOWN==0);  //������ɺ��޸�
						for(i=0;i<4;i++) TxByte(SD_NEXT[i]);  
					}
				}	
				break;
			case 3:    //����
				uart_state=2;  //����ʹ��״̬������2 
				break;
			case 4:   //GPRSͨѶ
				uart_state=4;
				break;
			default:   //ʱ��
				uart_state=2;  //����ʹ��״̬������2
				break;	
		}
		if(time_renew==0){  //��ʾʱ�����
			DelayMs(1);
			if(time_renew==0){
				while(time_renew==0);  //������ɺ��޸�
			}
		}
		if(STAT==1){   //��������
			
		}	
		
	}
	
	
}
