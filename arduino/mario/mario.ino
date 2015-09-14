#include "port_def.h"
//#include "ultrasound.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo 
void setup()
{
	Serial.begin(9600);
	//Motor pin initial 
	pinMode(IN1, OUTPUT);  
	pinMode(IN2, OUTPUT);
	pinMode(IN5, OUTPUT);
	pinMode(IN6, OUTPUT);

	//Ultrasound pin initial
	pinMode(triggerPort, OUTPUT); // set the digital pin as output
	pinMode(echoPort, INPUT);
}

void loop()
{
	while(Serial.available())
	{
		int cmd = Serial.read(); 
		work_on_command(cmd);
	}
}

void work_on_command(int cmd)
{
	if (cmd == 'w'){
	  	Serial.println("Go forward");
	  	go_forward();
	}
	else if(cmd=='s'){
	  	Serial.println("Go backward");
	  	go_backward();
	}
	else if(cmd=='a'){
	  	Serial.println("Turn left");
	  	go_left();
	}
	else if(cmd=='d'){
	  	Serial.println("Turn right");
	  	go_right();
	}
	///*
	else if(cmd=='p'){
		Serial.print("Distance:");
	  	long cm; 
	  	cm = ultrasound_distance();
	  	Serial.println (cm);
	  	//Serial.print(" cm\n");
	  	Serial.flush();
	}
	else if(cmd=='o'){ //open gripper
	  	Serial.println("Open gripper");
	  	OpenGripper();
	}       
	else if(cmd=='c'){ //close gripper
	  	Serial.println("Close gripper");
	  	CloseGripper();
	}
	else if(cmd=='e')
	{
	  	Serial.println("Turn right");
	  	turn_right();      
	}
	else if(cmd =='z'){
	  	Serial.println("Back left");
	  	back_left();
	}
	else if(cmd == 'v'){
	  	Serial.println("Back right");
	  	back_right();
	}
	else if (cmd=='x'){
	  	Serial.println("Stop");
	  	stop();
	}
	/*else if (cmd=='t'){
	  	Serial.println("Turn around");
	  	turn_around();
	}*/
	else if (cmd=='k')
	{
		//do nothing
	}
	else{
	}  
}
