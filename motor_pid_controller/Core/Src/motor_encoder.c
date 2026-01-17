/*
 * motor_encoder.c
 *
 *  Created on: Jan 9, 2026
 *      Author: Bartosz
 */

#include "motor_encoder.h"

void motor_encoder_init(motor_encoder_t* encoder, TIM_HandleTypeDef* encoder_tim,
		 uint8_t gear_ratio, uint8_t _cpr)
{
	encoder->encoder_timer = encoder_tim;
	encoder->last_value = 0;
	encoder->gear_ratio = gear_ratio;
	encoder->cpr = _cpr;
	encoder->rpm = 0.0f;

	arm_fir_init_f32(&encoder->filter.fir, SMA1_NUM_TAPS, SMA1_COEFFS, encoder->filter.state,SMA1_BLOCK_SIZE);
	HAL_TIM_Encoder_Start(encoder->encoder_timer, TIM_CHANNEL_ALL);
}

float32_t motor_encoder_rpm_callback(motor_encoder_t* encoder, uint16_t Ts_ms)
{
    int16_t curr = __HAL_TIM_GET_COUNTER(encoder->encoder_timer);
    int16_t delta = curr - encoder->last_value;

    float32_t Ts = Ts_ms * 0.001f;
    float32_t rpm_raw = (delta * 60.0f) / (encoder->cpr * Ts * encoder->gear_ratio);

    encoder->last_value = curr;
    float32_t rpm_filtered;
    arm_fir_f32(&encoder->filter.fir, &rpm_raw, &rpm_filtered, SMA1_BLOCK_SIZE);

    encoder->rpm = rpm_filtered;

    return rpm_filtered;
}

