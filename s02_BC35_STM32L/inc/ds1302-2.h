/*
 * ds1302.h
 *
 *  Created on: 2018年4月23日
 *      Author: weihaochen
 */

#ifndef DS1302_H_
#define DS1302_H_

#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "stm32l1xx_gpio.h"

#define     uint8       uint8_t
#define     uint16      uint16_t
#define     uint32      uint32_t
#define      BYTE      unsigned char

#define                 ds1302_sec_add                          0x80        //秒数据地址
#define                 ds1302_min_add                          0x82        //分数据地址
#define                 ds1302_hr_add                           0x84        //时数据地址
#define                 ds1302_date_add                         0x86        //日数据地址
#define                 ds1302_month_add                        0x88        //月数据地址
#define                 ds1302_day_add                          0x8a        //星期数据地址
#define                 ds1302_year_add                         0x8c        //年数据地址
#define                 ds1302_control_add                      0x8e        //控制数据地址
#define                 ds1302_charger_add                      0x90
#define                 ds1302_clkburst_add                     0xbe

#define				DS1302_CLK_PORT								GPIOB
#define				DS1302_CLK_PIN								GPIO_Pin_8
#define				DS1302_DAT_PORT								GPIOB
#define				DS1302_DAT_PIN								GPIO_Pin_7
#define				DS1302_RST_PORT								GPIOB
#define				DS1302_RST_PIN								GPIO_Pin_6



#define             DS1302_SCLK_LOW()                 (GPIO_ResetBits(DS1302_CLK_PORT,DS1302_CLK_PIN))
#define             DS1302_SCLK_HIGH()               (GPIO_SetBits(DS1302_CLK_PORT,DS1302_CLK_PIN))

#define             DS1302_SDA_LOW()                 (GPIO_ResetBits(DS1302_DAT_PORT,DS1302_DAT_PIN))
#define             DS1302_SDA_HIGH()                (GPIO_SetBits(DS1302_DAT_PORT,DS1302_DAT_PIN))

#define             DS1302_RST_LOW()                 (GPIO_ResetBits(DS1302_RST_PORT,DS1302_RST_PIN))
#define             DS1302_RST_HIGH()                (GPIO_SetBits(DS1302_RST_PORT,DS1302_RST_PIN))
#define             DS1302_SDA_READ()               (GPIO_ReadInputDataBit(DS1302_RST_PORT,DS1302_RST_PIN))

typedef struct  ds1302_t DS1302;
typedef struct time_format_t ds1302_time;
struct  ds1302_hw_t {

    uint16  sck_pin;
    GPIO_TypeDef *sck_port;
    uint32  sck_periph_clk;

    uint16  sda_pin;
    GPIO_TypeDef *sda_port;
    uint32  sda_periph_clk;

    uint16  rst_pin;
    GPIO_TypeDef *rst_port;
    uint32  rst_periph_clk;

};

struct  time_format_t {


    uint16  year;
    uint16  month;
    uint16  week;
    uint16  day;
    uint16  hour;
    uint16  min;
    uint16  sec;
    BYTE    year_str[4];
    BYTE    month_str[2];
    BYTE    week_str[2];
    BYTE    day_str[2];
    BYTE    hour_str[2];
    BYTE    min_str[2];
    BYTE    sec_str[2];
    BYTE    all_time[60];
};

struct  ds1302_t {

    struct ds1302_t*   self;
    struct ds1302_hw_t hw;
    struct time_format_t time;

    void    (*init)( struct ds1302_t* this );
    void    (*pin_set)( struct ds1302_t* this );
    void    (*reset)( struct ds1302_t* this );
    void    (*write_byte)( struct ds1302_t* this, uint8 addr, uint8 data  );
    BYTE    (*read_byte)( struct ds1302_t* this, uint8 addr );
    void    (*write_time)( struct ds1302_t* this );
    void    (*read_time)( struct ds1302_t* this );

};


extern DS1302* ds1302_new_dev(void);
void    ds1302_init();
void    ds1302_pin_set();
void    ds1302_reset();
void    ds1302_write_byte( uint8 addr, uint8 data );
BYTE    ds1302_read_byte( uint8 addr );
void    ds1302_write_time(ds1302_time time);
void    ds1302_read_time(ds1302_time time);
void    ds1302_hw_set_out();
void    ds1302_hw_set_in();
#endif /* DS1302_H_ */
