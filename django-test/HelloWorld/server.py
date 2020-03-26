# coding=utf-8

from socket import *
import sqlite3
import json
import time
import os
import string
import re
import urllib.request
import urllib.parse
import ssl

class server():
    tcp_server = socket(AF_INET, SOCK_STREAM)  # 开启套接字
    host = "127.0.0.1"
    port = 6000
    def __init__(self):
        self.init_socket_server()

    def init_socket_server(self):
        print("socket: server init")
        self.tcp_server = socket(AF_INET, SOCK_STREAM)  # 开启套接字
        self.tcp_server.bind( self.host, self.port )
        self.tcp_server.listen(5)
        print("socket: server listen to " + self.host)

    def init_sqlite_database(self):

        con = sqlite3.connect("DEMO.db")
        cur = con.cursor()
        sql = "CREATE TABLE IF NOT EXISTS dbs(id INTEGER PRIMARY KEY,time TEXT,x TEXT,y TEXT, z TEXT, vt BOOL, gps TEXT, at BOOL)"
        cur.execute(sql)

    def test(self):
        print("test function.")



