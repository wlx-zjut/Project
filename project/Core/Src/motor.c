#include "motor.h"
#include "gpio.h"
#include "tim.h"
#include "delay.h"
#include "usart.h"
void motor_left1_go(int speed){
	TIM8->CCR2=speed;	
	TIM8->CCR1=0;
}
void motor_left1_back(int speed){
	TIM8->CCR1=speed;	
	TIM8->CCR2=0;
}
void motor_left1_stop(){	
	TIM8->CCR1=8999;	
	TIM8->CCR2=8999;
}



void motor_right1_back(int speed){
	TIM12->CCR2=speed;	
	TIM12->CCR1=0;

}
void motor_right1_go(int speed){
	TIM12->CCR1=speed;	
	TIM12->CCR2=0;
}
void motor_right1_stop(){	
	TIM12->CCR1=8999;	
	TIM12->CCR2=8999;
}



void motor_left2_back(int speed){
	TIM8->CCR3=speed;	
	TIM8->CCR4=0;	

}
void motor_left2_go(int speed){
	TIM8->CCR4=speed;	
	TIM8->CCR3=0;	
}
void motor_left2_stop(){	
	TIM8->CCR4=8999;	
	TIM8->CCR3=8999;	
}


void motor_right2_go(int speed){
	TIM13->CCR1=speed;	
	TIM14->CCR1=0;	

}
void motor_right2_back(int speed){
	TIM13->CCR1=0;	
	TIM14->CCR1=speed;	
}
void motor_right2_stop(){	
	TIM13->CCR1=8999;	
	TIM14->CCR1=8999;	
}

void Car_go(int speed){
			motor_left1_go(speed);
		  motor_left2_go(speed);
			motor_right1_go(speed);
			motor_right2_go(speed);
}
void Car_back(int speed){
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
			motor_left2_go(speed);
			motor_left1_back(speed-100);

			motor_right1_go(speed-100);
			motor_right2_back(speed-100);
}

void Car_go_left_acc(int road){
		TIM2->CNT=30000;
		while(1){
			Car_go_left(8000);
			delay_ms(10);
			if(TIM2->CNT>30000+road){
					Car_stop();
					return ;
			}
		}
}



void Car_go_right(int speed){
			motor_left2_back(speed);
			delay_ms(10);
			motor_left1_go(speed);

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

void Car_go_right45(int speed){
			motor_left1_go(speed+1500);
		  motor_left2_back(speed);
			motor_right1_back(speed);
			motor_right2_go(speed+1500);	
}



int read_motor_left(){
			return -TIM2->CNT;
}

int read_motor_right(){
			return TIM5->CNT;
}
void turn_180(){
	Car_stop();
	delay_ms(100);
	TIM2->CNT=30000;
	TIM5->CNT=30000;	
	Car_go_spinright(8000);
	while(1){
		delay_ms(20);
		if((TIM2->CNT+TIM5->CNT)<55100){//Ô­À´ÊÇ55340
			Car_stop();
			return ;	
		}	
	}
}
