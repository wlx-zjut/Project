

#ifndef __ACTUATOR_H_
#define __ACTUATOR_H_
#include "main.h"
void leftactuator_up(int speed);
void leftactuator_down(int speed);
void leftactuator_stop(void);

void rightactuator_up(int speed);
void rightactuator_down(int speed);
void rightactuator_stop(void);

int read_leftactuator(void);
int read_rightactuator(void);

void PID_actuator(int goal_height);//目标高度
void actuator_down_end(void);//降到底
#endif






