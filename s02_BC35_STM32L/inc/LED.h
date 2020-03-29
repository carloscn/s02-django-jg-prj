#include <stm32l1xx.h>
void LED_Init(void);
#define LEDMCU_1   GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LEDMCU_0   GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LEDNET_1   GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define LEDNET_0   GPIO_ResetBits(GPIOB,GPIO_Pin_3)