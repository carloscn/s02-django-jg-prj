from django.shortcuts import render, HttpResponse, redirect
from django.contrib import auth
from django.http import JsonResponse
from app01.tools.valid_code import get_valid_code_img
from app01.models import Register, Site, Data, Product
from app01.myforms import UserForm
from app01.models import UserInfo
import json
import hashlib
from huawei.coap import  send_iot_command


# Create your views here.
# 登录
def login(request):
    if request.method == 'GET':
        print("login")
        return render(request, 'login.html')
    else:
        print("login**")
        response = {'user': None, 'msg': None}
        user = request.POST.get("user")
        pwd = request.POST.get("pwd")
        valid_code = request.POST.get('valid_code')
        request.session["user"] = user
        mysql_user = UserInfo.objects.filter(name=user, pwd=pwd).first()
        valid_code_str = request.session.get("valid_code_str")
        if mysql_user:
            response['user'] = mysql_user.name
        else:
            response["msg"] = "用户名或密码错误"
        return HttpResponse(json.dumps(response))
        # if valid_code.upper() == valid_code_str.upper():
        #     pass
        # else:
        #     response["msg"] = "验证码错误"
        return JsonResponse(response)


# 验证码生成
def get_validCode_img(requset):
    data = get_valid_code_img(requset)
    return HttpResponse(data)


# 注册用户
def register_user(requset):
    print("***********注册用户************")
    if requset.is_ajax():
        form = UserForm(requset.POST)
        response = {'user': None, 'msg': None}
        if form.is_valid():
            response['user'] = form.cleaned_data.get('user')
            #    生成一条用户记录
            user = form.cleaned_data.get('user')
            print(user)
            pwd = form.cleaned_data.get('pwd')
            avatar_obj = requset.FILES.get('avatar')
            if avatar_obj:
                print("账号注册-有avatar")
                user_obj = UserInfo.objects.create(name=user, pwd=pwd, avatar=avatar_obj)
            else:
                print("账号注册-无avatar")
                user_obj = UserInfo.objects.create(name=user, pwd=pwd)

        else:
            response['msg'] = form.errors
        return JsonResponse(response)
    form = UserForm()
    return render(requset, "user_register.html", {'form': form})


# 退出登录
def logout(request):
    auth.logout(request)  # request.session.flush()
    redirect('/app01/login/')


