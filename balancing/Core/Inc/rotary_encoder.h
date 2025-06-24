/*
 * rotary_encoder.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Hwabok
 */

#ifndef INC_ROTARY_ENCODER_H_
#define INC_ROTARY_ENCODER_H_

#include "tim.h"

#define ROTARY_ENCODER_MENU 0
#define ROTARY_ENCODER_PID 1

void rotary_encoder_init();

void rotary_encoder_set();
int8_t rotary_encoder_menu_get();
float rotary_encoder_pid_get();
void rotary_encoder_pid_clear();

void rotary_setMode(int8_t);
int8_t rotary_getMode();

#endif /* INC_ROTARY_ENCODER_H_ */
