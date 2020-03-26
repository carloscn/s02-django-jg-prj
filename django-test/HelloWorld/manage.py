#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys
import threading
''' 指定证书启动django应用
    $ python manage.py runsslserver --certificate /path/to/certificate.crt --key /path/to/key.key
    $ python manage.py runsslserver --certificate /path/to/certificate.crt --key /path/to/key.key 0.0.0.0:8000
'''
def main():

    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'HelloWorld.settings')
    try:
        from django.core.management import execute_from_command_line
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        ) from exc
    execute_from_command_line(sys.argv)

if __name__ == '__main__':

    main()

