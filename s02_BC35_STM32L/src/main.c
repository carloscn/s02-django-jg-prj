/**
 ******************************************************************************
 * @file    Project/STM32L1xx_StdPeriph_Templates/main.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    16-May-2014
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <BC35.h>
#include "main.h"
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "ds1302-2.h"
#include "mpu6050.h"
#include "buzzer.h"
#include "key.h"
#include "sw180.h"
GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;
//***与服务器进行交互，模块可以通过UDP方式传数据到服务器端，服务器也可以支持下发数据到设备端进行显示打印*****************/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
/** @addtogroup Template_Project
 * @{
 */

DS1302* ds1302;
ds1302_time time;
/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */

#define		DEIVCE_ID	0x00
extern unsigned char bc35_send_data[50];
unsigned char bc35_send_data_tmp[20];

int main(void)
{
	//	SystemInit();
	if (SysTick_Config(SystemCoreClock / 1000))//设置24bit定时器 1ms中断一次
	{
		/* Capture error */
		while (1);
	}
	uart_init(115200);
	uart2_init(115200);
	uart3_init(9600);
	TIM3_Int_Init(99,3199);//10ms中断一次
	TIM2_Int_Init(9999,3199);//1000ms中断一次
	Uart1_SendStr("start init BC35...\n");
	//	while(strstr(RxBuffer,"OK") == NULL);
	Delay(1000);
	Uart1_SendStr("1...\n");
	Delay(1000);
	Uart1_SendStr("2...\n");
	Delay(1000);
	Uart1_SendStr("3...\n");
	Delay(1000);
	Uart1_SendStr("4...\n");
	Delay(1000);
	Uart1_SendStr("5...\n");
	Delay(1000);
	Uart1_SendStr("6...\n");
	Delay(1000);
	Uart1_SendStr("7...\n");
	Delay(1000);
	Uart1_SendStr("8...\n");


	BC95_Init();
	BC95_PDPACT();
	BC95_ConUDP();
	Uart1_SendStr("Hello BC35\n");
	mpu6050_init();
	LED_Init();
	buzzer_init();
	key_init();
	sw180_init();
	//	ds1302->time.year = 2020;
	//	ds1302->time.month = 10;
	//	ds1302->write_time(ds1302);
	set_password(1234);
	memset(bc35_send_data,'\0',sizeof(bc35_send_data));
	strncat(bc35_send_data,"AF1869BF3930",12);//固定数据，勿动！
	strncat(bc35_send_data,"00",2);//设备号，两位
	Uart1_SendStr(bc35_send_data);
	Uart1_SendStr("\r\n");

	while (1)
	{
		key_scan();
		verify_password();
		mpu6050_get_data();
	}
}



/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}
#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
