#include "FM.h"

unsigned int max_pll=0x339b;           //108MHzʱ��pll,
unsigned int min_pll=0x299d;           //87.5MHzʱ��pll.

unsigned char radio_write_data[5]={0x2a,0xb6,0x40,0x11,0x40};        //Ҫд��TEA5767������
unsigned char radio_read_data[5];        //TEA5767������״̬

unsigned long frequency;
unsigned int pll;

/*************************************************************************
*��������radio_write
*�������ܣ�д��5���ֽڵ�����
*************************************************************************/
void radio_write(void)
{
    unsigned char i;
    iic_start();
    iic_write8bit(0xc0);        //TEA5767д��ַ
    if(!iic_testack())
    {
        for(i=0;i<5;i++)
        {
            iic_write8bit(radio_write_data[i]);
            iic_ack();
        }
    }
    iic_stop();    
}

/*************************************************************************
*��������get_pll
*�������ܣ���Ƶ�ʼ���PLL
*************************************************************************/
void get_pll(void)
{
    unsigned char hlsi;
    unsigned int twpll=0;
    hlsi=radio_write_data[2]&0x10;
    if (hlsi)
        pll=(unsigned int)((float)((frequency+225)*4)/(float)32.768);    //Ƶ�ʵ�λ:k
    else
        pll=(unsigned int)((float)((frequency-225)*4)/(float)32.768);    //Ƶ�ʵ�λ:k
}

/*************************************************************************
*��������get_frequency
*�������ܣ���PLL����Ƶ��
*************************************************************************/
void get_frequency(void)
{
    unsigned char hlsi;
    unsigned int npll=0;
    npll=pll;
    hlsi=radio_write_data[2]&0x10;
    if (hlsi)
        frequency=(unsigned long)((float)(npll)*(float)8.192-225);    //Ƶ�ʵ�λ:KHz
    else
        frequency=(unsigned long)((float)(npll)*(float)8.192+225);    //Ƶ�ʵ�λ:KHz
}

/*************************************************************************
*��������radio_read
*�������ܣ���TEA5767״̬,��ת����Ƶ��
*************************************************************************/
void radio_read(void)
{
    unsigned char i;
    unsigned char temp_l,temp_h;
    pll=0;
    iic_start();
    iic_write8bit(0xc1);        //TEA5767����ַ
    if(!iic_testack())
    {
        for(i=0;i<5;i++)
        {
            radio_read_data[i]=iic_read8bit();
            iic_ack();
        }
    }
    iic_stop();
    temp_l=radio_read_data[1];
    temp_h=radio_read_data[0];
    temp_h&=0x3f;
    pll=temp_h*256+temp_l;
    get_frequency();
}

/*************************************************************************
*��������search
*�������ܣ��ֶ�����Ƶ��,mode=1,+0.01MHz; mode=0:-0.01MHz ,���ÿ���TEA5767������̨�����λ:SM,SUD
*************************************************************************/
void search(bit mode)
{
    radio_read();        
    if(mode)
    {
        frequency+=10;
        if(frequency>max_freq)
            frequency=min_freq;
    }
    else
    {
        frequency-=10;
        if(frequency<min_freq)
            frequency=max_freq;
    }          
    get_pll();
    radio_write_data[0]=pll/256;
    radio_write_data[1]=pll%256;
    radio_write_data[2]=0x41;
    radio_write_data[3]=0x11;
    radio_write_data[4]=0x40;
    radio_write();
}

/*************************************************************************
*��������auto_search
*�������ܣ��Զ���̨,mode=1,Ƶ��������̨; mode=0:Ƶ�ʼ�С��̨,�������������ѭ����̨
*************************************************************************/
void auto_search(bit mode)
{
    radio_read();        
    if(mode)
    {
        radio_write_data[2]=0xb1;
        frequency+=20;
        if(frequency>max_freq)
            frequency=min_freq;
    }
    else
    {
		radio_write_data[2]=0x41; 
        frequency-=20;
        if(frequency<min_freq)
            frequency=max_freq;
    }          
    get_pll();

    radio_write_data[0]=pll/256+0x40;      //��0x40�ǽ�SM��Ϊ1 Ϊ�Զ�����ģʽ
    radio_write_data[1]=pll%256;    
    radio_write_data[3]=0x11;              //SSL1��SSL0��������ֹͣ����             
    radio_write_data[4]=0x40;
    radio_write();
    radio_read();
    while(!(radio_read_data[0]&0x80))     //��̨�ɹ���־
    {
        radio_read();
    }    
} 
