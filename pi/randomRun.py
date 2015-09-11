import sys
import zmq
import drive_mario as dm

context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting updates from publisher server...")
socket.connect("tcp://localhost:5556")

zip_filter = ""
mario_forward = 'w'
mario_backward = 's'

if isinstance(zip_filter,bytes):
    zip_filter = zip_filter.decode("ascii")
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)


arduino = dm.open_arduino_port()
while True:
    string = socket.recv_string()
    print(int(string))
    if(int(string) > 0):
        dm.send_command_to_mario(arduino, mario_forward)
    else:
        dm.send_command_to_mario(arduino, mario_backward)
    #time.sleep()
