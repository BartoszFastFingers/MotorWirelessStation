/*
 * motor_system.h
 *
 *  Created on: Jan 9, 2026
 *      Author: Bartosz
 */

#ifndef CORE_INC_MOTOR_SYSTEM_H_
#define CORE_INC_MOTOR_SYSTEM_H_

#include "motor_controller.h"
#include "motor_encoder.h"
#include "PID_pid.h"


typedef struct {
	motor_controller_t*	controller;
	motor_encoder_t* encoder;
	arm_pid_instance_f32 PID;
	float targeted_rpm;
}motor_system_t;

void motor_system_init(motor_system_t* motor_sys,
                       motor_controller_t* controller,
                       motor_encoder_t* encoder);

void update_pid_gains(motor_system_t* motor_sys, float32_t kp, float32_t ki, float32_t kd);

void motor_system_set_rpm(motor_system_t* motor_sys, float rpm);
#endif /* CORE_INC_MOTOR_SYSTEM_H_ */
