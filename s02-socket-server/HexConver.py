# -*- coding: utf-8 -*-
#
#  * \brief   This project about Tiny Network Serial.
#  *
#  * \License  THIS FILE IS PART OF MULTIBEANS PROJECT;
#  *           all of the files  - The core part of the project;
#  *           THIS PROGRAM IS NOT FREE SOFTWARE, NEED MULTIBEANS ORG LIC;
#  *
#  *                ________________     ___           _________________
#  *               |    __    __    |   |   |         |______     ______|
#  *               |   |  |  |  |   |   |   |                |   |
#  *               |   |  |__|  |   |   |   |________        |   |
#  *               |___|        |___|   |____________|       |___|
#  *
#  *                               MULTIBEANS ORG.
#  *                     Homepage: http://www.mltbns.com/
#  *
#  *           * You can download the license on our Github. ->
#  *           * -> https://github.com/lifimlt  <-
#  *           * Copyright (c) 2020 Carlos Wei: # carlos.wei.hk@gmail.com.
#  *           * Copyright (c) 2013-2020 MULTIBEANS ORG. http://www.mltbns.com/
#  *
#  *  \note    void.
#  ****************************************************************************

class HexConvert:

    def __init__(self):
        pass

    '''
    string to bytes
    eg:
    '0123456789ABCDEF0123456789ABCDEF'
    b'0123456789ABCDEF0123456789ABCDEF'
    '''
    def stringTobytes(str):
        return bytes(str, encoding='utf8')

    '''
    bytes to string
    eg:
    b'0123456789ABCDEF0123456789ABCDEF'
    '0123456789ABCDEF0123456789ABCDEF'
    '''
    def bytesToString(bs):
        return bytes.decode(bs, encoding='utf8')

    '''
    hex string to bytes
    eg:
    '01 23 45 67 89 AB CD EF 01 23 45 67 89 AB CD EF'
    b'\x01#Eg\x89\xab\xcd\xef\x01#Eg\x89\xab\xcd\xef'
    '''
    def hexStringTobytes(str):
        str = str.upper()
        str = str.replace(" ", "")
        return bytes.fromhex(str)
        # return a2b_hex(str)

    '''
    bytes to hex string 
    eg:
    b'\x01#Eg\x89\xab\xcd\xef\x01#Eg\x89\xab\xcd\xef'
    '01 23 45 67 89 AB CD EF 01 23 45 67 89 AB CD EF'
    '''
    def bytesToHexString(bs):
        # hex_str = ''
        # for item in bs:
        #     hex_str += str(hex(item))[2:].zfill(2).upper() + " "
        # return hex_str
        return ''.join(['%02X ' % b for b in bs])

    '''
    bytes to hex string 
    eg:
    [ 01 89 ab cd ef ]
    '01 89 AB CD EF'
    '''
    def intlistToHexString(int_list):
        hex_str = ''
        for item in int_list:
            hex_str += str(hex(item))[2:].zfill(2).upper() + " "
        return hex_str
    '''
    string to bytes 
    eg:
    "hello world"
    b'\x68\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64'
    '''
    def stringToUtf8(str):
        b = bytes(str, encoding="utf-8")
        return b

    '''
    int value to byte
    eg:
    9
    b'\x09'
    '''
    def byteToInt(b):
        num = int.from_bytes(b, 'little')
        return num

    '''
    int value to byte
    eg:
    b'\x09'
    9
    '''
    def intToByte(num):
        b1 = bytes([num])
        return b1