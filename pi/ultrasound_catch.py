import sys
import zmq
import drive_mario as dm
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting ultrasound data from publisher servef...")
socket.connect("tcp://localhost:5557")


zip_filter= ""

if isinstance(zip_filter, bytes):
    zip_filter = zip_filter.decode("ascii")
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)
grip = False
arduino = dm.open_arduino_port()
while True:
    string = socket.recv_string()
    print(string)
    if len(string.split(':')) > 1 and string.split(':')[1] != '':
        distance = int(string.split(':')[1])
    if(not grip and distance <= 5):#grip the ball
        dm.send_command_to_mario(arduino, 'c')
        mario_resp = dm.read_response_from_mario(arduino)
        grip = True
    if (grip and distance > 5 and distance < 3000):
        dm.send_command_to_mario(arduino, 'o')
        mario_resp = dm.read_response_from_mario(arduino)
        grip = False
