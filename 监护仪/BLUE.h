#ifndef __BLUE_H_
#define __BLUE_H_

//----加入定义的IO口----//
sbit STAT = P2^7;  //蓝牙连接为1

//---加入全局变量--//
extern unsigned char ECG[7];  //接收心电数据
extern unsigned char walk;  //接收步数


#endif