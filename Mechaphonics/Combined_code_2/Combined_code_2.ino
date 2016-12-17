/* import library */
#include <Encoder.h>
#include <SPI.h>  
#include <Pixy.h>
#include <Servo.h>

/* Encoder position for each key */
#define lowBb 0 //works right after calibration
#define lowC 275 //works right after calibration
#define D 350 //
#define Eb 520
#define F 800
#define G 1050
#define A 1250
#define highBb 1390
#define highC 1545

/* initialize pins */
int leftWheelA = 8;
int leftWheelB = 9;
int rightWheelA = 10;
int rightWheelB = 11;

int drive = 100;
int halt = 0;

int coinPin = 50;
int irPin = A0;
int usPin = 7;
int once = 0;

int gest_for = 255; 
int gest_back = 0; 

int turntime = 3800;
int turnSpeed = 150;

/* initialize variables */
Servo mallet;
Encoder railMotorEncoder(3, 2);

const int railMotorA = 6;
const int railMotorB = 5;
const int END = 1667;
int current_state; // determines current state of program

Pixy pixy; // create a pixy object

// compare height and width to determine if an object is being thrown at the robot 
int prev_height1, prev_width1, prev_height0, prev_width0; 

void setup() {

  Serial.begin (9600); // begin serial

  mallet.attach(4);
  mallet.write(90);

  Serial.println("Start");

  pinMode(railMotorA, OUTPUT);
  pinMode(railMotorB, OUTPUT);

  calibrateRail();

  // set wheel pins as outputs
  pinMode (leftWheelA, OUTPUT);
  pinMode (leftWheelB, OUTPUT);
  pinMode (rightWheelA, OUTPUT);
  pinMode (rightWheelB, OUTPUT);

  stopAll(30);

  pinMode (coinPin, INPUT); // set coin pin as input

  // set up IR sensor
  pinMode (irPin, OUTPUT); // set IR pin as output for setup
  
  digitalWrite(irPin, LOW);
  delayMicroseconds(2);
  digitalWrite(irPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(irPin, LOW);

  pinMode (irPin, INPUT); //set IR pin to input
  
  pixy.init(); // initialize pixy

  current_state = 3;
}

void loop() {

  Serial.println(current_state); 
  delay(1000);
  switch (current_state){

    case 0: 
    { 
            int coin = digitalRead(coinPin);

            if (once == 0){

              Serial.println("Please Insert Coin");
              once++;
            }

            if (coin == 1){
              current_state = 1;
              Serial.println(coin + " It's ALIVEEE");
              delay(500);
            }
          break;
    }
    case 1: 
    {
            driveToPosition();
            
            current_state = 2;
            
          break;
    }
    case 2: 
    {
      if (checkCurtain()){
        delay(1000);
        //playMusic();
      
        current_state = 3;
      } else {
        current_state = 2;
      }
      break;
    }
    case 3: 
    {
    // call function that performs gesture
      delay(1000);
      
      doGesture();
      
      delay(200);
      
      calibrateRail();

      delay(200);
      
      playMusic(); 
      current_state = 4;
      delay(1000);
      break;
    }
    case 4: 
    {
      if (checkPingPongs()){
        Serial.println("Evasive maneuvers!");
        returnToBase();
        current_state = 5;
        once = 0;
      }
      break;
    }
  }
}

void doGesture() { 

   for (int i = 0; i < 3; i++) { 

    analogWrite(leftWheelA, gest_for);
    analogWrite(rightWheelA, gest_back);
    analogWrite(leftWheelB, gest_back);
    analogWrite(rightWheelB, gest_for);

    delay(500);
    
    analogWrite(leftWheelA, gest_back);
    analogWrite(rightWheelA, gest_for);
    analogWrite(leftWheelB, gest_for);
    analogWrite(rightWheelB, gest_back);  

    delay(500);
    
   }
   stopAll(0);

    analogWrite(leftWheelA, gest_for);
    analogWrite(rightWheelA, gest_back);
    analogWrite(leftWheelB, gest_back);
    analogWrite(rightWheelB, gest_for);

    delay(250);
   
    stopAll(500); 
}

void driveToPosition(){

    Serial.println("Beginning Launch Sequence");

    stopAll(100);
/*
    long threshold = 24;
    long a = getAvgUSrange();
    while(a >= threshold) {
      Serial.print(a);
      Serial.print(" ");
      Serial.println(threshold);
      a = getAvgUSrange();
      forward(0);
    }
    
    Serial.print(a);
    Serial.print(" ");
    Serial.println(threshold);
    
    stopAll(30);
*/
    //center on curtain
    Serial.println("centering curtain!");
    centerColor(2);

    // stop driving forward
    stopAll(1000);

    // drive forward to position
    forward(3000);

    // stop driving forward at position
    stopAll(500);

    Serial.println("Houston, The Eagle Has Landed");
}

void returnToBase(){

    Serial.println("Initiating Return Voyage");

    // start driving backward
    //backUp(3400);
/*
    // stop driving backward
    stopAll(1000);

    //turn 360 degrees
    spotRight(4000);

    //go forward
    stopAll(100);

    long threshold = 24;
    long a = getAvgUSrange();
    while(a >= threshold) {
      Serial.print(a);
      Serial.print(" ");
      Serial.println(threshold);
      a = getAvgUSrange();
      forward(10);
    }
*/
    stopAll(10);

    //turn left to door
    findExit();
    //turnLeft(2300);

    stopAll(10);

//    forward(4000);
/*
    // turn right
    //doorFind();

    turnRight(2200);

    //backUp(1200);

    //turnRight(1750);

    forward(2000);
*/
/*
    long prev = getUSrange();
    turnRight(turntime*1.4);

    // stop turning
    stopAll(500);

    // drive forward to exit
    int totalForward = 0;
    long now = getUSrange();
    while(totalForward < 1900) {
      if(now > 10) {
        //go forward
        forward(100);
        totalForward += 100;
      } else {
        //back up
        backUp(500);

        stopAll(250);
        
        //rotate right
        turnRight(turntime/5);
        long right = getUSrange();

        stopAll(500);

        //rotate left
        turnLeft(turntime/5*2);

        stopAll(500);
        
        long left = getUSrange();

        if(left < right){
          turnRight(turntime/5*2);
        }

        delay(500);
        totalForward -= 125;
      }
      now = getUSrange();
    }
    delay(1000);
*/
    // stop driving forward at exit
    stopAll(500);

    Serial.println("Honey, I'm Home!");
}

long findExit() {
  centerColor(3);
  long l = getAvgUSrange();
  Serial.println("Centered sig 3! Advancing!");
  stopAll(500);
  forward(1000);
  stopAll(0);
  centerColor(3);
  stopAll(0);
  forward(1000);
  stopAll(0);
  centerColor(3);
  stopAll(0);
  forward(1000);
  stopAll(0);
  centerColor(3);
  stopAll(0);
  forward(1000);
  stopAll(0);
  centerColor(3);
  stopAll(0);
  forward(1000);
  stopAll(0);
  centerColor(3);
  stopAll(0);
  backUp(800);
  Serial.println("Advanced! Moving to sig 4");
  centerColor(4);
  Serial.println("Centered sig 4! Leaving");
  backUp(500);
  centerColor(4);
  backUp(500);
  centerColor(4);
  backUp(3000);

  //print range
  Serial.println(l);
  return l;
}

boolean checkCurtain () {

  boolean isOpen = false; // curtain is closed

  double prev, IRinches;
  bool first = true;
  while(!isOpen) {
    double sum = 0;

    for(int i = 0; i < 20; i++) {
      // read input value and convert to distance
      float volt = analogRead(irPin)*(5.0/1024);
      double cm = 0;
      if(volt != 0) {
        cm = pow(volt,-1.033)*14.58-1.465;
      }
      double in = cm * 0.393701;
    
      sum += in;
      delay(30);
    }
    if(!first) {
      prev = IRinches;
    }
    IRinches = sum/20.0; // convert to inches
    
    Serial.print("IR sensor: ");
    Serial.println(IRinches);

    if (IRinches > 100 || ((abs(IRinches-prev) >= 1.0) && !first)){ // if distance is more than 30 inches
      Serial.println("curtain open");
      isOpen = true; // curtain is open
    }
    first = false;
    
  }
  return isOpen;
}

// convert microseconds to inches
long microsecondsToInches(long microseconds) {
  
  return (0.007)*microseconds-0.2523;
}

long getAvgUSrange() {
  long sum = 0;
  for(int i = 0; i < 10; i++) {
    sum += getUSrange();
    delay(10);
  }
  long a = 10;
  
  return sum/a;
}

long getUSrange() {
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(usPin, OUTPUT);
  digitalWrite(usPin, LOW);
  delayMicroseconds(2);
  digitalWrite(usPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(usPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(usPin, INPUT);
  duration = pulseIn(usPin, HIGH);

  // convert the time into a distance
  inches = duration/74/2;

/*
  Serial.print(inches);
  Serial.print("in");
  Serial.println();
*/
  delay(100);
  return inches;
}

void stopAll(int duration) {
  analogWrite(rightWheelB, halt);
  analogWrite(leftWheelA, halt);
  analogWrite(leftWheelB, halt);
  analogWrite(rightWheelA, halt);

  if(duration != 0) {
    delay(duration);
  }
}
void turnRight(int duration) {
  analogWrite(leftWheelA, turnSpeed);
  analogWrite(rightWheelA, 155);
  analogWrite(leftWheelB, halt);
  analogWrite(rightWheelB, 255);

  delay(duration);
}

void turnLeft(int duration) {
  analogWrite(leftWheelA, 155);
  analogWrite(rightWheelA, turnSpeed);
  analogWrite(leftWheelB, 255);
  analogWrite(rightWheelB, halt);

  delay(duration);
}

void backUp(int duration) {
  analogWrite(leftWheelA, halt);
  analogWrite(rightWheelA, halt);
  analogWrite(leftWheelB, drive);
  analogWrite(rightWheelB, drive);

  delay(duration);
}

void forward(int duration) {
  analogWrite(leftWheelB, halt);
  analogWrite(rightWheelB, halt);
  analogWrite(leftWheelA, drive);
  analogWrite(rightWheelA, drive);

  delay(duration);
}

/*
 * Function checkPingPongs() 
 * Return true if more than 1 ping pong balls are thrown at the robot 
 */
boolean checkPingPongs () {
  static int frameRate = 1;
  uint16_t blocks; 

  // determines initial condition 
  while(1) {

     // number of detected objects 
     int number = pixy.getBlocks(); 
     Serial.println(number); 
     if (number >= 2) { // detects 2 objects 
          Serial.println("Initial Condition Achieved"); 
          updateData(pixy.blocks[0].height, pixy.blocks[0].width, pixy.blocks[1].height, pixy.blocks[1].width); 
          break; 
     } 
     Serial.println("not reached initial condition");
     delay(100); 
  } 

  Serial.println("We are going into the main loop for pixy"); 
  while (1) {
    if (frameRate%25 != 0) { // detect objects every 25 frames 
          frameRate++; 
          continue;  
    }
    frameRate /= 25;
    
    // grab blocks!
    int block = pixy.getBlocks();
    Serial.println(block); 
    if (block < 2) { // at least two ping pong balls 
          Serial.println("not enough ping pong balls"); 
          continue;
    }

    // condition that targeted ping pong balls are moving toward the robot 
    // the height and width of targeted objects should be increasing  
    // do experiment and change the value 3 
    if ((pixy.blocks[0].height - prev_height0) >= 5 && (pixy.blocks[0].width - prev_width0) >= 5 &&
            (pixy.blocks[1].height - prev_height1) >= 5 && (pixy.blocks[1].width - prev_width1) >= 5) { 
          return true; 
     } else {
          updateData(pixy.blocks[0].height, pixy.blocks[0].width, pixy.blocks[1].height, pixy.blocks[1].width);  
          Serial.println("Ping Pong is not thrown fast enough. Data updated"); 
     }

  } // end big while loop
}

void updateData(int height0, int width0, int height1, int width1) { 
  prev_height0 = height0; 
  prev_width0 = width0; 
  prev_height1 = height1; 
  prev_width1 = width1; 
  
  Serial.print("Object 0: height is "); 
  Serial.print(prev_height0); 
  Serial.print(" and width is "); 
  Serial.println(prev_width0); 
  Serial.print("Object 1: height is "); 
  Serial.print(prev_height1); 
  Serial.print(" and width is "); 
  Serial.println(prev_width1); 
}

void centerColor(int s) {
  stopAll(5);
  int totalFound = 0;
  bool centered = false;
  bool found = false;
  while(!found){
    int blocks = pixy.getBlocks();
    while (blocks == 0) {
      stopAll(5);
      Serial.print("num blocks: ");
      Serial.println(blocks);
      blocks = pixy.getBlocks();
      spotRight(50);
    }
    for(int i = 0; i < blocks; i++) {
      Serial.print(blocks);
      Serial.println(" blocks found.");
      Serial.print("signature ");
      Serial.println(pixy.blocks[i].signature);
      
      if(pixy.blocks[i].signature == s){
        Serial.print(s);
        Serial.println(" found!");
        found = true;
        break;
      }
    }
      
    if(found) {
      stopAll(0);
      break;
    } else {
      Serial.print("signature ");
      Serial.print(s);
      Serial.println(" not found!");
    }
    spotRight(500);
  }

  while(!centered) {
    bool f = false;
    for(int i = 0; i < pixy.getBlocks(); i++) {
      if(pixy.blocks[i].signature == s){
        Serial.print("signature ");
        Serial.print(s);
        Serial.println("found!");
        f = true;
        Serial.print("adjusted?: ");
        centered = center(i, s);
        Serial.println(centered);
        if(centered) {
          break;
        }
      } else {
        Serial.print("signature ");
        Serial.print(s);
        Serial.println("not found");
      }
      pixy.getBlocks();
    }
    if(!f && !centered){//if the color block is lost
      Serial.println("lost color! going back to beginning");
      centerColor(s);
    }
  }

  delay(5);
}

bool center(int i, int s) {
  Serial.println(pixy.blocks[i].x);
  while(pixy.blocks[i].x < 145 || pixy.blocks[i].x > 175) {
    if(pixy.blocks[i].signature != s) {
      centerColor(s);
    }
    Serial.println("Blocks: ");
    Serial.println(pixy.blocks[i].x);
    if(pixy.blocks[i].x > 170) {
      //turn right
      Serial.print("right for ");
      Serial.println(pixy.blocks[i].signature);
      turnRight(5);
    } else if(pixy.blocks[i].x < 150) {
      //turn left
      Serial.print("left for ");
      Serial.println(pixy.blocks[i].signature);
      turnLeft(5);  
    }
    pixy.getBlocks();
  }
  stopAll(5);
  return true;
}

void doorFind() {
  
  findDoor();

  Serial.println("Go Forward.");
  forward(0);
  delay(3000);
  stopAll(0);
  delay(1000);

}


long getDist() { 

  long sum = 0;
  
  triggerPing();
  sum += uSToInches(echoTime());
    triggerPing();
  sum += uSToInches(echoTime());
    triggerPing();
  sum += uSToInches(echoTime());
  sum /= 3;
  
  return sum;
}

void findDoor() {
  Serial.println("Turn right");
  turnRight(0);

  double diff = 0;
  // Turn until distances start getting larger
  do {

    //get distance
    
    diff = getDist();
    delay(10);
    
    //get another distance
    diff = diff - getDist();

    Serial.print("Diff: ");
    Serial.println(diff);

    //if the difference between the first and second distance
    //is positive, we have increased in distance, 
    //if it is negative we have decreased in distance
    //we keep driving until we increase in distance.
  } while (diff < 5);

  Serial.println("We're close.");

  stopAll(0);
  delay(1000);

   Serial.println("Turn right");
  turnRight(0);
  
  diff = 0;
  // Turn until distances start getting larger
  do {

    //get distance
    
    diff = getDist();
    delay(10);
    
    //get another distance
    diff = diff - getDist();

    Serial.print("Diff: ");
    Serial.println(diff);

    //if the difference between the first and second distance
    //is positive, we have increased in distance, 
    //if it is negative we have decreased in distance
    //we keep driving until we increase in distance.
  } while (diff > -1);

  Serial.println("We're closer.");
  stopAll(0);
  delay(1000);
}

//Initiates a ping
void triggerPing() {
  pinMode(usPin, OUTPUT);
  digitalWrite(usPin, LOW);
  delayMicroseconds(2);
  digitalWrite(usPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(usPin, LOW);
}

long echoTime() {
  pinMode(usPin, INPUT);
  return pulseIn(usPin, HIGH);
}

long uSToInches(long duration) {
  //Ping travels at 74 uS/inches
  return duration/74/2;
}

void spotRight(int duration) {
  analogWrite(leftWheelA, turnSpeed);
  analogWrite(rightWheelA, halt);
  analogWrite(leftWheelB, halt);
  analogWrite(rightWheelB, turnSpeed);

  delay(duration);
}

void spotLeft(int duration) {
  analogWrite(leftWheelA, halt);
  analogWrite(rightWheelA, turnSpeed);
  analogWrite(leftWheelB, turnSpeed);
  analogWrite(rightWheelB, halt);

  delay(duration);
}

void playMusic() {

  int Q = 550;
  
  // First line
  moveTo(A+25);
  delay(100);
//  int window = 5;
//  while (railMotorEncoder.read() < (A + window) && railMotorEncoder.read() > (A - window)) {
//    moveTo(A);
//    delay(10);
//  }
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(highBb);
  hitKey();
  delay(0.8*Q);

  calibrateAtEnd();

  moveTo(highC+15);
  hitKey();
  delay(Q);

  moveTo(highC+15);
  hitKey();
  delay(Q);

  moveTo(highBb);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(G+15);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(1.4*Q);

  moveTo(G);
  hitKey();
  delay(0.4*Q);

  moveTo(G);
  hitKey();
  delay(2*Q);

  // Second line
  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(highBb);
  hitKey();
  delay(0.8*Q);

  calibrateAtEnd();
  
  moveTo(highC);
  hitKey();
  delay(Q);

  moveTo(highC);
  hitKey();
  delay(Q);

  moveTo(highBb);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(1.5*Q);

  moveTo(F);
  hitKey();
  delay(0.4*Q);

  moveTo(F-20);
  hitKey();
  delay(2*Q);

  // Third line
  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(0.4*Q);

  moveTo(highBb);
  delay(100);
  hitKey();
  delay(0.4*Q);

  moveTo(A);
  delay(100); 
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(A);
  hitKey();
  delay(0.4*Q);

  moveTo(highBb);
  delay(100);
  hitKey();
  delay(0.4*Q);

  moveTo(A);
  delay(100);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q);

  moveTo(F);
  hitKey();
  delay(Q);

  moveTo(G);
  hitKey();
  delay(Q-100);
  
  calibrateRail();
  int Z = 50;
  
  moveTo(lowC+Z);
  delay(10); 
  hitKey();
  delay(1.5*Q);

  //Forth line 
  moveTo(A+Z);
  hitKey();
  delay(Q);

  moveTo(A+Z);
  hitKey();
  delay(Q);

  moveTo(highBb+Z);
  hitKey();
  delay(Q);

  moveTo(highC+Z);
  hitKey();
  delay(Q);

  moveTo(highC+Z);
  hitKey();
  delay(Q);

  moveTo(highBb+Z);
  hitKey();
  delay(Q);

  moveTo(A+Z);
  hitKey();
  delay(Q);

  moveTo(G+Z);
  hitKey();
  delay(Q);

  moveTo(F+Z);
  hitKey();
  delay(Q);

  moveTo(F+Z);
  hitKey();
  delay(Q);

  moveTo(G+Z);
  hitKey();
  delay(Q);

  moveTo(A+Z);
  hitKey();
  delay(Q);

  moveTo(G+Z);
  hitKey();
  delay(1.5*Q);

  moveTo(F+Z);
  hitKey();
  delay(0.5*Q);

  moveTo(F+Z);
  hitKey();
  delay(2*Q);
  
}


void moveTo(int endLoc) {

  if (endLoc == lowBb) {
    calibrateRail();
  } else {

    const int keyWindow = 10; //acceptable +/-  rail position error

    bool inWindow = false;

    do  {

      int currLoc = railMotorEncoder.read();

      Serial.println(currLoc);

      if (currLoc < endLoc) {
        //we are at lower pitch keys
        moveToHigherKeys();
        delay(10);
      } else if (currLoc > endLoc) {
        //we are at higher pitch keys
        moveToLowerKeys();
        delay(10);
      }

      stopKeyMove();

      inWindow = (endLoc - keyWindow < currLoc) && (currLoc < endLoc + keyWindow);
    } while (!inWindow);

    delay(50); 
    moveAgain(endLoc);
    
  }
}

void calibrateAtEnd() { 
  
  double lastPos, currPos = 0;

  moveToHigherKeys();
  do {
    lastPos = currPos;
    delay(10);
    currPos = railMotorEncoder.read();

    Serial.println(currPos);
  } while (currPos != lastPos);
  stopKeyMove();

  railMotorEncoder.write(END);
}


void moveAgain(int endLoc) {

  if (endLoc == lowBb) {
    calibrateRail();
  } else {

    const int keyWindow = 10; //acceptable +/-  rail position error

    bool inWindow = false;

    do  {

      int currLoc = railMotorEncoder.read();

      Serial.println(currLoc);

      if (currLoc < endLoc) {
        //we are at lower pitch keys
        moveToHigherKeys();
        delay(10);
      } else if (currLoc > endLoc) {
        //we are at higher pitch keys
        moveToLowerKeys();
        delay(10);
      }

      stopKeyMove();

      inWindow = (endLoc - keyWindow < currLoc) && (currLoc < endLoc + keyWindow);
    } while (!inWindow);

  }
}

void playRandom() {

  int d = 200;

  int keys[8] = {lowBb, lowC, D, Eb, F, G, A, lowC};
  String names[8] = {"lowBb", "lowC", "D", "Eb", "F", "G", "A", "lowC"};

  int randNum = random(0, 8);

  moveTo(keys[randNum]);
  delay(100);
  hitKey();
  delay(d);

  /*Serial.println(names[randNum]);
    delay(750);*/

}

void calibrateRail() {
  double lastPos, currPos = 0;

  moveToLowerKeys();
  do {
    lastPos = currPos;
    delay(10);
    currPos = railMotorEncoder.read();

    Serial.println(currPos);
  } while (currPos != lastPos);
  stopKeyMove();

  railMotorEncoder.write(0);

}

void moveToHigherKeys() {
  analogWrite(railMotorA, 0);
  analogWrite(railMotorB, 245);
}

void moveToLowerKeys() {
  analogWrite(railMotorA, 245);
  analogWrite(railMotorB, 0);
}

void stopKeyMove() {
  digitalWrite(railMotorA, LOW);
  digitalWrite(railMotorB, LOW);
}

void hitKey() {

  //mallet down
  int angle = 10;
  mallet.write(angle);
  delay(140);

  //mallet up
  angle = 65;
  mallet.write(angle);
}


  
