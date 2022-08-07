#include "actuator.h"
#include "usart.h"
#include "delay.h"
#include <stdlib.h>
#include <math.h>

void rightactuator_down(int speed){
	TIM9->CCR1=speed;
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);
}
void rightactuator_up(int speed){
	TIM9->CCR1=speed;
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);
}
void rightactuator_stop(){
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);
}


void leftactuator_down(int speed){
	TIM9->CCR2=speed;
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_13,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_10,GPIO_PIN_SET);
}
void leftactuator_up(int speed){
	TIM9->CCR2=speed;
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_13,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_10,GPIO_PIN_RESET);
}
void leftactuator_stop(){
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_13,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_10,GPIO_PIN_RESET);
}


int read_leftactuator(){
	return TIM1->CNT;	
}
int read_rightactuator(){
	return TIM3->CNT;	
}


int Kp=-250,Kd=0,Ki=0;
int error_d=0;


int PID_Place(int Set_Duty,int Actual_Duty,int integral)//目标值,实际值,积分值
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp * error + Kd * (error - error_d)+Ki*integral;
	error_d = error;
	return Duty;
}


int Kp_1=-100,Kd_1=0;
int error_d_1=0;
int PID_Place_once(int Set_Duty,int Actual_Duty)//目标值,实际值
{
	int error;
	int Duty;
	error = Actual_Duty - Set_Duty;
	Duty = Kp_1 * error + Kd_1 * (error - error_d);
	error_d_1 = error;
	return Duty;
}


int break_flag=0;


void PID_once_actuator(int goal_height,int left_actual_height,int right_actual_height,int left_integral,int right_integral)//目标高度,实际高度,路径积分
{
	  int left_PWM,right_PWM;
		Kp=-500;
		left_PWM=PID_Place(goal_height,left_actual_height,left_integral);
	  Kp=-250;
		right_PWM=PID_Place(goal_height,right_actual_height,right_integral);
		if(abs(goal_height-left_actual_height)<=25 &&  abs(goal_height-right_actual_height)<=25) break_flag=1;
//		if(left_PWM<=6500&&right_PWM<=2000 &&   left_PWM>0&&right_PWM>0) break_flag=1;
//		if(left_PWM>=-6500&&right_PWM>=-2000 && left_PWM<0&&right_PWM<0) break_flag=1;
		printf("%d   %d  %d\n",abs(goal_height-left_actual_height),abs(goal_height-right_actual_height),break_flag);
	  int Set_height;
		Set_height=(left_actual_height+right_actual_height)/2;
	
	
	
	  left_PWM-=PID_Place_once(Set_height,left_actual_height);
		right_PWM+=PID_Place_once(Set_height,right_actual_height);

	
	
		if(left_PWM>=8999)   left_PWM=8999;
		if(left_PWM<=-8999)  left_PWM=-8999;	
		if(right_PWM>=8799)  right_PWM=8799;
		if(right_PWM<=-8799) right_PWM=-8799;		

		if(left_PWM>=0) leftactuator_up(left_PWM);
	  else            leftactuator_down(left_PWM);
	
		if(right_PWM>=0)rightactuator_up(left_PWM);
	  else            rightactuator_down(left_PWM);
}


void PID_actuator(int goal_height)//目标高度
{
	  int left_actual_height,right_actual_height;
		TIM1->CNT=30000;
	  TIM3->CNT=30000;
	  while(1){
			left_actual_height=TIM1->CNT-30000;
			right_actual_height=TIM3->CNT-30000;	
			PID_once_actuator(goal_height,left_actual_height,right_actual_height,left_actual_height,right_actual_height);
			//printf("height  %d  %d   \n",TIM3->CNT,TIM1->CNT);	

			if(break_flag==1){
				leftactuator_stop();
				rightactuator_stop();
				break_flag=0;
				break;			
		  }
		}
}


void actuator_down_end()//降到底
{
	  int tim1_last=0,tim3_last=0;
		while(1){
		leftactuator_down(8999);
		rightactuator_down(8999);
		delay_ms(50);			
			if(tim1_last==TIM1->CNT &&  tim3_last==TIM3->CNT)
			{
				leftactuator_stop();
				rightactuator_stop();
				return ;				
			}
					tim1_last=TIM1->CNT;
					tim3_last=TIM3->CNT;
		}
}










