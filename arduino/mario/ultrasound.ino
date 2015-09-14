/* This is the file for ultrasound control */
#ifndef ULTRASOUND
#define ULTRASOUND

long ultrasound_distance()
{
	long duration, cm; 
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(triggerPort, OUTPUT); // set the digital pin as output
	digitalWrite(triggerPort, LOW); //set the pin OFF 
	delayMicroseconds(2); //pauses for 2 microseconds q 
	digitalWrite(triggerPort, HIGH); //set the pin ON  
	delayMicroseconds(10); // pauses for 10 microseconds  
	digitalWrite(triggerPort, LOW); // set the pin OFF

	//Read the signal from the sensor: a HIGH pulse whose 
	//duration is the time (in miocrosecond) from the sending 
	//of the Ping to the reception of its echo off of an object
	pinMode(echoPort, INPUT);
	duration = pulseIn (echoPort, HIGH);

	//convert the time into a distance
	cm = microsecondsToCentimeters (duration);
	//Serial.println(cm);
	delayMicroseconds(10); // pauses for 10 microseconds  
	return cm;
}

long microsecondsToCentimeters(long microseconds)
{
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}

#endif
