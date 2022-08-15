
#include "action.h"
#include "uart_get.h"
#include "motor.h"
#include "usart.h"
#include "delay.h"
#define Kp (100)
#define Kd 0

int Action_error_d[2];//记录速度偏差
int Action_Sonser_Error;//角度偏差
int Action_g_Duty;
int Action_Left_Duty,Action_Right_Duty;
int Action_Base_Duty = 6300;

int Action_PID_Place(int Set_Duty,int Actual_Duty)
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp * error + Kd * (error - Action_error_d[1]);
	Action_error_d[1] = Action_error_d[0];
	Action_error_d[0] = error;
	return Duty;
}



#define Kp_1 (-50)
#define Kd_1 -1
int Action1_error_d[2];//记录速度偏差
int Action1_Sonser_Error;//角度偏差
int Action1_g_Duty;
int Action1_Left_Duty,Action1_Right_Duty;

int Action1_PID_Place(int Set_Duty,int Actual_Duty)
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp_1 * error + Kd_1 * (error - Action1_error_d[1]);
	Action1_error_d[1] = Action1_error_d[0];
	Action1_error_d[0] = error;
	return Duty;
}



void get_milk_in_once(void)
{	
		
		Action_Sonser_Error = (int)(176-line_mid);
		Action_g_Duty = Action_PID_Place(0,Action_Sonser_Error);
		Action1_Sonser_Error=(int)(138-right_line_mid);
		Action1_g_Duty=Action1_PID_Place(0,Action1_Sonser_Error);
	
	
			Action_Left_Duty = Action_Base_Duty - Action_g_Duty;
			Action_Right_Duty = Action_Base_Duty + Action_g_Duty;

//--------------------------------------------------------------	

		int Action_Left1_Duty,Action_Left2_Duty,Action_Right1_Duty,Action_Right2_Duty;
		
		
		Action_Left1_Duty=Action_Left_Duty+Action1_g_Duty;
		Action_Left2_Duty=Action_Left_Duty-Action1_g_Duty;
		Action_Right1_Duty=Action_Right_Duty-Action1_g_Duty;
		Action_Right2_Duty=Action_Right_Duty+Action1_g_Duty;
		
		if(Action_Left1_Duty >= 8999)
		{
			 Action_Left1_Duty = 8999;
		}	  
		if(Action_Right1_Duty >= 8999)
		{
			 Action_Right1_Duty = 8999;
		}	
		if(Action_Left1_Duty <= -8999)
		{
			 Action_Left1_Duty = -8999;
		}
		if(Action_Right1_Duty <= -8999)
		{
			 Action_Right1_Duty = -8999;
		}
		
		if(Action_Left2_Duty >= 8999)
		{
			 Action_Left2_Duty = 8999;
		}	  
		if(Action_Right2_Duty >= 8999)
		{
			 Action_Right2_Duty = 8999;
		}	
		if(Action_Left2_Duty <= -8999)
		{
			 Action_Left2_Duty = -8999;
		}
		if(Action_Right2_Duty <= -8999)
		{
			 Action_Right2_Duty = -8999;
		}	
		
		
		
		if(Action_Left1_Duty > 0)
		{
			motor_left1_go(Action_Left1_Duty);
		}
		else if(Action_Left1_Duty < 0)
		{
			motor_left1_back(-Action_Left1_Duty);
		}
		else
		{
			motor_left1_back(0);
		}
		
		if(Action_Left2_Duty > 0)
		{
			motor_left2_go(Action_Left2_Duty);
		}
		else if(Action_Left2_Duty < 0)
		{
			motor_left2_back(-Action_Left2_Duty);
		}
		else
		{
			motor_left2_back(0);
		}
		
		if(Action_Right1_Duty > 0)
		{
			motor_right1_go(Action_Right1_Duty);
		}
		else if(Action_Right1_Duty < 0)
		{
			motor_right1_back(-Action_Right1_Duty);
		}
		else
		{
		  motor_right1_back(0);
		}
		
		if(Action_Right2_Duty > 0)
		{
			motor_right2_go(Action_Right2_Duty);
		}
		else if(Action_Right2_Duty < 0)
		{
			motor_right2_back(-Action_Right2_Duty);
		}
		else
		{
		  motor_right2_back(0);
		}		
		
//		printf(" %d  %d   %d   %d \n ",Action_Left1_Duty,Action_Left2_Duty,Action_Right1_Duty,Action_Right2_Duty);
}



void get_milk_in(void)
{	
		HAL_UART_Transmit(&huart4, (uint8_t*)"z", 1, 0xFFFF);	
		delay_ms(100);
		while(cross_flag){
			Car_go(7000);
			delay_ms(500);
		}			
		while(left_line_mid){
			get_milk_in_once();
		}	
		Car_stop();									
}

