#include "key.h"

/*************************************************************************
*函数名：Key_return
*函数功能：多置开关返回值 0-默认状态 1-选择收音 2-选择SD卡 3-选择分析显示 4-通讯
*************************************************************************/
unsigned char Key_return()
 {
	if(state_default==0){
		return 0;
	}
	else if(state_FM==0){
		return 1;
	}
	else if(state_SD==0){
		return 2;
	}
	else if(state_AN==0){
		return 3;
	}
	else if(state_GPRS==0){
		return 4;
	}
}