#
#   Connects SUB socket to tcp://localhost:5556
#

import sys
import zmq
import struct
import thread
import time
import serial, sys

x = 0
y = 1
r = 0
lock = thread.allocate_lock()
laststring = ''
gripper='c'
def open_arduino_port():
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    arduino.open()
    return arduino

def send_command_to_mario(arduino, mario_com):
    arduino.write(mario_com)
    #time.sleep(1)

def read_response_from_mario(arduino):
    mario_reep = arduino.readline()
    return mario_reep

def receiveData():
    global x,y,r,lock
    #  Socket to talk to server
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    print("Collecting updates from server...")
    socket.connect("tcp://localhost:5556")
    zip_filter = ""
    # Python 2 - ascii bytes to unicode str
    if isinstance(zip_filter, bytes):
        zip_filter = zip_filter.decode('ascii')
    socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)
    while True:
        data = socket.recv()
        content = struct.unpack('iii', data[0:12])
        lock.acquire()
        x = content[0]
        y = content[1]
        r = content[2]
        lock.release()
        #print(content)


def detect_diction():
    global laststring
    global gripper
    if(y < 60):
        if(x < 130 and laststring != 'a'):
            send_command_to_mario(arduino, 'a')
            laststring = 'a'
            print('turn_left')
        elif(x > 190 and laststring != 'd'):
            send_command_to_mario(arduino, 'd')
            laststring = 'd'
            print('turn_right')
        elif(130 < x and x < 190 and laststring != 'w'):
            send_command_to_mario(arduino, 'w')
            laststring = 'w'
            print('go_forward')
        else:
            pass
    else:
        if(x < 130 and laststring != 'v'):
            send_command_to_mario(arduino, 'v')
            laststring = 'v'
            print('back_right')
        elif(x > 190 and laststring != 'z'):
            send_command_to_mario(arduino, 'z')
            laststring = 'z'
            print('back_left')
        elif(y>220 and 130 < x and x < 190  and laststring != 'k'):
            #send_command_to_mario(arduino, 'o')
            send_command_to_mario(arduino, 'k')
            laststring = 'k'
            print('last')
            gripper='c'
            time.sleep(5)
        elif(130 < x and x < 190 and laststring != 'w'):
            send_command_to_mario(arduino, 'w')
            laststring = 'w'
            print('go_forward')
    print(laststring)

if __name__ == '__main__':
    global laststring
    global gripper
    thread.start_new_thread(receiveData, ())
    arduino = open_arduino_port()
    old_x = x
    old_y = y
    old_r = r
    send_command_to_mario(arduino, 'o')
    while True:
        lock.acquire()
        print(x,y,r)
        if(gripper=='c'):
            send_command_to_mario(arduino, 'o')
            gripper='o'
        if (x != old_x or  y != old_y or r != old_r):
            old_x = x
            old_y = y
            old_r = r
            detect_diction()
        elif(laststring != 't'):
            pass
            #send_command_to_mario(arduino, 't')
            #laststring = 't'
            #print('turn_around')
            #send_command_to_mario(arduino, 'x')
        lock.release()
        time.sleep(.1)