# 注册产品
def register_product(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        h1 = hashlib.md5()
        str = name + 'xttciot'
        h1.update(str.encode(encoding='utf-8'))
        pro_key = h1.hexdigest()
        script = request.POST.get('script')
        userinfo =  request.session.get("user")
        user = UserInfo.objects.filter(name = userinfo).first()
        a = UserInfo.objects.get(id=user.id)
        Product.objects.create(name=name, pro_key=pro_key, pro_script=script, userinfo=a)
        return redirect("/app01/checktpro/")
    return render(request, 'product_register.html')


# 查看产品
def check_product(request):
    userinfo = request.session.get("user")
    user = UserInfo.objects.filter(name=userinfo).first()
    a = UserInfo.objects.get(id = user.id)
    product_list = Product.objects.filter(userinfo=a).all()
    print(product_list)
    return render(request, 'main.html', {'product_list': product_list})


# 编辑产品
def change_product(request, id):
    edit_pro_obj = Product.objects.filter(pk=id).first()
    if request.method == "POST":
        id = request.POST.get('id')
        name = request.POST.get('name')
        script = request.POST.get('script')
        h1 = hashlib.md5()
        str = name + 'xttciot'
        h1.update(str.encode(encoding='utf-8'))
        pro_key = h1.hexdigest()
        Product.objects.filter(id=id).update(id=id, name=name, pro_key=pro_key, pro_script=script)
        # 重定向
        return redirect("/app01/first/")
    return render(request, "change_product.html", {'edit_pro_obj': edit_pro_obj})


def del_product(request, id):
    Product.objects.filter(id=id).delete()
    return redirect("/app01/checktpro/")


# 注册站点
def resite(request):
    if request.method == 'GET':
        return render(request, 'site_register.html')
    else:
        id = request.POST.get('id')
        name = request.POST.get('name')
        script = request.POST.get('script')

        Site.objects.create(id=id, name=name, site_script=script)
        return render(request, 'site_register.html')


# 查看站点
def check_site(request):
    site_list = Site.objects.all()
    return render(request, 'show_site.html', {'site_list': site_list})


# 删除站点
def delsite(request, id):
    Site.objects.filter(id=id).delete()
    return redirect("/app01/checksite/")


# 编辑站点
def change_site(request, id):
    edit_site_obj = Site.objects.filter(pk=id).first()
    if request.method == "POST":
        id = request.POST.get('siteid')
        name = request.POST.get('name')
        script = request.POST.get('script')
        Site.objects.filter(id=id).update(id=id, name=name, site_script=script)
        # 重定向
        return redirect("/app01/checksite/")
    return render(request, "change_site.html", {'edit_site_obj': edit_site_obj})


# 设备注册
def register(request):
    if request.method == "POST":
        # id = request.POST.get('id')
        name = request.POST.get('name')
        address = request.POST.get('address')
        # 经纬度
        longitude = request.POST.get('longitude')
        latitude = request.POST.get('latitude')
        imei = request.POST.get('imei')
        dev_id = request.POST.get('dev_id')
        siteid = request.POST.get('site_list')
        h2 = hashlib.md5()
        str = imei + dev_id
        h2.update(str.encode(encoding='utf-8'))
        dev_id_key = h2.hexdigest()
        pro = "bc35"
        print("pro: " + pro)

        pro1 = Product.objects.get(name = pro)
        print("pro1")
        print(pro1)

        Register.objects.create(dev_name=name, dev_address=address,
                                longitude=longitude, imei=imei, latitude=latitude, dev_id=dev_id, site_id=siteid,
                                dev_id_key=dev_id_key
                                , pro=pro1)
        print("pro: " + pro)
    site_list = Site.objects.all()
    return render(request, "device_register.html", {"site_list": site_list})


# 登录
def first(request):
    product_list = Product.objects.all()
    device_list = Register.objects.all()
    return render(request, 'main.html', {'product_list': product_list,'device_list': device_list})


# 查看设备
def check(request):
    device_list = Register.objects.all()
    return render(request, 'show_device.html', {'device_list': device_list})


def check_device_status(requset):
    return render(requset, 'dev_status.html')


# 删除设备
def deldevice(request, id):
    Register.objects.filter(id=id).delete()
    return redirect("/app01/check/")


# 编辑设备
def changedevice(request, id):
    site_list = Site.objects.all()
    edit_device_obj = Register.objects.filter(pk=id).first()
    if request.method == "POST":
        id = request.POST.get('id')
        name = request.POST.get('name')
        address = request.POST.get('address')
        longitude = request.POST.get('longitude')
        latitude = request.POST.get('latitude')
        imei = request.POST.get('imei')
        print(imei)
        dev_id = request.POST.get('dev_id')
        h2 = hashlib.md5()
        str = imei + dev_id
        h2.update(str.encode(encoding='utf-8'))
        dev_id_key = h2.hexdigest()
        siteid = request.POST.get('site_list')
        Register.objects.filter(id=id).update(id=id, site_id=siteid, latitude=latitude, dev_address=address,
                                              dev_name=name,
                                              longitude=longitude, imei=imei, dev_id=dev_id, dev_id_key=dev_id_key)

        return redirect("/app01/check/")
    return render(request, "change_device.html", {'edit_device_obj': edit_device_obj, "site_list": site_list})


def data(request):
    data_list = Data.objects.all()
    return render(request, 'data.html', {'data_list': data_list})


def request_data(request):

    print("请求数据")
    send_iot_command()
    data_list = Data.objects.all()
    return render(request, 'data.html', {'data_list': data_list})

def axis(request):
    print("thingjs request....")
    number = request.GET["id"]
    print("request number " , number)
    data_list = Data.Objects.all()

    database_return = Data.Objects.filter(id=number).first()
    print('*******************************************************')
    print(database_return)
    #if database_return is None:
        #print("no adpater data in database.")
        #return HttpResponse(0)
    x_data = database_return[3]
    y_data = database_return[4]
    z_data = database_return[5]
    vt = database_return[6]
    gps = database_return[7]
    at = database_return[8]
    res = {"x": x_data, "y": y_data, "z":z_data, "gps":gps, "at":at, "vt":vt }
    print("return json:", res)
    return HttpResponse(json.dumps(res))