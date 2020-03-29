/*
 * sw180.h
 *
 *  Created on: 2020Äê3ÔÂ25ÈÕ
 *      Author: multimicro
 */

#ifndef SW180_H_
#define SW180_H_

#include "stm32l1xx_gpio.h"

#define				SW180_15P_PIN					GPIO_Pin_3
#define				SW180_15P_PORT					GPIOB

#define				SW180_15P_READ()				(GPIO_ReadInputDataBit(SW180_15P_PORT,SW180_15P_PIN))

#define				SW180_VIBRATE_ON				1
#define				SW180_VIBRATE_OFF				0


int sw180_filter;
int sw180_status;

void sw180_init();

#endif /* SW180_H_ */
