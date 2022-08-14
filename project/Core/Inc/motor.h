#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "motor.h"
#include "main.h"
void motor_left1_go(int speed);
void motor_left1_back(int speed);
void motor_left1_stop(void);

void motor_left2_go(int speed);
void motor_left2_back(int speed);
void motor_left2_stop(void);

void motor_right1_go(int speed);
void motor_right1_back(int speed);
void motor_right1_stop(void);

void motor_right2_go(int speed);
void motor_right2_back(int speed);
void motor_right2_stop(void);

void Car_go(int speed);
void Car_back(int speed);
void Car_stop(void);

void Car_go_left(int speed);
void Car_go_right(int speed);
void Car_go_spinright(int speed);
void Car_go_spinleft(int speed);

int read_motor_left(void);
int read_motor_right(void);

void turn_180(void);
#endif


