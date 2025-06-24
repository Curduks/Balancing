/*
 * rotary_encoder.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Hwabok
 */


#include "rotary_encoder.h"

static float rotary = 0;
static float pid_value = 0;
static int8_t change_mode = 0;

void rotary_encoder_init(){
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	TIM2->CNT = 1000; // 1000 == 0 / 음수 표현을 위해
}

void rotary_encoder_set(){
	if(change_mode == ROTARY_ENCODER_MENU){
		rotary = TIM2->CNT;
		if(rotary >= 1003) {
			rotary = 1002;
			TIM2->CNT = 1002;
		}
		if(rotary < 1000) {
			rotary = 1000;
			TIM2->CNT = 1000;
		}
	}else if(change_mode == ROTARY_ENCODER_PID){
		pid_value = TIM2->CNT;
	}
}

float rotary_encoder_get(){
	if(change_mode == ROTARY_ENCODER_MENU)
		return (rotary-1000);
	else if(change_mode == ROTARY_ENCODER_PID)
		return (pid_value-1000);
}

int8_t rotary_encoder_menu_get(){
	return rotary-1000;
}

float rotary_encoder_pid_get(){
	return pid_value-1000;
}

void rotary_encoder_pid_clear(){
	TIM2->CNT = rotary;
	pid_value = 1000;
}

void rotary_setMode(int8_t mode){
	switch (mode) {
		case ROTARY_ENCODER_MENU:
			change_mode = 0;
			break;
		case ROTARY_ENCODER_PID:
			change_mode = 1;
			break;
		default:
			break;
	}
}

int8_t rotary_getMode(){
	return change_mode;
}
