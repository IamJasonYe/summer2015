#encoding=utf-8
import MultipartPostHandler, cookielib, urllib2

myfile = open(r"/home/pi/Downloads/test.wav", 'rb')
appkey = '7d78263e23217e1e99a2092670e62d2b'
url = 'http://japi.juhe.cn/voice_words/getWords'
rate = '16000'
params = {'key': appkey,
          'file': myfile,
          'rate': rate
         }

cookies = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookies), MultipartPostHandler.MultipartPostHandler)
res = opener.open(url, params)

print res.read()
