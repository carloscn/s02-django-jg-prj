/*
 * sw180.c
 *
 *  Created on: 2020年3月25日
 *      Author: multimicro
 */
#include"sw180.h"
#include "usart.h"
#include "buzzer.h"

void sw180_init(){

	sw180_status = SW180_VIBRATE_OFF;
	sw180_filter = 0;
	EXTI_Config();
}

void sw180_scan(){

}


static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 配置NVIC为优先级组1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* 配置中断源：按键1 */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI3_IRQn;
	/* 配置抢占优先级 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

/**
 * @brief  配置 IO为EXTI中断口，并设置中断优先级
 * @param  无
 * @retval 无
 */
void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//注意要打开SYSCFG时钟

	/* 配置 NVIC 中断*/
	NVIC_Configuration();

	/*--------------------------配置引脚-----------------------------*/
	/* 选择按键用到的GPIO */
	GPIO_InitStructure.GPIO_Pin =  SW180_15P_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	//GPIO_Initstructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init( SW180_15P_PORT, &GPIO_InitStructure);


	/* -------------选择EXTI的信号源 -------------*/
	SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOB,  GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line =  EXTI_Line3;

	/* EXTI为中断模式 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling
	/* 使能中断 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		sw180_filter ++;
		if (sw180_filter > 10) {
			sw180_filter = 0;
			sw180_status = SW180_VIBRATE_ON;
			BUZZER_ON();
			Uart1_SendStr("WARRING: SW180在振动！\r\n");
			BUZZER_OFF();
		}
	}
}
