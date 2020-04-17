import requests
import json,os
from . import Constant
from . import RestConstant
from . import ClientInfo

# deviceId = "ebc7ae16-7e95-4ee9-80b9-8442339fbcbd"

def send_iot_command():
    deviceId = "a6d43cf0-dec0-4db6-bba3-991adcf24092"
    appId = "BASX4yKSxBvr5K2OIcs22De0yIMa"
    secret = "avV6p8rrwG0FRKhyddRpLXP6Lqka"

    post_url =  "https://49.4.92.191:8743/iocm/app/sec/v1.1.0/login"
    #print("post_url: " + post_url)
    payload = {
        'appId': appId,
        'secret': secret
    }
    headers = {
        'Content-Type': 'application/x-www-form-urlencoded'
    }
    # cert = Info.readCertificate()
    currentPath = os.getcwd()
    workPath = os.path.join(currentPath,'huawei')
    print(workPath)
    certFilePath = os.path.join(workPath, 'cert\client.crt')
    certFilePath2 = os.path.join(workPath, 'cert\client.key')
    cert = (certFilePath, certFilePath2)
    print(cert)
    # cert = ('cert/client.crt','cert/client.key')
    response = requests.request("POST",post_url, headers=headers, data=payload, cert=cert,verify=False, timeout=10)

    #print(response.text)
    accessToken = json.loads(response.text)['accessToken']
    #print("accessToken: " + accessToken)

    getUrl = "https://49.4.92.191:8743/iocm/app/cmd/v1.4.0/deviceCommands"
    print("getUrl: " + getUrl)
    headers = {
        "app_key": appId,
        "Authorization": "Bearer " + accessToken,
        "Content-Type": "application/json"
    }
    payload = {
        "callbackUrl": None,
        "deviceId": deviceId,
        "command": {
            "method": "bc35_ctrl",
            "serviceId": "ManholeCover",
            "paras": {
                "SendData":"1"
            }
        },
        "expireTime": 0,  # 必须为0，否则发送模式为缓冲下发，NB设备不能及时收到消息
        "maxRetransmit": None
    }
    payload = json.dumps(payload)
    print(payload)
    response = requests.request("POST",getUrl, headers=headers, data=payload, cert=cert, verify=False, timeout=10)
    responseData = json.loads(response.text)
    print(responseData)
    return responseData

if __name__=="__main__":
    # get_iot_data()
    send_iot_command()