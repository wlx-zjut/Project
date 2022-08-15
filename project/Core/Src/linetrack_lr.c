#include "linetrack_lr.h"
#include "uart_get.h"
#include "motor.h"
#include "usart.h"
#include "delay.h"
int Kp_lr=20;
#define Kd 5
int LR_Track_error_d[2];//¼ÇÂ¼ËÙ¶ÈÆ«²î
int LR_Sonser_Error;//½Ç¶ÈÆ«²î
int LR_g_Duty;
int LR_Left_Duty,LR_Right_Duty;
int LR_Base_Duty = 8000;


int LR_Track_PID_Place(int Set_Duty,int Actual_Duty)
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp_lr * error + Kd * (error - LR_Track_error_d[1]);
	LR_Track_error_d[1] = LR_Track_error_d[0];
	LR_Track_error_d[0] = error;
	return Duty;
}

int right_left_cy;
void app_LineWalking_go_right(void)
{	
		Kp_lr=-25;
		LR_Sonser_Error = (int)(right_left_cy-left_line_mid);
		LR_g_Duty = LR_Track_PID_Place(0,LR_Sonser_Error);
		if(LR_g_Duty > 0) //³µÁ¾ÓÒÆ«
		{
			LR_Left_Duty = LR_Base_Duty - LR_g_Duty;
			LR_Right_Duty = LR_Base_Duty + LR_g_Duty;
		}
		else           //³µÁ¾×óÆ«
		{
			LR_Left_Duty = LR_Base_Duty - LR_g_Duty;
			LR_Right_Duty = LR_Base_Duty + LR_g_Duty;
		}
		if(LR_Left_Duty >= 8999)
		{
			 LR_Left_Duty = 8999;
		}	  
		if(LR_Right_Duty >= 8999)
		{
			 LR_Right_Duty = 8999;
		}		
		
		if(LR_Left_Duty <= -8999)
		{
			 LR_Left_Duty = -8999;
		}
		if(LR_Right_Duty <= -8999)
		{
			 LR_Right_Duty = -8999;
		}	
		
	 // printf("%d  %d \n",LR_Left_Duty,LR_Right_Duty);
		if(LR_Left_Duty > 0  && LR_Right_Duty > 0)
		{
			motor_left1_go(LR_Left_Duty);
			motor_left2_back(LR_Right_Duty);
			motor_right2_go(LR_Left_Duty);
			motor_right1_back(LR_Right_Duty);
			return ;
		}
		else if(LR_Left_Duty < 0 && LR_Right_Duty < 0 )
		{
			motor_left1_back(-LR_Left_Duty);
			motor_left2_go(-LR_Right_Duty);
			motor_right2_back(-LR_Left_Duty);
			motor_right1_go(-LR_Right_Duty);
		}
		else
		{
			motor_left1_go(0);
			motor_right2_go(0);
		}
		if(LR_Right_Duty > 0)
		{
			motor_left2_back(LR_Right_Duty);
			motor_right1_back(LR_Right_Duty);
		}
		else if(LR_Right_Duty < 0)
		{
			motor_left2_go(-LR_Right_Duty);
			motor_right1_go(-LR_Right_Duty);
		}
		else
		{
		  motor_left2_go(0);
			motor_right2_go(0);
		}
}



void app_LineWalking_go_left_start(void)
{	
		Kp_lr=-25;
		LR_Sonser_Error = (int)(right_left_cy-right_line_mid);
		LR_g_Duty = LR_Track_PID_Place(0,LR_Sonser_Error);
		if(LR_g_Duty > 0) //³µÁ¾ÓÒÆ«
		{
			LR_Left_Duty = LR_Base_Duty + LR_g_Duty;
			LR_Right_Duty = LR_Base_Duty - LR_g_Duty;
		}
		else           //³µÁ¾×óÆ«
		{
			LR_Left_Duty = LR_Base_Duty + LR_g_Duty;
			LR_Right_Duty = LR_Base_Duty - LR_g_Duty;
		}
		if(LR_Left_Duty >= 8999)
		{
			 LR_Left_Duty = 8999;
		}	  
		if(LR_Right_Duty >= 8999)
		{
			 LR_Right_Duty = 8999;
		}		
		
		if(LR_Left_Duty <= -8999)
		{
			 LR_Left_Duty = -8999;
		}
		if(LR_Right_Duty <= -8999)
		{
			 LR_Right_Duty = -8999;
		}	
		
	 // printf("%d  %d \n",LR_Left_Duty,LR_Right_Duty);
		if(LR_Left_Duty > 0  && LR_Right_Duty > 0)
		{
			motor_left1_back(LR_Left_Duty);
			motor_left2_go(LR_Right_Duty);
			motor_right2_back(LR_Left_Duty);
			motor_right1_go(LR_Right_Duty);
			return ;
		}
		else if(LR_Left_Duty < 0 && LR_Right_Duty < 0 )
		{
			motor_left1_go(-LR_Left_Duty);
			motor_left2_back(-LR_Right_Duty);
			motor_right2_go(-LR_Left_Duty);
			motor_right1_back(-LR_Right_Duty);
		}
		else
		{
			motor_left1_go(0);
			motor_right2_go(0);
		}
		if(LR_Right_Duty > 0)
		{
			motor_left2_go(LR_Right_Duty);
			motor_right1_go(LR_Right_Duty);
		}
		else if(LR_Right_Duty < 0)
		{
			motor_left2_back(-LR_Right_Duty);
			motor_right1_back(-LR_Right_Duty);
		}
		else
		{
		  motor_left2_go(0);
			motor_right2_go(0);
		}
}


void go_left_to_cross_start(void){
	while(1){
		Car_go_left_acc(950);
		if(!cross_flag) break;					
	}
	
	while(1){
			app_LineWalking_go_left_start();
			if(cross_flag){
			Car_stop();
			return ;
			}
	}
		return ;
}

void go_right_to_cross_start(void){

	while(1){
		Car_go_right(8000);
		delay_ms(1000);
		if(!cross_flag) break;					
	}
	
	while(1){
			app_LineWalking_go_right();
			if(cross_flag){
			Car_stop();
			return ;
			}
	}
		return ;
}