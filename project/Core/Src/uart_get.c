#include "uart_get.h"
#include "usart.h"
uint8_t recv_buf[2];
uint8_t line_mid;//Ѳ��ֵ
uint8_t right_line_mid;//��Ѳ��ֵ
uint8_t left_line_mid;//��Ѳ��ֵ
uint8_t cross_flag;//·�ڱ�־λ

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* �ж����ĸ����ڴ������ж� */
    if(huart ->Instance == UART4)
    {
        //�����յ������ݷ���
        tarck_ReceivData(recv_buf[0]);
        //����ʹ�ܴ��ڽ����ж�
        HAL_UART_Receive_IT(huart, (uint8_t*)recv_buf,1);
    }
}



int tarck_RxState=0;
int tarck_RxData[6];
//����track K210���ص�����
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
        tarck_HandleData();//ȫ��������ɣ��������ݴ���     
    }
    else//������������λ0
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






