#include "key.h"

/*************************************************************************
*��������Key_return
*�������ܣ����ÿ��ط���ֵ 0-Ĭ��״̬ 1-ѡ������ 2-ѡ��SD�� 3-ѡ�������ʾ 4-ͨѶ
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