# -*- coding: utf-8 -*-

import json
import socket
import ctypes
from typing import Union
import pymysql
import datetime
import binascii
import string
import re
import time
import os
import time
import struct
import hashlib
from . import coap

class server():

    def __init__(self):
        self.event_time
        self.event_time_old

    def init_database(self):
        # 打开数据库连接
        db = pymysql.connect("localhost", "root", "root", "orm", charset='utf8')
        # 使用cursor()方法获取操作游标
        cursor = db.cursor()
        # 使用execute方法执行SQL语句
        cursor.execute("select * from s02table")
        # 使用 fetchone() 方法获取一条数据
        data = cursor.fetchone()
        print("Database return : ", data)
        self.write_database(self,"12345",'2020/02/03/12:45:36','12.2578', '25.3658', '125.2256', '0', '12.56565,121.4484847', '1')
        # 关闭数据库连接
        db.close()

    def init_network(self):
        self.event_time_old = "20200413"

    def write_database(self, time, x, y, z, vt, al, at, dev_id):
        # 打开数据库连接
        db = pymysql.connect("localhost", "root", "root", "orm", charset='utf8')
        # 使用cursor()方法获取操作游标
        cursor = db.cursor()
        cursor.execute("select * from app01_data order by id desc limit 0,1")
        data = cursor.fetchone()
        print("Database return : ", data)
        if data == None:
            id = "1"
        else:
            id = str(data[0] + 1)
        devid = "1"
        print(time)
        sql_1 = "INSERT INTO app01_data (dev_id, mpu6050_x, mpu6050_y,mpu6050_z,vibrate,alarm,admin,time,device_id)\n"
        sql_2 = "\tVALUES\n("
        sql_3 = '"' + dev_id + '"' + "," + \
                x + "," +  \
                y + "," +  \
                z + "," + \
                vt + "," + \
                al + "," + \
                at + "," + \
                '"' + time + '"' + "," +\
                devid + ")"
        sql = sql_1 + sql_2 + sql_3
        print("do sql> " + sql)
        try:
            # 执行sql语句
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
        except:
            print("写入数据库失败")
            # Rollback in case there is any error
            db.rollback()
        # 关闭数据库连接
        db.close()

    def run_server(self):
        while(1):
            times = time.strftime("%Y/%m/%d/%H:%M:%S", time.localtime(time.time()))
            print(times)
            coap_data = coap.get_iot_data()
            # print(coap_data)
            coap_data = json.loads(json.dumps(coap_data))
            self.event_time = coap_data['services'][0]['eventTime']
            if self.event_time_old != self.event_time:
                self.event_time_old = self.event_time
                self.process_rec_data(self,coap_data)
            time.sleep(1)
            # pass

    def process_rec_data(self,data):
        deviceId = data['deviceId']
        print(deviceId)
        x_value = float(data['services'][0]['data']['MPU6050_x'])/10.0
        y_value = float(data['services'][0]['data']['MPU6050_y'])/10.0
        z_value = float(data['services'][0]['data']['MPU6050_z'])/10.0
        vibrate = data['services'][0]['data']['Vibirate']
        alarm = data['services'][0]['data']['Alarm']
        admin = data['services'][0]['data']['Admin']

        print("x value:", x_value)
        print("y value:", y_value)
        print("z value:", z_value)
        print(vibrate)
        print(alarm)
        print(admin)

        id = str(hashlib.md5(b'12345').hexdigest())
        print("md5 id: " + id)
        times = time.strftime("%S", time.localtime(time.time()))
        id = times
        times = time.strftime("%Y/%m/%d/%H:%M:%S", time.localtime(time.time()))
        #  def write_database(self, id, time, x, y, z, vt, gps, at):
        self.write_database(self, times, str(x_value), str(y_value), str(z_value), str(vibrate),  str(alarm), str(admin), str(deviceId))



