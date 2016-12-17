#include <Encoder.h>
#include <Servo.h>

#define lowBb 0 //works right after calibration
#define lowC 120 //works right after calibration
#define D 330 //
#define Eb 520
#define F 710
#define G 900
#define A 1100
#define highBb 1300
#define highC 1490

Servo mallet;

Encoder railMotorEncoder(2, 3);

const int railMotorA = 5;
const int railMotorB = 6;


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

  calibrateRail();

  Serial.print("Current position is ");
  Serial.println(railMotorEncoder.read());

  playMusic();

  delay(5000);
  //playRandom();

}

void playMusic() {

  // First line
  moveTo(A - 75);
  delay(100);
  int window = 5;
  while (railMotorEncoder.read() < (A + window) && railMotorEncoder.read() > (A - window)) {
    moveTo(A);
    delay(10);
  }
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);
  delay(250);

  moveTo(G);
  hitKey();
  delay(250);

  moveTo(G);
  hitKey();
  delay(500);
  delay(500);

  // Second line
  moveTo(A);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);
  delay(250);

  moveTo(F);
  hitKey();
  delay(250);

  moveTo(F);
  hitKey();
  delay(500);
  delay(500);

  // Third line
  moveTo(G);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(250);

  moveTo(highBb);
  hitKey();
  delay(250);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(250);

  moveTo(highBb);
  hitKey();
  delay(250);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(lowC);
  hitKey();
  delay(500);

  //Forth line 
  moveTo(A);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highC);
  hitKey();
  delay(500);

  moveTo(highBb);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(F);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);

  moveTo(A);
  hitKey();
  delay(500);

  moveTo(G);
  hitKey();
  delay(500);
  delay(250);

  moveTo(F);
  hitKey();
  delay(250);

  moveTo(F);
  hitKey();
  delay(500);
  delay(500);
  
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
  analogWrite(railMotorB, 255);
}

void moveToLowerKeys() {
  analogWrite(railMotorA, 255);
  analogWrite(railMotorB, 0);
}

void stopKeyMove() {
  digitalWrite(railMotorA, LOW);
  digitalWrite(railMotorB, LOW);
}

void hitKey() {

  //mallet down
  int angle = 90;
  mallet.write(angle);
  delay(140);

  //mallet up
  angle = 180;
  mallet.write(angle);
}

