import sys
import zmq
import drive_mario as dm
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting ultrasound data from publisher servef...")
socket.connect("tcp://localhost:5557")


zip_filter= ""

def median_filter(data):
    return sorted(data)[len(data)/2]


if isinstance(zip_filter, bytes):
    zip_filter = zip_filter.decode("ascii")
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)
grip = False
arduino = dm.open_arduino_port()
data = [3000,3000,3000,3000,3000]
distance = 3000
result = 3000
while True:
    string = socket.recv_string()
    print(string)
    if len(string.split(':')) > 1 and string.split(':')[1] != '':
        result = int(string.split(':')[1])
    if(result < 3000):
        distance = result
        data.pop(0)
        data.append(distance)
        distance = median_filter(data)
    if(not grip and distance <= 5):#grip the ball
        dm.send_command_to_mario(arduino, 'c')
        grip = True
    if (grip and distance > 8 and distance < 3000):
        dm.send_command_to_mario(arduino, 'o')
        grip = False
    print(distance)
