/*
 * buzzer.h
 *
 *  Created on: 2020Äê3ÔÂ25ÈÕ
 *      Author: multimicro
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#include "stm32l1xx_gpio.h"

#define				BUZZER_PIN					GPIO_Pin_4
#define				BUZZER_PORT					GPIOA

#define             BUZZER_OFF()                (GPIO_ResetBits(BUZZER_PORT,BUZZER_PIN))
#define             BUZZER_ON()               (GPIO_SetBits(BUZZER_PORT,BUZZER_PIN))

void buzzer_init();
void buzzer_tick();
void buzzer_verify_password_success();
void buzzer_verify_password_fail();


#endif /* BUZZER_H_ */
