/**
 * Motor Speed Control
 * 
 * Slows the speed of motor rotation from full speed
 * to 0 and then pauses .5 sec before repeating.
 * 
 * Elijah Pivo and Jeff Lai
 * 9/23/16
 */

//the pin the motor is connected to
const int motor = 2;

//the max duty cycle
const int maxSpeed = 255;

//the min duty cycle
const int minSpeed = 0;

void setup() {
  //sets the motor pin to an output
  pinMode(motor, OUTPUT);
}

void loop() {

  //slowly slows the motor from full speed to 0
  for (int duty = maxSpeed; duty >= minSpeed; duty--) {
    analogWrite(motor, duty);
    delay(30);
  }

  //wait for .5 seconds
  delay(500);
}
