#!/usr/bin/python
# -*- coding: utf8 -*-
import os
import json
import urllib2
import sys, urllib, base64
from pygame import mixer
class Chat(object):
    key = "8482dc11c26e16105d420e5e8357a062"
    apiurl = "http://www.tuling123.com/openapi/api?"
 
    def init(self):
        os.system("clear")
        print "尽情调教把!"
        print "-------------------------------"
 
    def get(self):
        print "> ",
        info = raw_input()
        print info
        if (info == 'q' or info == 'exit' or info == "quit"):
            print "- Goodbye"
            return
        self.send(info)
 
    def send(self, info):
        url_tuling = self.apiurl + 'key=' + self.key + '&' + 'info=' + info
        tuling = urllib2.urlopen(url_tuling)
        re = tuling.read()
        re_dict = json.loads(re)
        text = re_dict['text']
        text = text.encode('utf-8')
        #text = '你好啊，希望你今天过的快乐'
        #print(chardet.detect(text))
        url = 'http://apis.baidu.com/apistore/baidutts/tts?text='+text+'&ctp=1&per=0'
        f1 = open('test.mp3', 'w')

        req = urllib2.Request(url)

        req.add_header("apikey", " f6805eda3bd2a46de02ab4afa7a506a0")
        resp = urllib2.urlopen(req)
        content = resp.read()  
        result = json.loads(content, 'utf-8')
        decoded_content = base64.b64decode(result['retData'])
        f1.write(decoded_content)
        f1.close()
        print '- ', text
        mixer.init()
        mixer.music.load('test.mp3')
        mixer.music.play()
        self.get()
 
 
if __name__ == "__main__":
    chat = Chat()
    chat.init()
    chat.get()
