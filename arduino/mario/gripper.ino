/* This is the file for gripper control */
#ifndef GRIPPER
#define GRIPPER

#include <Servo.h>
//Gripper default positions
#define Gopen 800
#define Gclose 2200

Servo myservo;  // create servo object to control a servo 

int CloseGripper(void){
   //Serial.println("cl");
   myservo.attach(GripperServoPin);
   myservo.write(Gclose); 
   delay(200);
   myservo.detach(); //stop sending pulses to reserve power on the 
  return 0;
}
int OpenGripper(void){
   //Serial.println("op");
   myservo.attach(GripperServoPin);
   myservo.write(Gopen); 
   delay(200);
   myservo.detach(); //stop sending pulses to reserve power on the 
   return 0;
}

#endif