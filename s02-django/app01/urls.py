"""app02 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path,re_path
from app01 import views
from django.conf.urls import url

urlpatterns = [
    path('admin/',admin.site.urls),
    # 登录页面
    path('login/', views.login),
    # 验证码
    path('login/get_validCode_img/',views.get_validCode_img),
    # 用户注册
    path('registeruser/',views.register_user),
    # 主页面
    path('first/', views.first),
    # 退出登录
    path('logout/',views.logout),
    # 注册产品
    path('repro/',views.register_product),
    # 编辑产品
    path('checktpro/',views.check_product),
    # 注册站点
    path('resite/',views.resite),
    # 编辑站点
    path('checksite/',views.check_site),
    # 设备注册
    path('register/', views.register),
    # 查看设备
    path('check/', views.check),
    # 查看设备状态
    path('checkdevstatus/',views.check_device_status),
    # 数据
    path('data/',views.data),
    # 请求数据
    path('request_data/', views.request_data),
    # 请求数据
    url(r'^axis', views.axis, name="axis"),
    # 增删改查设备
    re_path(r'checkproduct/(\d+)/delete',views.del_product),
    re_path(r'checkproduct/(\d+)/change',views.change_product),
    # 设备增删改查
    re_path(r"check/(\d+)/delete",views.deldevice),
    re_path(r"check/(\d+)/change",views.changedevice),
    # 站点增删改查
    re_path(r'checksite/(\d+)/delete',views.delsite),
    re_path(r'checksite/(\d+)/change',views.change_site),
#
]


