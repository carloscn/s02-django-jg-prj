#include "usart.h"
#include <stm32l1xx.h>
void Clear_Buffer(void);//清空缓存	
void BC95_Init(void);
void BC95_PDPACT(void);
void BC95_ConUDP(void);
void BC95_RECData(void);
void BC95_Senddata(uint8_t len,uint8_t *data);
typedef struct
{
   uint8_t CSQ;    
   uint8_t Socketnum;   //编号
   uint8_t reclen;   //获取到数据的长度
   uint8_t res;      
   uint8_t recdatalen[10];
   uint8_t recdata[100];
} BC95;
