import sys
import zmq


context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting updates from publisher server...")
socket.connect("tcp://localhost:5556")

zip_filter = ""


if isinstance(zip_filter,bytes):
    zip_filter = zip_filter.decode("ascii")
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)



while True:
    string = socket.recv_string()
    print(string)
