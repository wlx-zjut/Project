#include "uart_get.h"
#include "usart.h"
uint8_t recv_buf[2];
uint8_t line_mid;//巡线值
uint8_t right_line_mid;//右巡线值
uint8_t left_line_mid;//左巡线值
uint8_t cross_flag;//路口标志位

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 判断是哪个串口触发的中断 */
    if(huart ->Instance == UART4)
    {
        //将接收到的数据发送
        tarck_ReceivData(recv_buf[0]);
        //重新使能串口接收中断
        HAL_UART_Receive_IT(huart, (uint8_t*)recv_buf,1);
    }
}



int tarck_RxState=0;
int tarck_RxData[6];
//接受track K210返回的数据
void tarck_ReceivData(uint8_t data)
{
	int i;

    if(tarck_RxState==0&&data=='a')
    {
        tarck_RxState=1;
        tarck_RxData[0]=data;
    }
    else if(tarck_RxState==1)
    {
        tarck_RxState=2;
        tarck_RxData[1] =data;
    }
    else if(tarck_RxState==2)
    {
        tarck_RxState=3;
        tarck_RxData[2] =data;
    }
    else if(tarck_RxState==3)
    {
        tarck_RxState=4;
        tarck_RxData[3] =data;
    }
    else if(tarck_RxState==4)
    {
        tarck_RxState=5;
        tarck_RxData[4] =data;
    }			
		else if(tarck_RxState==5&&data=='z')
    {
				tarck_RxState = 0;
        tarck_RxData[5] = data;
        tarck_HandleData();//全部接收完成，进行数据处理     
    }
    else//将所有数据置位0
    {
        tarck_RxState = 0;
        for( i=0;i<6;i++)
           tarck_RxData[i]=0;
    }
    
}


void tarck_HandleData()
{
		line_mid=tarck_RxData[1];
		right_line_mid=tarck_RxData[2];
		left_line_mid=tarck_RxData[3];
		cross_flag=tarck_RxData[4];
//		printf(" %d  %d   %d   %d \n ",line_mid,right_line_mid,left_line_mid,cross_flag);
}






