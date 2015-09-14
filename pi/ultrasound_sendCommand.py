import time, os, sched, sys
import drive_mario as dm
if __name__ == '__main__':
    arduino = dm.open_arduino_port()
    while True:
        mario_com = 'p'
        dm.send_command_to_mario(arduino, mario_com)
        time.sleep(0.3)
