/*
 * Jeff, Modified on 12/09/2016
 * I added calibrateAtEnd() function so that it also calibrates at the end (highC) with variable END. 
 * You can easily do test to modifiy the value of END. 
 * 
 * Some potential improvements I have in mind: 
 * 1. If we're hitting a key twice in a row, we just do hitKey() twice instead of moveTo() twice. 
 * 2. Do calibrateAtEnd() whenever we are hitting highC (or highBb?). 
 * 3. moveTo() is not reliable enough, so do some tests to change the window value or do multuple moveAgain() at the end. 
 * 4. Calibrate each key move precisly i.e. duration of time between each hitKey() and position of each key for moveTo() 
 * 
 * To generate the resonating sound: 
 * 1. Loosen or tighten the screws on the keys. 
 * 2. Change the angles and duration of delay for hitKey().
 * 
 */

#include <Encoder.h>
#include <Servo.h>

#define lowBb 0 //works right after calibration
#define lowC 375 //works right after calibration
#define D 450 //
#define Eb 620
#define F 900
#define G 1150
#define A 1350
#define highBb 1490
#define highC 1600

Servo mallet;

Encoder railMotorEncoder(3, 2);

const int railMotorA = 6;
const int railMotorB = 5;
const int END = 1667; 

void setup() {
  Serial.begin(9600);
  mallet.attach(4);
  mallet.write(180);

  Serial.println("Start");

  pinMode(railMotorA, OUTPUT);
  pinMode(railMotorB, OUTPUT);

  calibrateRail();

}

void loop() {

  delay(1000);
  //calibrateRail();

  Serial.print("Current position is ");
  Serial.println(railMotorEncoder.read());

  playMusic();

  //delay(5000);
  //playRandom();

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

  //calibrateAtEnd();

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

  delay(25); 
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

