#ifndef __UART_GET_H__
#define __UART_GET_H__
#include "main.h"
extern uint8_t recv_buf[2];

void tarck_ReceivData(uint8_t data);
void tarck_HandleData(void);

extern uint8_t line_mid;//ȫ��Ѳ��ֵ
extern uint8_t right_line_mid;//Ѳ��ֵ
extern uint8_t left_line_mid;//Ѳ��ֵ
extern uint8_t cross_flag;//·�ڱ�־λ


#endif 





