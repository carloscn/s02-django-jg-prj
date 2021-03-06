from django.utils.deprecation import MiddlewareMixin
import csp_nonce

class MyTest(MiddlewareMixin):
    def process_response(self, request, response):
        response['Access-Control-Allow-Origin']= "*"
        response['Access-Control-Allow-Headers'] = "*"
        return response
