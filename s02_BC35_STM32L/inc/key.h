/*
 * key.h
 *
 *  Created on: 2020Äê3ÔÂ25ÈÕ
 *      Author: multimicro
 */

#ifndef KEY_H_
#define KEY_H_
#include "stm32l1xx_gpio.h"

#define				KEY_WITHE_0_PIN					GPIO_Pin_5
#define				KEY_WITHE_1_PIN					GPIO_Pin_6
#define				KEY_WITHE_2_PIN					GPIO_Pin_7
#define				KEY_BLACK_0_PIN					GPIO_Pin_12
#define				KEY_BLACK_1_PIN					GPIO_Pin_13
#define				KEY_BLACK_2_PIN					GPIO_Pin_14
#define				KEY_BLACK_3_PIN					GPIO_Pin_15
#define				KEY_WITHE_PORT					GPIOA
#define				KEY_BLACK_PORT					GPIOB


#define             KEY_WITHE_0_LOW()                (GPIO_ResetBits(KEY_WITHE_PORT,KEY_WITHE_0_PIN))
#define             KEY_WITHE_0_HIGH()                 (GPIO_SetBits(KEY_WITHE_PORT,KEY_WITHE_0_PIN))
#define             KEY_WITHE_1_LOW()                (GPIO_ResetBits(KEY_WITHE_PORT,KEY_WITHE_1_PIN))
#define             KEY_WITHE_1_HIGH()                 (GPIO_SetBits(KEY_WITHE_PORT,KEY_WITHE_1_PIN))
#define             KEY_WITHE_2_LOW()                (GPIO_ResetBits(KEY_WITHE_PORT,KEY_WITHE_2_PIN))
#define             KEY_WITHE_2_HIGH()                 (GPIO_SetBits(KEY_WITHE_PORT,KEY_WITHE_2_PIN))

#define				KEY_BLACK_0_READ()				 (GPIO_ReadInputDataBit(KEY_BLACK_PORT,KEY_BLACK_0_PIN))
#define				KEY_BLACK_1_READ()				 (GPIO_ReadInputDataBit(KEY_BLACK_PORT,KEY_BLACK_1_PIN))
#define				KEY_BLACK_2_READ()				 (GPIO_ReadInputDataBit(KEY_BLACK_PORT,KEY_BLACK_2_PIN))
#define				KEY_BLACK_3_READ()				 (GPIO_ReadInputDataBit(KEY_BLACK_PORT,KEY_BLACK_3_PIN))

#define 			ADMIN_STATUS_ON					0
#define 			ADMIN_STATUS_OFF				1


//#define             KEY_BLACK_0_LOW()                (GPIO_ResetBits(KEY_BLACK_PORT,KEY_BLACK_0_PIN))
//#define             KEY_BLACK_0_HIGH()               (GPIO_SetBits(KEY_BLACK_PORT,KEY_BLACK_0_PIN))
//#define             KEY_BLACK_1_LOW()                (GPIO_ResetBits(KEY_BLACK_PORT,KEY_BLACK_1_PIN))
//#define             KEY_BLACK_1_HIGH()               (GPIO_SetBits(KEY_BLACK_PORT,KEY_BLACK_1_PIN))
//#define             KEY_BLACK_2_LOW()                (GPIO_ResetBits(KEY_BLACK_PORT,KEY_BLACK_2_PIN))
//#define             KEY_BLACK_2_HIGH()               (GPIO_SetBits(KEY_BLACK_PORT,KEY_BLACK_2_PIN))
//#define             KEY_BLACK_3_LOW()                (GPIO_ResetBits(KEY_BLACK_PORT,KEY_BLACK_3_PIN))
//#define             KEY_BLACK_3_HIGH()               (GPIO_SetBits(KEY_BLACK_PORT,KEY_BLACK_3_PIN))

int admin_status;

void key_init();
void key_scan();
void set_password(unsigned int);
void verify_password();

#endif /* KEY_H_ */
