/*
 * pid.c
 *
 *  Created on: Jun 23, 2025
 *      Author: Hwabok
 */


#include "pid.h"

static float KP = 10.4;
static float KI = 5.0;
static float KD = 0.22;

static float prev_error=0, integral = 0;


static void motor_direction(int8_t direction){
	if(direction == motor_stop){
		HAL_GPIO_WritePin(MOTOR_BREAK_GPIO_Port, MOTOR_BREAK_Pin, GPIO_PIN_RESET);
	}else if(direction == motor_left){
		HAL_GPIO_WritePin(MOTOR_BREAK_GPIO_Port, MOTOR_BREAK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
	}else if(direction == motor_right){
		HAL_GPIO_WritePin(MOTOR_BREAK_GPIO_Port, MOTOR_BREAK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
	}
}

void motor_control(mpu6050* __my_mpu6050, int pwm){ // pitch 값에 다라 모터 속도,방향 조절
	if(__my_mpu6050->pitch > 57 || __my_mpu6050->pitch < 27) {
		pwm = 0;
		integral = 0;
		prev_error = 0;
		motor_direction(motor_stop);
		set_pwm_duty_cycle(0);
		return;
	}

	if(pwm > MAX_PWM) pwm = MAX_PWM;
	if(pwm < -MAX_PWM) pwm = -MAX_PWM;

	if(pwm > 0){
		motor_direction(motor_right);
		set_pwm_duty_cycle(pwm);
	}else if(pwm == 0){
		motor_direction(motor_stop);
		set_pwm_duty_cycle(pwm);
	}else if(pwm < 0){
		motor_direction(motor_left);
		set_pwm_duty_cycle(-pwm);
	}


}

float pid_control(float target, float measured){ // pid 계산
	float error;

	error = target - measured;

	integral += error * 0.01;

	if(integral > Imax) integral = Imax;
	if(integral < (-Imax)) integral = -Imax;
	//if((int)target == (int)measured) integral = 0;

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

void set_pwm_duty_cycle(uint8_t dutyCycle){ // 모터 듀티비(속도) 설정
	if (dutyCycle > 100) dutyCycle = 100;

	uint32_t ccr_value = (uint32_t)(1000 - 1000 * (dutyCycle / 100.0f));

	TIM3->CCR1 = ccr_value;
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
