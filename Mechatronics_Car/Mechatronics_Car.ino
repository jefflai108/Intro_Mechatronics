#include <SPI.h>  
#include <Pixy.h>

Pixy pixy; // create a pixy object
int pinA = 5; // initialize pinA of motor
int i = 0; // sentinel to make it only stop once

// set pins for sensors
const int RSPin = 7; 
const int LSPin = 6;
int j = 0;

unsigned long timestamp;  // variable for timestamp
long Rpulse, Lpulse, Rinches, Linches; // variables for sensor data

void setup() {

  Serial.begin(9600); // begin serial
  Serial.print("Starting...\n"); // tell user the program has started
  delay(500);

  // set pins as outputs
  pinMode (pinA, OUTPUT);
  pinMode(RSPin, INPUT);
  pinMode(LSPin, INPUT);
  
  pixy.init(); // initialize pixy

}

void loop() {
  
  if ((i == 0) && isStop()){ // if the pixy sees the stop label

    endRun(); // call function to stop motor and stop collecting data
    i = 1;
  }

  else { // otherwise continue driving and gathering data

    if (j == 0){

      analogWrite (pinA, 255); // set motor to drive at highest speed
      Serial.println("Motor Started");
      delay(500);

      Serial.println("Data Collection Started");
      delay(500);
      Serial.println("Left  Right");
    
      j++; // only print this information once
    }

    collectData(); // call collectData function
    
  }
}

/* isStop function checks if the Pixy cam senses the label.  If it does, it returns true.
 * Otherwise it returns false.
 */
boolean isStop() {

  int sig = 0; // initialize signature 
  uint16_t blocks; // initialize blocks
  boolean stop = false; // initialize stop at false
  
  // grab blocks
  blocks = pixy.getBlocks(1);
  
  // if there are blocks
  if (blocks)
  {

    sig = pixy.blocks[0].signature; // set it equal to the sig
  
    if (sig == 1){ // if the signature is 1
         
        stop = true; // send signal to stop the car
    }
  }  

  return stop;
}

/* endRun fuction stops the motor and data collection when the Pixy cam senses the stop label */

void endRun (){

  // stop motor by setting both puns to low
  analogWrite (pinA, 0);
  Serial.println("Motor Stopped");

  // stop transmitting information via serial to end data collection
  Serial.println("Data Collection Stopped");
  Serial.end();
}

/* collectData collects the data from the long range US sensors*/
void collectData (){

  Rpulse = pulseIn(RSPin, HIGH); // collect data from right pin
  Lpulse = pulseIn(LSPin, HIGH); // collect data from left pin

  // scale data to inches
  Rinches = Rpulse / 147;
  Linches = Lpulse / 147;

  timestamp = millis(); // set timestamp to current time

  // print formatted outputs
  Serial.print(timestamp);
  Serial.print(",");
  Serial.print(Linches);
  Serial.print(",");
  Serial.println(Rinches);
}


