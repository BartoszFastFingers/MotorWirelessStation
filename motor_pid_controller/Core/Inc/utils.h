/*
 * utils.h
 *
 *  Created on: Jan 9, 2026
 *      Author: Bartosz
 */

#ifndef CORE_INC_UTILS_H_
#define CORE_INC_UTILS_H_

#include "gpio.h"

typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PIN;
}pin_t;

#endif /* CORE_INC_UTILS_H_ */
