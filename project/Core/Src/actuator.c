#include "actuator.h"

void actuator_down(int speed){
	TIM11->CCR1=speed;
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);
}
void actuator_up(int speed){
	TIM11->CCR1=speed;
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);
}
void actuator_stop(){
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_4,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);
}


