import zmq
import time, os, sched, sys
import drive_mario as dm
if __name__ == '__main__':
    arduino = dm.open_arduino_port()
    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    socket.bind("tcp://*:5557")
    while True:
        mario_resp = dm.read_response_from_mario(arduino)
        socket.send_string(mario_resp)
        print(mario_resp)
        #time.sleep(0)
