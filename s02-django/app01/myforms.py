from django import forms
from django.forms import widgets
from app01.models import UserInfo
from django.core.exceptions import NON_FIELD_ERRORS,ValidationError
class UserForm(forms.Form):
    user = forms.CharField(max_length=32,
                           error_messages={'required':'该字段不能为空'},
                           label='用户名',
                           widget=widgets.TextInput(attrs={'class':'form-control'}))
    pwd = forms.CharField(max_length=32,
                          label='密码',
                          widget=widgets.PasswordInput(attrs={'class':'form-control'}))
    re_pwd = forms.CharField(max_length=32,
                             label='确认密码',
                              widget=widgets.PasswordInput(attrs={'class':'form-control'}))
    # 判断是否用户已存在
    def clean_user(self):
        val = self.cleaned_data.get('user')
        user = UserInfo.objects.filter(name = val).first()
        if not user:
            return val
        else:
            raise ValidationError('该用户已注册')

    # 判断两次密码是否一致
    def clean(self):
        pwd =self.cleaned_data.get('pwd')
        re_pwd = self.cleaned_data.get('re_pwd')
        if pwd and re_pwd:
            if pwd == re_pwd:
                return self.cleaned_data
            else:
                raise ValidationError('两次密码不一致！')



















