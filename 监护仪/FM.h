#ifndef _FM_H_
#define _FM_H_

//-----����ͷ�ļ�-----//
#include "STC8A.h"
#include "I2C.h"

//---�ض���ؼ���---//
#ifndef max_freq
#define max_freq 108000
#endif


#ifndef min_freq
#define min_freq 87500
#endif

//---����ȫ�ֺ���---//


//---����ȫ�ֱ���--//
extern unsigned int max_pll;           //108MHzʱ��pll,
extern unsigned int min_pll;           //87.5MHzʱ��pll.

extern unsigned char radio_write_data[5];        //Ҫд��TEA5767������
extern unsigned char radio_read_data[5];        //TEA5767������״̬

extern unsigned long frequency;
extern unsigned int pll;
//---����ȫ�ֺ���---//
void radio_write(void);  //д��radio_write_data[]
void get_pll(void);  //��Ƶ�ʼ���PLL
void get_frequency(void);  //��PLL����Ƶ��
void radio_read(void);   //��TEA5767״̬,��ת����Ƶ��
void search(bit mode);  //�ֶ�����Ƶ��,mode=1,+0.01MHz; mode=0:-0.01MHz ,���ÿ���TEA5767������̨�����λ:SM,SUD
void auto_search(bit mode);   //�Զ���̨,mode=1,Ƶ��������̨; mode=0:Ƶ�ʼ�С��̨,�������������ѭ����̨


#endif