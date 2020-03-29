/*
 * key.c
 *
 *  Created on: 2020年3月25日
 *      Author: multimicro
 */
#include "key.h"
#include "buzzer.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "timer.h"

unsigned char password_fixed[10];
unsigned char password_key[10];
unsigned int password_key_conter;


void key_init()
{
	GPIO_InitTypeDef io_cfg;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	io_cfg.GPIO_Pin     =  KEY_WITHE_0_PIN | KEY_WITHE_1_PIN | KEY_WITHE_2_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_OUT;
	io_cfg.GPIO_OType 	= 	GPIO_OType_PP;
	//	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_NOPULL;
	//    io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(KEY_WITHE_PORT, &io_cfg );
	//	io_cfg.GPIO_Pin     =  KEY_WITHE_1_PIN;
	//	GPIO_Init(KEY_WITHE_PORT, &io_cfg );
	//	io_cfg.GPIO_Pin     =  KEY_WITHE_2_PIN;
	//	GPIO_Init(KEY_WITHE_PORT, &io_cfg );

	//IN
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	io_cfg.GPIO_Pin     =  KEY_BLACK_0_PIN | KEY_BLACK_1_PIN | KEY_BLACK_2_PIN | KEY_BLACK_3_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_IN;
	io_cfg.GPIO_OType 	= 	GPIO_OType_PP;
	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(KEY_BLACK_PORT, &io_cfg );
	//	io_cfg.GPIO_Pin     =  KEY_BLACK_1_PIN;
	//	GPIO_Init(KEY_BLACK_PORT, &io_cfg );
	//	io_cfg.GPIO_Pin     =  KEY_BLACK_2_PIN;
	//	GPIO_Init(KEY_BLACK_PORT, &io_cfg );
	//	io_cfg.GPIO_Pin     =  KEY_BLACK_3_PIN;
	//	GPIO_Init(KEY_BLACK_PORT, &io_cfg );

	KEY_WITHE_0_HIGH();
	KEY_WITHE_1_HIGH();
	KEY_WITHE_2_HIGH();
	memset(password_key,'\0',sizeof(password_key));
	password_key_conter = 0;
	admin_status = ADMIN_STATUS_OFF;
}

void set_password(unsigned int paw){

	sprintf(password_fixed,"%d",paw);
	Uart1_SendStr("Enter password is: ");
	Uart1_SendStr(password_fixed);
	Uart1_SendStr("\r\n");
}

void verify_password(){
	char *strx;
	strx = strstr(password_key,"#");
	if (strx == NULL) {
		return;
	}
	Uart1_SendStr("Input password is:   ");
	Uart1_SendStr(password_key);
	Uart1_SendStr("\r\n");
	Uart1_SendStr("Correct password is: ");
	Uart1_SendStr(password_fixed);
	Uart1_SendStr("\r\n");
	if (strstr(password_key,password_fixed) == NULL || password_key_conter != 5 ) {
		memset(password_key,'\0',sizeof(password_key));
		password_key_conter = 0;
		Uart1_SendStr("Please reenter the password!\r\n");
		buzzer_verify_password_fail();
	} else {
		Uart1_SendStr("Verify password success!\r\n");
		buzzer_verify_password_success();
		admin_status = !admin_status;
		// code
		memset(password_key,'\0',sizeof(password_key));
		password_key_conter = 0;
	}

}

void key_scan(){

	//扫描原理
	//此按键为3x4
	/*
	 * 		KEY_BLACK_0	———————————————————————————————————————————————
	 *							|				|				|
	 * 		KEY_BLACK_1	———————————————————————————————————————————————
	 *							|				|				|
	 * 		KEY_BLACK_2	———————————————————————————————————————————————
	 *							|				|				|
	 * 		KEY_BLACK_3	———————————————————————————————————————————————
	 *							|				|				|
	 *					  KEY_WHITE_0      KEY_WHITE_1     KEY_WHITE_2
	 *
	 *		1. 横列的引脚配置为输入引脚，纵列的引脚配置为输出引脚，初始输出电平为低
	 *		2. 分别拉高KEY_WHITE_x的电平，然后扫描读取KEY_BLACK_y的值，若为0，说明(KEY_WHITE_x,KEY_BLACK_y)坐标处的按键被按下
	 *		3. (KEY_WHITE_x,KEY_BLACK_y)坐标映射为键盘上不同的按键值
	 *
	 * */

	//拉高KEY_WHITE_0
	KEY_WITHE_0_LOW();
	KEY_WITHE_1_HIGH();
	KEY_WITHE_2_HIGH();
	if(KEY_BLACK_0_READ() == 0){
		Delay(100);
		if(KEY_BLACK_0_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			Uart1_SendStr("#\r\n");
			strncat(password_key,"#",1);
			password_key_conter++;
			buzzer_tick();
		}
	} else if(KEY_BLACK_1_READ() == 0){
		Delay(100);
		if(KEY_BLACK_1_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			Uart1_SendStr("9\r\n");
			strncat(password_key,"9",1);
			password_key_conter++;
			buzzer_tick();
		}
	} else if(KEY_BLACK_2_READ() == 0){
		Delay(100);
		if(KEY_BLACK_2_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"6",1);
			password_key_conter++;
			Uart1_SendStr("6\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_3_READ() == 0){
		Delay(100);
		if(KEY_BLACK_3_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"3",1);
			password_key_conter++;
			Uart1_SendStr("3\r\n");
			buzzer_tick();
		}
	}
	//拉高KEY_WHITE_1
	KEY_WITHE_1_LOW();
	KEY_WITHE_0_HIGH();
	KEY_WITHE_2_HIGH();
	if(KEY_BLACK_0_READ() == 0){
		Delay(100);
		if(KEY_BLACK_0_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"0",1);
			password_key_conter++;
			Uart1_SendStr("0\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_1_READ() == 0){
		Delay(100);
		if(KEY_BLACK_1_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"8",1);
			password_key_conter++;
			Uart1_SendStr("8\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_2_READ() == 0){
		Delay(100);
		if(KEY_BLACK_2_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"5",1);
			password_key_conter++;
			Uart1_SendStr("5\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_3_READ() == 0){
		Delay(100);
		if(KEY_BLACK_3_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"2",1);
			password_key_conter++;
			Uart1_SendStr("2\r\n");
			buzzer_tick();
		}
	}

	//拉高KEY_WHITE_2
	KEY_WITHE_2_LOW();
	KEY_WITHE_0_HIGH();
	KEY_WITHE_1_HIGH();
	if(KEY_BLACK_0_READ() == 0){
		Delay(100);
		if(KEY_BLACK_0_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			Uart1_SendStr("Please reenter the password!\r\n");
			memset(password_key,'\0',sizeof(password_key));
			password_key_conter = 0;
			buzzer_tick();
		}
	} else if(KEY_BLACK_1_READ() == 0){
		Delay(100);
		if(KEY_BLACK_1_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"7",1);
			password_key_conter++;
			Uart1_SendStr("7\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_2_READ() == 0){
		Delay(100);
		if(KEY_BLACK_2_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"4",1);
			password_key_conter++;
			Uart1_SendStr("4\r\n");
			buzzer_tick();
		}
	} else if(KEY_BLACK_3_READ() == 0){
		Delay(100);
		if(KEY_BLACK_3_READ() == 0){
			//TIM_SetCounter(TIM2,0);
			strncat(password_key,"1",1);
			password_key_conter++;
			Uart1_SendStr("1\r\n");
			buzzer_tick();
		}
	}
	KEY_WITHE_0_HIGH();
	KEY_WITHE_1_HIGH();
	KEY_WITHE_2_HIGH();
}
