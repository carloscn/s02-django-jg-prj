# -*- coding: utf-8 -*-

import sys
import socket
import ctypes
from typing import Union
from HexConver import HexConvert as hexc
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

class server():
    # threading info
    target_ip = ""
    target_port = 8080
    local_ip = ""
    local_port = 8888
    udp_socket = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

    HOST = "0.0.0.0"
    PORT = 12345
    BUFSIZ = 1024
    ADDR = (HOST, PORT)


    def init_database(self):
        # 打开数据库连接
        db = pymysql.connect("localhost", "root", "root", "S02DB", charset='utf8')
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
        pass

    def write_database(self, id, time, x, y, z, vt, gps, at):
        # 打开数据库连接
        db = pymysql.connect("localhost", "root", "root", "S02DB", charset='utf8')
        # 使用cursor()方法获取操作游标
        cursor = db.cursor()

        sql_1 = "INSERT INTO s02table (id, time, x, y, z, vt, gps, at)\n"
        sql_2 = "\tVALUES\n("
        sql_3 = '"' + id + '"' + "," + \
                '"' + time + '"' + "," + \
                '"' + x + '"' + "," +  \
                '"' + y + '"' + "," +  \
                '"' + z + '"' + "," + \
                vt  + "," + \
                '"' + gps + '"' + "," + \
                at + ")"
        sql = sql_1 + sql_2 + sql_3
        print("do sql> " + sql)
        try:
            # 执行sql语句
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
        except:
            # Rollback in case there is any error
            db.rollback()
        # 关闭数据库连接
        db.close()

    def run_server(self):
        dataCounter = 0
        self.init_database(self)
        self.udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.udp_socket.bind(self.ADDR)

        excelname = time.strftime("%Y-%m-%d-%H_%M_%S", time.localtime(time.time())) + '.xls'
        currenttime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time.time()))
        print(currenttime)
        while(1):
            # print 'Waiting for message from BC95...'
            data, addr = self.udp_socket.recvfrom(1024)
            #readstr = str(binascii.b2a_hex(data))  # 把接收到的数据转为字符型
            data_str = hexc.bytesToHexString(data).replace(" ", "")
            currenttime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time.time()))
            print(currenttime)
            print(data_str)
            self.process_rec_data(self, data_str)
            # BC95通过电信云接收的数据格式为
            #  df68ff97907e  00  1111  2222  3333  00  11  00
            # |------------||--||----||----||----||--||--||--|
            #     (ignro)    ID  xxxx  yyyy  zzzz  zd  bj  ad
            #    固定12位                          zd: 振动数据
            #                                      bj: 报警数据
            #                                      ad: 管理员权限
        self.udp_socket.close()

    def process_rec_data(self,data):
        x_value = float(data[14:18])/10.01111
        y_value = float(data[18:22])/10.01111
        z_value = float(data[22:26])/10.01111
        v_state = int(data[-3])
        a_state = int(data[-1])
        print("x value: " + str(x_value))
        print("y value:", y_value)
        print("z value:", z_value)

        id = str(hashlib.md5(b'12345').hexdigest())
        print("md5 id: " + id)
        id = "12346"
        times = time.strftime("%Y/%m/%d/%H:%M:%S", time.localtime(time.time()))
        gps = "114.51114,37.095344"
        #  def write_database(self, id, time, x, y, z, vt, gps, at):
        self.write_database(self, id, times, str(x_value), str(y_value), str(z_value), str(v_state),  gps, str(a_state))



