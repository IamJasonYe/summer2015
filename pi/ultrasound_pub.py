import zmq
import time, os, sched, sys
import drive_mario as dm
if __name__ == '__main__':
    arduino = dm.open_arduino_port()
    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    socket.bind("tcp://*:5557")
    while True:
        mario_com = 'p'
        dm.send_command_to_mario(arduino, mario_com)
        #time.sleep()
        mario_resp = dm.read_response_from_mario(arduino)
        distance = mario_resp.split(':')
        if(len(distance)>1):
            distance = '%i' % int(distance[1])
            outString = 'd:' + str(distance)
        else:
            distance = 3456
            outString = 'd:'
        socket.send_string(outString)
        print(outString)
        time.sleep(0.23)
