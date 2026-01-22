/*
 * motor_system.c
 *
 *  Created on: Jan 18, 2026
 *      Author: Bartosz
 */


#include "motor_system.h"


void motor_system_init(motor_system_t* motor_sys,
                       motor_controller_t* controller,
                       motor_encoder_t* encoder)
{
	motor_sys->controller = controller;
	motor_sys->encoder = encoder;

	motor_sys->PID.Kp = PID_KP;
	motor_sys->PID.Ki = PID_KI;
	motor_sys->PID.Kd = PID_KD;
	motor_sys->targeted_rpm = 0;
	arm_pid_init_f32(&(motor_sys->PID), 1);
}

void update_pid_gains(motor_system_t* motor_sys, float32_t kp, float32_t ki, float32_t kd)
{
    ((float32_t*)PID_GAINS_UINT)[0] = kp;
    ((float32_t*)PID_GAINS_UINT)[1] = ki;
    ((float32_t*)PID_GAINS_UINT)[2] = kd;

    motor_sys->PID.Kp = kp;
    motor_sys->PID.Ki = ki;
    motor_sys->PID.Kd = kd;

    arm_pid_init_f32(&(motor_sys->PID), 1);
}

void motor_system_set_rpm(motor_system_t* motor_sys, float rpm)
{
	float32_t pid_out = arm_pid_f32(&(motor_sys->PID), rpm - motor_sys->encoder->rpm);
	int32_t value = CONTROLLER_MIN_ROT_VALUE + (int32_t)pid_out;
    if(value > CONTROLLER_MAX_ROT_VALUE) value = CONTROLLER_MAX_ROT_VALUE;
    if(value < CONTROLLER_MIN_ROT_VALUE) value = CONTROLLER_MIN_ROT_VALUE;
    motor_controller_set_value(motor_sys->controller, value);
}
