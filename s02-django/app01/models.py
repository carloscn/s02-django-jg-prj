from django.db import models

# Create your models here.
# 用户表
class UserInfo(models.Model):
    print("数据库：用户表")
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=16)
    pwd = models.CharField(max_length=16)
    #avatar = models.FileField(upload_to='avatar/', default='static/img/default.jpg')

    def __str__(self):
        return self.name

# 注册表
class Register(models.Model):
    print("数据库：注册表")
    id = models.IntegerField(primary_key=True)
    dev_name = models.CharField(max_length=32,null=True)
    dev_address = models.CharField(max_length=32,null=True)
    # 经纬度
    #dev_script = models.CharField(max_length=32,null=True)
    longitude = models.CharField(max_length=32,null=True)
    latitude = models.CharField(max_length=32,null=True)
    imei = models.CharField(max_length=15,null=True)
    dev_id = models.CharField(max_length=8,null=True)
    dev_id_key = models.CharField(max_length=32,null=True)
    create_time = models.DateTimeField(verbose_name='注册时间', auto_now_add=True,null=True)
    # 外键，外接产品表
    pro = models.ForeignKey(to='Product',to_field='id',on_delete=models.CASCADE,null=True)
    # 外键，外接站点表
    site = models.ForeignKey(to='Site', to_field='id', on_delete=models.CASCADE, null=True)


# 数据表
class Data(models.Model):
    print("数据库：数据表")
    id = models.AutoField(primary_key=True)
    mpu6050_x = models.FloatField(null=True)
    mpu6050_y = models.FloatField(null=True)
    mpu6050_z = models.FloatField(null=True)
    vibrate = models.IntegerField(null=True)
    alarm = models.IntegerField(null=True)
    admin = models.IntegerField(null=True)
    time = models.DateTimeField(verbose_name='时间', auto_now_add=True,null=True)
    # 外键 外接设备注册表
    device = models.ForeignKey(to='Register', to_field='id', on_delete=models.CASCADE, null=True)


# 站点表
class Site(models.Model):
    print("数据库：站点表")
    id = models.IntegerField(primary_key=True)
    name = models.CharField(max_length=20)
    site_script= models.CharField(max_length=64,null=True)



# 状态表
class State(models.Model):
    print("数据库：状态表")
    id = models.AutoField(primary_key=True)
    state = models.CharField(max_length=16,null=True)
    time = models.DateTimeField(verbose_name='时间', auto_now_add=True,null=True)
    # 外键 外接设备注册表
    devid = models.ForeignKey(to='Register', to_field='id', on_delete=models.CASCADE, null=True)


class Product(models.Model):
    print("数据库：产品表")
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=32,null=True)
    pro_key = models.CharField(max_length=32,null=True)
    pro_script = models.CharField(max_length=64,null=True)
    # 外键，外接用户表
    userinfo = models.ForeignKey(to='UserInfo',to_field='id',on_delete=models.CASCADE,null=True)

