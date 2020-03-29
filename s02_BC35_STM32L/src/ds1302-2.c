/*
 * ds1302.c
 *
 *  Created on: 2018年4月23日
 *      Author: weihaochen
 */
#include "ds1302-2.h"
#include "usart.h"

//初始时间定义

BYTE    time_buf[8] = {0x20,0x10,0x09,0x14,0x23,0x59,0x50,0x02};//初始时间
BYTE    readtime[14];//当前时间
uint16  sec_buf=0;  //秒缓存
bool    sec_flag=0; //秒标志位


void    ds1302_init()
{
	ds1302_pin_set();

	DS1302_RST_LOW();
	DS1302_SCLK_LOW();
}

void    ds1302_pin_set()
{

	GPIO_InitTypeDef io_cfg;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	io_cfg.GPIO_Pin     =  DS1302_CLK_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_OUT;
	io_cfg.GPIO_OType 	= 	GPIO_OType_PP;
	//	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_NOPULL;
	//    io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(DS1302_CLK_PORT, &io_cfg );

	io_cfg.GPIO_Pin     =  DS1302_DAT_PIN;
	GPIO_Init(DS1302_DAT_PORT, &io_cfg );

	io_cfg.GPIO_Pin     =  DS1302_RST_PIN;
	GPIO_Init(DS1302_RST_PORT, &io_cfg );

}


void    ds1302_reset()
{
	DS1302_RST_LOW();
}


void    ds1302_write_byte(uint8 addr, uint8 data )
{
	unsigned char   i;
	DS1302_RST_HIGH();

	addr    =   addr    &   0xFE;
	// Write address;
	for( i = 0; i < 8; i++ ) {
		if( addr & 0x01 ) {
			DS1302_SDA_HIGH();
		}else {
			DS1302_SDA_LOW();
		}
		DS1302_SCLK_HIGH();
		DS1302_SCLK_LOW();
		addr = addr >> 1;
	}
	// Write data;
	for( i = 0; i < 8; i++ ) {
		if( data & 0x01 ) {
			DS1302_SDA_HIGH();
		}else {
			DS1302_SDA_LOW();
		}
		DS1302_SCLK_HIGH();
		DS1302_SCLK_LOW();
		data = data >> 1;
	}
	DS1302_RST_LOW();

}

BYTE    ds1302_read_byte( uint8 addr )
{
	BYTE    i,temp;

	DS1302_RST_HIGH();
	addr = addr | 0x01;
	for( i = 0; i < 8; i++ ) {
		if( addr & 0x01 ) {
			DS1302_SDA_HIGH();
		}else {
			DS1302_SDA_LOW();
		}
		DS1302_SCLK_HIGH();
		DS1302_SCLK_LOW();
		addr >>= 1;

	}
	ds1302_hw_set_in();
	for( i = 0; i < 8; i++ ) {
		temp  >>= 1;
		if( DS1302_SDA_READ() ) {
			temp    |=  0x80;
		}else {
			temp    &=  0x7F;
		}
		DS1302_SCLK_HIGH();
		DS1302_SCLK_LOW();
	}
	ds1302_hw_set_out();
	DS1302_RST_LOW();
	return temp;

}
void    ds1302_write_time(ds1302_time time)
{

	ds1302_hw_set_out();
	ds1302_write_byte(ds1302_control_add,0x00);         //关闭写保护
	ds1302_write_byte(ds1302_sec_add,0x80);             //暂停时钟
	ds1302_write_byte(ds1302_year_add,time.year);     //年
	ds1302_write_byte(ds1302_month_add,time.month);    //月
	ds1302_write_byte(ds1302_date_add,time.day);     //日
	ds1302_write_byte(ds1302_hr_add,time.hour);       //时
	ds1302_write_byte(ds1302_min_add,time.min);      //分
	ds1302_write_byte(ds1302_sec_add,time.sec);      //秒
	ds1302_write_byte(ds1302_day_add,time.week);      //周
	ds1302_write_byte(ds1302_control_add,0x80);         //打开写保护
}

void    ds1302_read_time(ds1302_time time)
{

	time_buf[1] = ds1302_read_byte(ds1302_year_add);      //年

	time_buf[2] = ds1302_read_byte(ds1302_month_add);     //月

	time_buf[3] = ds1302_read_byte(ds1302_date_add);      //日

	time_buf[4] = ds1302_read_byte(ds1302_hr_add);        //时

	time_buf[5] = ds1302_read_byte(ds1302_min_add);       //分

	time_buf[6] = (ds1302_read_byte(ds1302_sec_add))&0x7f;//秒，屏蔽秒的第7位，避免超出59

	time_buf[7] = ds1302_read_byte(ds1302_day_add);       //周


	// Deal year;
	time.year     =   (time_buf[0] >> 4)  * 1000 + \
			(time_buf[0] & 0xF) * 100 + \
			(time_buf[1] >> 4)  * 10 + \
			(time_buf[1] & 0xF) * 1;
	itoa( time.year, time.year_str, 4 );


	time.month    =   (time_buf[2] >> 4)  * 10 + \
			(time_buf[2] & 0xF) *1;
	itoa( time.month, time.month_str,2 );


	time.day    =     (time_buf[3] >> 4)  * 10 + \
			(time_buf[3] & 0xF) *1;
	itoa( time.day, time.day_str, 2 );


	time.hour    =    ((time_buf[4] >> 4) & 0xF)  * 10 + \
			(time_buf[4] & 0xF) *1;
	itoa( time.hour, time.hour_str, 2 );

	time.min    =     (time_buf[5] >> 4)  * 10 + \
			(time_buf[5] & 0xF) *1;
	itoa( time.min, time.min_str, 2 );

	time.sec    =     (time_buf[6] >> 4)  * 10 + \
			(time_buf[6] & 0xF) *1;
	itoa( time.sec, time.sec_str, 2 );


	time.week   =     (time_buf[7] >> 4)  * 10 + \
			(time_buf[7] & 0xF) *1;
	itoa( time.week, time.week_str, 2 );


	sprintf( time.all_time,    \
			"time: %d-%d-%d %d:%d:%d week:%d \n" , \
			time.year,   \
			time.month,  \
			time.day,    \
			time.hour,   \
			time.min,    \
			time.sec,    \
			time.week   );
	Uart1_SendStr(time.all_time);
}
/*
 * --------------------------------
 * 1. SCK   -    PB8
 * 2. DAT   -    PB7
 * 3. RST   -    PB6
 * */


void    ds1302_hw_set_in()
{
	GPIO_InitTypeDef io_cfg;
	io_cfg.GPIO_Pin     =  DS1302_DAT_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_IN;
//	io_cfg.GPIO_OType 	= 	GPIO_OType_OD;
//	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_NOPULL;
//	io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(DS1302_DAT_PORT, &io_cfg );

}

void    ds1302_hw_set_out()
{
	GPIO_InitTypeDef io_cfg;
	io_cfg.GPIO_Pin     =  DS1302_DAT_PIN;
	io_cfg.GPIO_Mode    =   GPIO_Mode_OUT;
	io_cfg.GPIO_OType 	= 	GPIO_OType_PP;
	//	io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_NOPULL;
	//    io_cfg.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	//    io_cfg.GPIO_Speed   =   GPIO_Speed_40MHz;
	GPIO_Init(DS1302_DAT_PORT, &io_cfg );
}
