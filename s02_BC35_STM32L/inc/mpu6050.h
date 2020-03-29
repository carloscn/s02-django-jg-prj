/*
 * mpu6050.h
 *
 *  Created on: 2020Äê3ÔÂ24ÈÕ
 *      Author: multimicro
 */

#ifndef MPU6050_H_
#define MPU6050_H_

int mpu6050_rec_date_complete;
int mpu6050_rec_date_start;


void mpu6050_init();
void mpu6050_get_data();

#endif /* MPU6050_H_ */
