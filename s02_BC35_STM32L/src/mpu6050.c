/*
 * mpu6050.c
 *
 *  Created on: 2020年3月24日
 *      Author: multimicro
 */

#include "mpu6050.h"
#include "usart.h"
#include "string.h"
#include "sw180.h"
#include "key.h"
#include "BC35.h"

unsigned char temp_buf[11];
unsigned char mpu6050_data[100];

float a[3],w[3],angle[3],T;

extern unsigned char bc35_send_data[50];

void mpu6050_init(){
	mpu6050_rec_date_complete = 0;
	mpu6050_rec_date_start = 0;
}

void mpu6050_get_data(){

	if(mpu6050_rec_date_start == 0)
		return;
	mpu6050_rec_date_start = 0;
//	Uart1_SendStr("-------------------------------------------------------\r\n");

	unsigned char Temp[35];
	int i;
	while(mpu6050_rec_date_complete != 1);//等待数据接收完成
	mpu6050_rec_date_complete = 0;
	memcpy(Temp,RxBuffer2,33);
	if(Temp[0]==0x55)       //检查帧头
	{
		for (i = 0; i < 3; ++i) {
			switch(Temp[1 + 11 * i])
			{
			case 0x51: //标识这个包是加速度包
				a[0] = ((short)(Temp[3 + 11 * i]<<8 | Temp[2 + 11 * i]))/32768.0*16;      //X轴加速度
				a[1] = ((short)(Temp[5 + 11 * i]<<8 | Temp[4 + 11 * i]))/32768.0*16;      //Y轴加速度
				a[2] = ((short)(Temp[7 + 11 * i]<<8 | Temp[6 + 11 * i]))/32768.0*16;      //Z轴加速度
				T    = ((short)(Temp[9 + 11 * i]<<8 | Temp[8 + 11 * i]))/340.0+36.25;      //温度
				break;
			case 0x52: //标识这个包是角速度包
				w[0] = ((short)(Temp[3 + 11 * i]<<8| Temp[2 + 11 * i]))/32768.0*2000;      //X轴角速度
				w[1] = ((short)(Temp[5 + 11 * i]<<8| Temp[4 + 11 * i]))/32768.0*2000;      //Y轴角速度
				w[2] = ((short)(Temp[7 + 11 * i]<<8| Temp[6 + 11 * i]))/32768.0*2000;      //Z轴角速度
				T    = ((short)(Temp[9 + 11 * i]<<8| Temp[8 + 11 * i]))/340.0+36.25;      //温度
				break;
			case 0x53: //标识这个包是角度包
				angle[0] = ((short)(Temp[3 + 11 * i]<<8| Temp[2 + 11 * i]))/32768.0*180;   //X轴滚转角（x 轴）
				angle[1] = ((short)(Temp[5 + 11 * i]<<8| Temp[4 + 11 * i]))/32768.0*180;   //Y轴俯仰角（y 轴）
				angle[2] = ((short)(Temp[7 + 11 * i]<<8| Temp[6 + 11 * i]))/32768.0*180;   //Z轴偏航角（z 轴）
				T        = ((short)(Temp[9 + 11 * i]<<8| Temp[8 + 11 * i]))/340.0+36.25;   //温度
				//printf("X轴角度：%.2f   Y轴角度：%.2f   Z轴角度：%.2f\r\n",angle[0],angle[1],angle[2]);
				break;
			default:  break;
			}
		}

//		sprintf(mpu6050_data,"ACC: X %-3.2f  Y %3.2f  Z %3.2f\r\n"
//				"RAD: X %-3.2f  Y %3.2f  Z %3.2f\r\n"
//				"ANG: X %-3.2f  Y %3.2f  Z %3.2f\r\n",a[0],a[1],a[2],w[0],w[1],w[2],angle[0],angle[1],angle[2]);

		sprintf(mpu6050_data,"ANG: X %3.1f  Y %3.1f  Z %3.1f\r\n",angle[0],angle[1],angle[2]);
		Uart1_SendStr(mpu6050_data);

		sprintf(bc35_send_data + 14,"%04d", (int)((angle[0] + 180.0) * 10));

		sprintf(bc35_send_data + 18,"%04d", (int)((angle[1] + 180.0) * 10));

		sprintf(bc35_send_data + 22,"%04d", (int)((angle[2] + 180.0) * 10));


		//SW180振动数据
		if (sw180_status == SW180_VIBRATE_OFF) {
			strncat(bc35_send_data + 26,"00",2);
		} else {
			strncat(bc35_send_data + 26,"11",2);
		}
		//报警数据
		if (sw180_status == SW180_VIBRATE_OFF) {
			strncat(bc35_send_data + 28,"00",2);
		} else {
			strncat(bc35_send_data + 28,"11",2);
		}
		//管理员模式
		if (admin_status == ADMIN_STATUS_OFF) {
			strncat(bc35_send_data + 30,"00",2);
		} else {
			strncat(bc35_send_data + 30,"11",2);
		}

		Uart1_SendStr(bc35_send_data);
		Uart1_SendStr("\r\n");
		BC95_Senddata(16,bc35_send_data);
		sw180_status = SW180_VIBRATE_OFF;
	}
	Uart1_SendStr("-------------------------------------------------------\r\n");

}
