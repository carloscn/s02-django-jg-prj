#include "led.h"
void LED_Init(void)
{		
	GPIO_InitTypeDef   GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_SetBits(GPIOB,GPIO_Pin_2);

}
