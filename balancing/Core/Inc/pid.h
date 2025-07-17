/*
 * pid.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Hwabok
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "tim.h"
#include "stdlib.h"
#include "mpu6050.h"

#define PID_KP 0
#define PID_KI 1
#define PID_KD 2

#define MAX_PWM 60
#define Imax 70
#define motor_stop 0
#define motor_left 1
#define motor_right 2

float pid_control(float target, float measured);
float PID_getValue(int8_t value);
char* PID_getValueToChar(int8_t value);

void motor_control(mpu6050* __my_mpu6050,int pwm);
void set_pwm_duty_cycle(uint8_t dutyCycle);

#endif /* INC_PID_H_ */
