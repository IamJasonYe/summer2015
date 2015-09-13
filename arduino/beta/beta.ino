//Car control port
#define IN1 5
#define IN2 6
#define IN5 3
#define IN6 11
//Servo port
#include <Servo.h> 
#define GripperServoPin 4

//gripper default positions
#define Gopen 800
#define Gclose 2200
//Ultarsound port
#define triggerPort A1  //Trigger Pin
#define echoPort    A2  //Echo Pin

//--------------------------------------------------
//Global variables:
int cmd;
long int to=0;
Servo myservo;  // create servo object to control a servo 
//--------------------------------------------------

//--------------------------------------------------
// gripper functions
//-----------------------------

// the setup routine runs once when you press reset:
void setup() {                
  // Car control
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  
  //Servo 
  Serial.begin(9600);        // set up Serial library at 9600 bps
  myservo.attach(4);   
  myservo.write(Gopen); 
  delay(200);
  myservo.detach(); //stop sending pulses to reserve power 
  
  //Ultrasound 
  Serial.begin(9600);

}

// the loop routine runs over and over again forever:
// void loop() {
//   Serial.println("Helloworld!");
//   digitalWrite(IN1, HIGH);   // turn the LED on (HIGH is the voltage level)
//   digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
//   digitalWrite(IN5, HIGH);   // turn the LED on (HIGH is the voltage level)
//   digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
// }
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
  Serial.println(cm);
	return cm;
  delay(10);
}
void loop() {
  while (Serial.available()) {
    cmd = Serial.read(); 
    to=0;
//------------------------------------------------------------
//------------SERVO FOR GRIPPER--------------------------------- 
//--------------------------------------------------------------
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
      // establish variables for duration of the ping, 
      // and the distance result in centimeters:
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
      
      Serial.print (cm);
      Serial.print("\n");
      Serial.flush();
      
      delay(10);
    }
    //*/
    else if(cmd=='o'){ //open gripper
      Serial.println("Open gripper");
      OpenGripper();
     //Serial.println("op");
     // myservo.attach(4);
     // myservo.write(Gopen); 
     // delay(200);
     // myservo.detach(); //stop sending pulses to reserve power on the 
    }       
    else if(cmd=='c'){ //close gripper
      Serial.println("Close gripper");
      CloseGripper();
     //Serial.println("cl");
     // myservo.attach(4);
     // myservo.write(Gclose); 
     // delay(200);
     // myservo.detach(); //stop sending pulses to reserve power on the 
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
    else if (cmd=='t'){
      Serial.println("Turn around");
      turn_around();
    }
    else if (cmd=='k')
    {
    	// long cm = di;
    	int i = 500;
    	//go_forward();
     analogWrite(IN1, 180);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
     analogWrite(IN5, 180);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
  
    	//OpenGripper();
    	int d =  ultrasound_distance();
    	while(d>4 && i--){
        int tmp=ultrasound_distance();
        if(tmp<3000)
          d = (tmp + d) / 2 ;
        Serial.println(d);
        //delay(10);
    	}
      if(d>4)
        Serial.println("not in catching range");
      else{
        Serial.println("In catching range");
        stop();
        CloseGripper();
        //stop();
        Serial.println("stop!");
        d =  ultrasound_distance();
        while(d<=5 || d>3000){
          d =  ultrasound_distance();
          delay(10);
        }
      }
    }
//  ------------------------------------------------------------       
    else{
      ;
      //delay(20);
    }  
//  ------------------------------------------------------------ 
  }
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void go_left()
{
   analogWrite(IN1, 255);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
   analogWrite(IN5, 80);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
   //delay(40);
   //digitalWrite(IN1, LOW);
   //digitalWrite(IN5, LOW);

}

void go_right()
{
  //int i=0;
  //for (i=0; i<=4; i++){
  analogWrite(IN1, 80);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN5, 255);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(40);
  //digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  //}
}

void back_left()
{
   analogWrite(IN2, 255);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
   analogWrite(IN6, 80);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
   //delay(40);
   //digitalWrite(IN1, LOW);
   //digitalWrite(IN5, LOW);

}

void back_right()
{
  //int i=0;
  //for (i=0; i<=4; i++){
  analogWrite(IN2, 80);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN6, 255);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(40);
  //digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  //}
}

void turn_right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);  
}

void go_forward()
{
  analogWrite(IN1, 150);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN5, 150);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(150);
  //digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
}

void go_backward()
{
  digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN2, 200);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN6, 200);   // turn the LED on (HIGH is the voltage level)
  //delay(40);
  //digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);  
}

void turn_around()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);  

}

