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

#define PID_KP 0
#define PID_KI 1
#define PID_KD 2

float pid_control(int target, int measured);
float PID_getValue(int8_t value);
void PID_setValue(int8_t value, float num);
char* PID_getValueToChar(int8_t value);

#endif /* INC_PID_H_ */
