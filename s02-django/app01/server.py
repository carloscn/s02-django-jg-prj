import socket
import json
from app01.models import Register, Site, Data, Product,State
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# 绑定端口:
# 假设字段{'pro_key':'add0fff2d6652fc09ad973a86fb73516',
#         'dev_key':'99059523ea1a63c53b14fa70ecd488b',
#         'dev_id':1,
#         'tmp':34,
#         'hum':28
#         'pm10':14,
#         'pm25':20
#         'state':1}
s.bind(('127.0.0.1', 9999))
while True:
    data,client_addr = s.recvfrom(2048)
    data = json.loads(data)
    pro_key = data['pro_key']
    dev_key = data['dev_key']
    dev_id = data['dev_id']
    tmp = data['tmp']
    hum = data['hum']
    pm10 = data['pm10']
    pm25 = data['pm25']
    state = data['state']


    pro_list = Product.objects.all()
    dev_list = Register.objects.all()
    dev = Register.objects.get(id = dev_id)

    if state == 1:
        state="在线"
    else:
        status="离线"

    for pro in pro_list:
        if pro.pro_key == pro_key:
            for dev in dev_list:
                if dev.dev_id_key == dev_key:
                    Data.objects.create(tmp = tmp,hum=hum,pm10=pm10,pm25=pm25)
                    State.objects.create(state = state,devid = dev)

    s.sendto(data.upper(),client_addr)
server.close()
