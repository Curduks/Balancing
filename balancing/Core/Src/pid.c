/*
 * pid.c
 *
 *  Created on: Jun 23, 2025
 *      Author: Hwabok
 */


#include "pid.h"

static float KP =  0.3;
static float KI = 0.2;
static float KD = 0.1;

float pid_control(int target, int measured){
	static float error, prev_error=0, integral = 0;
	error = target - measured;
	integral += error * 0.01;
	float derivative = (error - prev_error) / 0.01;
	prev_error = error;

	return KP * error + KI * integral + KD * derivative;
}

float PID_getValue(int8_t value){
	switch (value) {
		case PID_KP:
			return KP;
			break;
		case PID_KI:
			return KI;
			break;
		case PID_KD:
			return KD;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}

void PID_setValue(int8_t value, float num){
	switch (value) {
		case PID_KP:
			KP += num;
			break;
		case PID_KI:
			KI += num;
			break;
		case PID_KD:
			KD += num;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}

char* PID_getValueToChar(int8_t value){
	static char values[6];
	switch (value) {
		case PID_KP:
			gcvt(KP,2, values);

			for(int i = 0; i < 5; i++){
			  if(values[i] == '\0' || values[i] == 165){
				  values[i] = ' ';
			  }
			}
			values[5] = '\0';
			return values;
			break;
		case PID_KI:
			gcvt(KI,2, values);
			for(int i = 0; i < 5; i++){
			  if(values[i] == '\0' || values[i] == 165){
				  values[i] = ' ';
			  }
			}
			values[5] = '\0';
			return values;
			break;
		case PID_KD:
			gcvt(KD,2, values);
			for(int i = 0; i < 5; i++){
			  if(values[i] == '\0' || values[i] == 165){
				  values[i] = ' ';
			  }
			}
			values[5] = '\0';
			return values;
			break;
		default:
			break;
	}
	return values;
}
