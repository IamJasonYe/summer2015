# File usages:
##  ***/pi ***
	Collect all the programs of Raspberry Pi board, which were mainly programed in Python.
##### drive_mario.py:
	control the car with arduino board.
##### ultrasound.py:
	return the ultrasound measurement every 0.5 second time.

##### test_timer.py:
	previous version of ultrasound.py

##### publisher.py:
	Using zmq to publish something.

##### subscriber.py:
 	Using zmq to receive something.
---
## ***/arduino***
	Collect all the programs of Arduino board.
### /arduino/beta
	The all-in-one version and it's not used now.
### /arduino/mario
	The reconstruction one of the Arduino control.
---

## ***/cam***
	The openCV files of Pingpong ball tracking and some extension.
Here is some frequently used program
```
/cam/pingPongTracking.py	#This file is a subscriber of the corordinates of the tracking object.
/cam/userland-master/build/bin/camcvCircle2 #Excecutable, using it with parameter n, like 'camcvCircle2 n'
```


