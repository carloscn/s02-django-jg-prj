from django.http import HttpResponse
from django.http import JsonResponse
from django.shortcuts import render
import requests
import json
import pymysql


def index(request):
    context = {}
    context['hello1'] = '0.0'
    context['hello2'] = '0.0'
    context['hello3'] = '0.0'
    print("load data ok!")

    return render(request, 'index.html', context)

#设备id(id)	时间(time)	x轴信息(x)	y轴信息(y)	z轴信息(z)	振动状态（vt）	位置信息（gps）	管理员状态(at)
def add(request):
    a = request.GET['a']
    b = request.GET['b']
    c = request.GET['c']
    #print("add function")
    a = float(a)
    b = float(b)
    c = float(c)
    return HttpResponse(str(a + b + c))

def res(request):
    num =  request.GET['s']
    print( num )
    #r0 = requests.get("https://iotda.cn-north-4.myhuaweicloud.com:443/iocm/app/dm/v1.4.0/devices/b12551af-3ee4-4de6-8946-0dd9a32d919a?select=name",cert=('d:/cert/client.cert', 'd:/cert/client.key'),verify = True)
    database_return = read_database(num)
    if database_return == None:
        print("no adpater data in database.")
        return HttpResponse(0)
    number = database_return[0]
    id = database_return[1]
    time = database_return[2]
    x_data = database_return[3]
    y_data = database_return[4]
    z_data = database_return[5]
    vt = database_return[6]
    gps = database_return[7]
    at = database_return[8]
    gps = gps.replace(',','` ')
    back_str = str(id) + ',' + time + ',' + x_data + ',' + y_data + ',' + z_data + ',' + str(vt) + ',' + gps + ',' + str(at)
    print(back_str)
    return HttpResponse(back_str)
    #return HttpResponse(0)

def read_database(number):
    db = pymysql.connect("localhost", "root", "root", "S02DB", charset='utf8')
    # 使用cursor()方法获取操作游标
    cursor = db.cursor()
    sql = 'SELECT * FROM s02table WHERE number = ' + str(number)
    try:
        # 执行sql语句
        cursor.execute(sql)
        # 提交到数据库执行
        db.commit()
        # 5.查看结果
        result = cursor.fetchone()  # 用于返回单条数据
        # results = cursor.fetchall()  # 用于返回多条数据
        print(result)
    except:
        # Rollback in case there is any error
        db.rollback()
        result = None
    # 6.关闭查询
    cursor.close()
    # 关闭数据库
    db.close()

    # 关闭数据库连接
    return result

def axis(request):
    print("thingjs request....")
    number = request.GET["id"]
    print("request number " , number)
    database_return = read_database(number)
    if database_return == None:
        print("no adpater data in database.")
        return HttpResponse(0)
    x_data = database_return[3]
    y_data = database_return[4]
    z_data = database_return[5]
    res = {"x": x_data, "y": y_data, "z":z_data }
    print("return json:", res)
    return HttpResponse(json.dumps(res))
