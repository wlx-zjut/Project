#include "linetrack.h"
#include "uart_get.h"
#include "motor.h"
#include "usart.h"
#include "delay.h"
#define Kp (-50)
#define Kd 0
int Track_error_d[2];//¼ÇÂ¼ËÙ¶ÈÆ«²î
int Sonser_Error;//½Ç¶ÈÆ«²î
int g_Duty;
int Left_Duty,Right_Duty;
int Base_Duty = 8000;

int Track_PID_Place(int Set_Duty,int Actual_Duty)
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp * error + Kd * (error - Track_error_d[1]);
	Track_error_d[1] = Track_error_d[0];
	Track_error_d[0] = error;
	return Duty;
}



void app_LineWalking_go(void)
{	
		
		Sonser_Error = (int)(155-line_mid);
		g_Duty = Track_PID_Place(0,Sonser_Error);
		if(g_Duty > 0) //³µÁ¾ÓÒÆ«
		{
			Left_Duty = Base_Duty - g_Duty;
			Right_Duty = Base_Duty + g_Duty;
		}
		else           //³µÁ¾×óÆ«
		{
			Left_Duty = Base_Duty - g_Duty;
			Right_Duty = Base_Duty + g_Duty;
		}
		if(Left_Duty >= 8999)
		{
			 Left_Duty = 8999;
		}	  
		if(Right_Duty >= 8999)
		{
			 Right_Duty = 8999;
		}	
		if(Left_Duty <= -8999)
		{
			 Left_Duty = -8999;
		}
		if(Right_Duty <= -8999)
		{
			 Right_Duty = -8999;
		}
		if(Left_Duty > 0)
		{
			motor_left1_back(Left_Duty);
			motor_right2_back(Left_Duty);
		}
		else if(Left_Duty < 0)
		{
			motor_left1_go(-Left_Duty);
			motor_right2_go(-Left_Duty);
		}
		else
		{
			motor_left1_back(0);
			motor_right2_back(0);
		}
		if(Right_Duty > 0)
		{
			motor_right1_back(Right_Duty);
			motor_left2_back(Right_Duty);
		}
		else if(Right_Duty < 0)
		{
			motor_right1_go(-Right_Duty);
			motor_left2_go(-Right_Duty);
		}
		else
		{
		  motor_right1_back(0);
			motor_left2_back(0);
		}
}



void app_LineWalking_back(void)
{	
		
		Sonser_Error = (int)(155-line_mid);
		g_Duty = Track_PID_Place(0,Sonser_Error);
		if(g_Duty > 0) //³µÁ¾ÓÒÆ«
		{
			Left_Duty = Base_Duty + g_Duty;
			Right_Duty = Base_Duty - g_Duty;
		}
		else           //³µÁ¾×óÆ«
		{
			Left_Duty = Base_Duty + g_Duty;
			Right_Duty = Base_Duty - g_Duty;
		}
		if(Left_Duty >= 8999)
		{
			 Left_Duty = 8999;
		}	  
		if(Right_Duty >= 8999)
		{
			 Right_Duty = 8999;
		}	
		if(Left_Duty <= -8999)
		{
			 Left_Duty = -8999;
		}
		if(Right_Duty <= -8999)
		{
			 Right_Duty = -8999;
		}
		if(Left_Duty > 0)
		{
			motor_left1_go(Left_Duty);
			motor_right2_go(Left_Duty);
		}
		else if(Left_Duty < 0)
		{
			motor_left1_back(-Left_Duty);
			motor_right2_back(-Left_Duty);
		}
		else
		{
			motor_left1_back(0);
			motor_right2_back(0);
		}
		if(Right_Duty > 0)
		{
			motor_right1_go(Right_Duty);
			motor_left2_go(Right_Duty);
		}
		else if(Right_Duty < 0)
		{
			motor_right1_back(-Right_Duty);
			motor_left2_back(-Right_Duty);
		}
		else
		{
		  motor_right1_back(0);
			motor_left2_back(0);
		}
}



void LineWalking_go_cross_stop(void){
	Car_back(8000);
	delay_ms(1000);
	
	while(1){
			app_LineWalking_go();
			if(cross_flag){
			Car_stop();
			return ;
			}
	}
		return ;
}


void LineWalking_back_cross_stop(void){
	while(1){
			app_LineWalking_back();
			if(cross_flag){
			Car_stop();
			return ;
			}
	}
		return ;
}