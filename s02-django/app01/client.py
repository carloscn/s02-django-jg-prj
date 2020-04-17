from socket import *
c = socket(AF_INET,SOCK_DGRAM)

while True:
    msg = input('>>:').strip()
    c.sendto(msg.encode('utf-8'),('127.0.0.1',9999))
    data,server_addr = c.recvfrom(1024)
    print(data,server_addr)

c.close()