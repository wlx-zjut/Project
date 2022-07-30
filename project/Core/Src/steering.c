#include "steering.h"
#include "main.h"
#include "tim.h"
void	steering_to_0(){
	TIM10->CCR1=999;
}

void	steering_to_45(){
	TIM10->CCR1=1999;
}

void	steering_to_90(){
	TIM10->CCR1=2999;
}
void	steering_to_135(){
	TIM10->CCR1=3999;
}

void	steering_to_180(){
	TIM10->CCR1=4999;
}

