import configparser
import os
from .ClientInfo import ClientInfo
from .DictUtil import DictUtil

cf = configparser.ConfigParser()


class Constant(object):

    def __init__(self):
        self.Info = ClientInfo()
        self.workPath = os.path.join('./')

    def readCertificate(self):
        certFilePath = os.path.join(self.workPath, 'cert/client.crt')
        certFilePath2 = os.path.join(self.workPath, 'cert/client.key')
        cert = (certFilePath, certFilePath2)
        return cert

    def readConfFile(self):
        configFilePath = os.path.join(self.workPath, 'application.ini')
        print("ready to read")
        dat = cf.read(configFilePath)
        print(dat)
        print("ready to read " + configFilePath)
        platformIp = cf.get("CLIENT_INFO", "platformIp")
        platformPort = cf.get("CLIENT_INFO", "platformPort")
        appId = cf.get("CLIENT_INFO", "appId")
        print("appId" + appId)
        secret = cf.get("CLIENT_INFO", "secret")
        # print("secret" + secret)
        return platformIp, platformPort, appId, secret

    def clientInfo(self):
        ret = self.readConfFile()
        # print(ret)
        self.Info.setPlatformIp(ret[0])
        self.Info.setPlatformPort(ret[1])
        self.Info.setAppId(ret[2])
        self.Info.setSecret(ret[3])
        self.Info = DictUtil.dto2dict(self.Info)
        return self.Info

    # def clientInfo(self):
    #     clientInfo = ClientInfo()
    #     clientInfo.platformIp = (Constant().readConfFile())[0]
    #     clientInfo.platformPort = (Constant().readConfFile())[1]
    #     clientInfo.appId = (Constant().readConfFile())[2]
    #     clientInfo.secret = (Constant().readConfFile())[3]
    #     clientInfo = DictUtil.dto2dict(clientInfo)
    #     return clientInfo

    ######################################------------ Authentication ------------######################################
    #####################################------------ DeviceManagement ------------#####################################
    #######################################------------ BatchProcess ------------#######################################
    ######################################------------ RuleEngine ------------##########################################
    #################################------------ SubscriptionManagement ------------###################################
    #################################------------ DeviceServiceInvocation ------------##################################
    ####################################------------ SignalDelivery ------------########################################
    ######################################------------ DataCollection ------------######################################
    ##################################------------ DeviceGroupManagement ------------###################################
    ######################################------------ DeviceUpgrade ------------#######################################
    ###################################------------ PushMessageReceiver ------------####################################

# if __name__=="__main__":
#     Constant = Constant()
#     ret = Constant.clientInfo()
#     print(ret)