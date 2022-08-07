#include "motor.h"
#include "gpio.h"
#include "tim.h"
void motor_left1_back(int speed){
	TIM8->CCR1=speed;	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_SET);
}
void motor_left1_go(int speed){
	TIM8->CCR1=speed;	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_RESET);		
}
void motor_left1_stop(){	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_RESET);
}



void motor_left2_back(int speed){
	TIM8->CCR3=speed;	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_11,GPIO_PIN_SET);

}
void motor_left2_go(int speed){
	TIM8->CCR3=speed;	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_11,GPIO_PIN_RESET);		
}
void motor_left2_stop(){	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_11,GPIO_PIN_RESET);
}



void motor_right1_back(int speed){
	TIM8->CCR2=speed;	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_14,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_SET);

}
void motor_right1_go(int speed){
	TIM8->CCR2=speed;	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_14,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_RESET);		
}
void motor_right1_stop(){	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_14,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_RESET);
}

void motor_right2_back(int speed){
	TIM8->CCR4=speed;	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_SET);

}
void motor_right2_go(int speed){
	TIM8->CCR4=speed;	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_RESET);		
}
void motor_right2_stop(){	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_RESET);
}

void Car_back(int speed){
			motor_left1_go(speed);
		  motor_left2_go(speed);
			motor_right1_go(speed);
			motor_right2_go(speed);
}
void Car_go	(int speed){
			motor_left1_back(speed);
		  motor_left2_back(speed);
			motor_right1_back(speed);
			motor_right2_back(speed);
}
void Car_stop(){
			motor_left1_stop();
		  motor_left2_stop();
			motor_right1_stop();
			motor_right2_stop();
}

void Car_go_left(int speed){
			motor_left1_back(speed);
		  motor_left2_go(speed);
			motor_right1_go(speed);
			motor_right2_back(speed);
}


void Car_go_right(int speed){
			motor_left1_go(speed);
		  motor_left2_back(speed);
			motor_right1_back(speed);
			motor_right2_go(speed);
}
void Car_go_spinright(int speed){
			motor_left1_go(speed);
		  motor_left2_go(speed);
			motor_right1_back(speed);
			motor_right2_back(speed);	
}

void Car_go_spinleft(int speed){
			motor_left1_back(speed);
		  motor_left2_back(speed);
			motor_right1_go(speed);
			motor_right2_go(speed);	
}

int read_motor_left(){
			return -TIM2->CNT;
}

int read_motor_right(){
			return TIM5->CNT;
}

