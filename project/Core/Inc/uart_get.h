#ifndef __UART_GET_H__
#define __UART_GET_H__
#include "main.h"
extern uint8_t recv_buf[2];

void tarck_ReceivData(uint8_t data);
void tarck_HandleData(void);

extern uint8_t line_mid;//全局巡线值
extern uint8_t right_line_mid;//巡线值
extern uint8_t left_line_mid;//巡线值
extern uint8_t cross_flag;//路口标志位


#endif 





