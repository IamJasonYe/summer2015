#encoding=utf-8
import sys, urllib, urllib2, json
import base64
myfile = open(r"jcaptcha.jpg", 'rb')
image = base64.b64encode(myfile.read())
myfile.close()
url = 'http://apis.baidu.com/apistore/idlocr/ocr'
params = {'fromdevice': 'pc',#必填, 来源。如'android''iphone'
          'clientip': '10.10.10.0',#必填，客户输出IP。
          'detecttype': 'LocateRecognize',#必填,OCR接口类型
          'languagetype': '1',#非必填，文字类型。如：'1'（中英）'2'（英）
          'imagetype': '1',#必填，图片类型。如：'1'（base64之后）'2'（源文件）
          'image': image#非必填，图像资源。
         }

decode_params = urllib.urlencode(params)
req = urllib2.Request(url, decode_params)

req.add_header("apikey", '649945717e4090aaab24eda5dced6d2e')
req.add_header('Content-Type', "application/x-www-form-urlencoded")
res = urllib2.urlopen(req)
result = res.read()
word = result[result.index('"word":')+8:-4]
print word

