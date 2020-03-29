/*
 * buzzer.c
 *
 *  Created on: 2020Äê3ÔÂ25ÈÕ
 *      Author: multimicro
 */

#include "buzzer.h"

void buzzer_init()
{
	GPIO_InitTypeDef io_cfg;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	io_cfg.GPIO_Pin     =  BUZZER_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_OUT;
	io_cfg.GPIO_OType 	= 	GPIO_OType_PP;
	//	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_NOPULL;
	//    io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(BUZZER_PORT, &io_cfg );
}

void buzzer_tick(){
	BUZZER_ON();
	Delay(100);
	BUZZER_OFF();
}

void buzzer_verify_password_success(){
	Delay(100);
	BUZZER_ON();
	Delay(500);
	BUZZER_OFF();
}

void buzzer_verify_password_fail(){
	BUZZER_ON();
	Delay(50);
	BUZZER_OFF();
	Delay(50);
	BUZZER_ON();
	Delay(50);
	BUZZER_OFF();
	Delay(50);
	BUZZER_ON();
	Delay(50);
	BUZZER_OFF();
}
