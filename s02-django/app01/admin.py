from django.contrib import admin

# Register your models here.
from app01 import models
admin.site.register(models.Data)