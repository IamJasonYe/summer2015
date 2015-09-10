#! /usr/bin/env python
#coding=utf-8
import time, os, sched, sys
import drive_mario as dm
#第一个参数确定任务的时间，返回某个特定的时间到现在的秒数
#第二个参数以某种人为的方式衡量时间
schedule = sched.scheduler(time.time, time.sleep)
nTime = 1
def perform_command(cmd, inc):
    # 安排inc秒后再次运行自己，即周期运行
    global nTime
    schedule.enter(inc, 0, perform_command, (cmd,inc))
    #os.system(cmd)
    #print(time.time())
    print 'execute time:' + str(time.time()), 'at nTIme:' + str(nTime)
    nTime = nTime + 1
# 读命令
   # mario_com = sys.stdin.readline()
    mario_com = 'p'
    dm.send_command_to_mario(arduino, mario_com)
    time.sleep(0.5)
    mario_resp = dm.read_response_from_mario(arduino)
    print mario_resp
def timming_exe(cmd, inc = 60):
    # enter用来安排某事件的发生时间,从现在起第n秒开始启动
    schedule.enter(inc, 0, perform_command, (cmd, inc))
    # 持续运行，直到计划时间队列变成空为止
    schedule.run()

if __name__ == '__main__':
#   tt=time.time()
#   print('show time after 5 seconds:', tt)
    arduino = dm.open_arduino_port()
    timming_exe('echo %time%',0.5 )

