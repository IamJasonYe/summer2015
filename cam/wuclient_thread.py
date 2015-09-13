#
#   Connects SUB socket to tcp://localhost:5556
#

import sys
import zmq
import struct
import thread 
import time

x = 0
y = 1
w = 2
h = 3
lock = thread.allocate_lock()

def receiveData():
	global x,y,w,h,lock
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
		content = struct.unpack('iiii', data[0:16]) 
		lock.acquire()
		x = content[0]
		y = content[1]
		w = content[2]
		h = content[3]
		lock.release()
    		#print(content)

thread.start_new_thread(receiveData, ())
while True:
	lock.acquire()
	print (x,y,w,h)
	lock.release()
	time.sleep(.1)
