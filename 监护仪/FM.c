#include "FM.h"

unsigned int max_pll=0x339b;           //108MHz时的pll,
unsigned int min_pll=0x299d;           //87.5MHz时的pll.

unsigned char radio_write_data[5]={0x2a,0xb6,0x40,0x11,0x40};        //要写入TEA5767的数据
unsigned char radio_read_data[5];        //TEA5767读出的状态

unsigned long frequency;
unsigned int pll;

/*************************************************************************
*函数名：radio_write
*函数功能：写入5个字节的命令
*************************************************************************/
void radio_write(void)
{
    unsigned char i;
    iic_start();
    iic_write8bit(0xc0);        //TEA5767写地址
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
*函数名：get_pll
*函数功能：由频率计算PLL
*************************************************************************/
void get_pll(void)
{
    unsigned char hlsi;
    unsigned int twpll=0;
    hlsi=radio_write_data[2]&0x10;
    if (hlsi)
        pll=(unsigned int)((float)((frequency+225)*4)/(float)32.768);    //频率单位:k
    else
        pll=(unsigned int)((float)((frequency-225)*4)/(float)32.768);    //频率单位:k
}

/*************************************************************************
*函数名：get_frequency
*函数功能：由PLL计算频率
*************************************************************************/
void get_frequency(void)
{
    unsigned char hlsi;
    unsigned int npll=0;
    npll=pll;
    hlsi=radio_write_data[2]&0x10;
    if (hlsi)
        frequency=(unsigned long)((float)(npll)*(float)8.192-225);    //频率单位:KHz
    else
        frequency=(unsigned long)((float)(npll)*(float)8.192+225);    //频率单位:KHz
}

/*************************************************************************
*函数名：radio_read
*函数功能：读TEA5767状态,并转换成频率
*************************************************************************/
void radio_read(void)
{
    unsigned char i;
    unsigned char temp_l,temp_h;
    pll=0;
    iic_start();
    iic_write8bit(0xc1);        //TEA5767读地址
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
*函数名：search
*函数功能：手动设置频率,mode=1,+0.01MHz; mode=0:-0.01MHz ,不用考虑TEA5767用于搜台的相关位:SM,SUD
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
*函数名：auto_search
*函数功能：自动搜台,mode=1,频率增加搜台; mode=0:频率减小搜台,不过这个好像不能循环搜台
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

    radio_write_data[0]=pll/256+0x40;      //加0x40是将SM置为1 为自动搜索模式
    radio_write_data[1]=pll%256;    
    radio_write_data[3]=0x11;              //SSL1和SSL0控制搜索停止条件             
    radio_write_data[4]=0x40;
    radio_write();
    radio_read();
    while(!(radio_read_data[0]&0x80))     //搜台成功标志
    {
        radio_read();
    }    
} 
