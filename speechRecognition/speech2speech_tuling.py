#!usr/bin/env python
#coding=utf-8
import os
import sys, urllib, base64
from pygame import mixer
import MultipartPostHandler, cookielib, urllib2
import numpy as np
from pyaudio import PyAudio,paInt16
from datetime import datetime
import wave, time
import json
import chardet
from Tkinter import *

#define of params
NUM_SAMPLES = 2000
framerate = 16000
channels = 1
sampwidth = 2
#record time
TIME = 6

class Chat(object):
    key = "8482dc11c26e16105d420e5e8357a062"
    apiurl = "http://www.tuling123.com/openapi/api?"
 
    def init(self):
        os.system("clear")
        print "尽情调教把!"
        print "-------------------------------"
 
    def get(self):
        print "> ",
        info = dictectwords()
        
        if (info == 'q' or info == 'exit' or info == "quit"):
            print "- Goodbye"
            return
        if (info == None):
            info = ''
        info = info.encode('utf-8')
        self.send(info)
 
    def send(self, info):
        url_tuling = self.apiurl + 'key=' + self.key + '&' + 'info=' + str(info)
        tuling = urllib2.urlopen(url_tuling)
        re = tuling.read()
        re_dict = json.loads(re)
        text = re_dict['text']
        text = text.encode('utf-8')
        #print '回答是： ', text
        
        #文本轉語音
        url = 'http://apis.baidu.com/apistore/baidutts/tts?text='+str(text)+'&ctp=1&per=0'
        f1 = open('test.mp3', 'w')

        req = urllib2.Request(url)

        req.add_header("apikey", " f6805eda3bd2a46de02ab4afa7a506a0")
        resp = urllib2.urlopen(req)
        content = resp.read()  
        result = json.loads(content, 'utf-8')
        answer = result['retData']
        decoded_content = base64.b64decode(answer)
        f1.write(decoded_content)
        f1.close()
        print '- ', text
        mixer.init()
        mixer.music.load('test.mp3')
        mixer.music.play()
        time.sleep(2)
        self.get()
 

def save_wave_file(filename, data):
  '''save the date to the wav file'''
  wf = wave.open(filename, 'wb')
  wf.setnchannels(channels)
  wf.setsampwidth(sampwidth)
  wf.setframerate(framerate)
  wf.writeframes("".join(data))
  wf.close()	
  
def record_wave():
  #open the input of wave
  pa = PyAudio()
  stream = pa.open(format = paInt16, channels = 1, rate = framerate, input = True, frames_per_buffer = NUM_SAMPLES)
  save_buffer = []
  count = 0
  while count < TIME*4:
    #read NUM_SAMPLES sampling data
    string_audio_data = stream.read(NUM_SAMPLES)
    save_buffer.append(string_audio_data)
    count += 1
    print '.'
  #filename = datetime.now().strftime("%Y-%m-%d_%H_%M_%S")+".wav"
  filename = 'record.wav'
  save_wave_file(filename, save_buffer)
  save_buffer = []
  #print filename, "saved"

def dictectwords():
  record_wave()
  myfile = open(r"record.wav", 'rb')
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
  mywords = json.loads(res.read())['result']
  print mywords
  return mywords
  
if __name__ == "__main__":
    chat = Chat()
    chat.init()
    chat.get()
