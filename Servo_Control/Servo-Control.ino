/**
 * Servo Control
 * 
 * Elijah Pivo and Jeff Lai
 * 9/23/14
 * 
 */

#include <Servo.h>

const int onOff = 10;
const int servo = 7; 

Servo myservo; 
 
void setup()
{
  pinMode(onOff, INPUT);
  myservo.attach(servo); 
}
 
void loop()
{
  if (digitalRead(onOff) == LOW) { 
    switchNotPressed();
  } else { 
    switchPressed(); 
  }
}

void switchPressed() { 
  myservo.write(10);
  delay(1000); 
  myservo.write(30);
  delay(1000);  
}

void switchNotPressed() { 
  myservo.write(170);
  delay(1000); 
  myservo.write(150);
  delay(1000);  
}

