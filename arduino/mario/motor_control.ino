/* This is the file for motor control */
#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

void go_left()
{
     analogWrite(IN1, 255);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
     analogWrite(IN5, 80);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
}

void go_right()
{
    analogWrite(IN1, 80);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
    analogWrite(IN5, 255);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
}

void back_left()
{
     analogWrite(IN2, 255);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
     analogWrite(IN6, 80);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
}

void back_right()
{
    analogWrite(IN2, 80);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
    analogWrite(IN6, 255);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
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
  analogWrite(IN1, 180);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN2, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN5, 180);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN6, LOW);   // turn the LED on (HIGH is the voltage level)
}

void go_backward()
{
  digitalWrite(IN1, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN2, 200);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(IN5, LOW);   // turn the LED on (HIGH is the voltage level)
  analogWrite(IN6, 200);   // turn the LED on (HIGH is the voltage level)
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

#endif MOTOR_CONTROL
