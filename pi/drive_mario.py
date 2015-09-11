#module: send behavior commands to Mario

import serial, time, sys

def open_arduino_port ():
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    arduino.open()
    return arduino
def send_command_to_mario(arduino, mario_com):
    arduino.write(mario_com)
    #time.sleep(1)

def read_response_from_mario(arduino):
    mario_resp = arduino.readline()
    return mario_resp

if __name__ == '__main__':
    arduino = open_arduino_port()
    while True:
        mario_com = sys.stdin.readline()
        print mario_com
        send_command_to_mario(arduino, mario_com)
        time.sleep(1)
        mario_resp = read_response_from_mario(arduino)
        print mario_resp
