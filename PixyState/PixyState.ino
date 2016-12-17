#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;
const int x = 133; //reference point x value  
const int h = 23; //refernence point height value 
int state = 1;    //There are two states, move and don't move
void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 

  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%100==0)
    {
      // State machine 
      int a = pixy.blocks[0].x; 
      int b = pixy.blocks[0].height; 
      
      switch(state){
        case(1): //This is the move state
          state = moveRobot(a, b);   
          break;
        case(2): //This is the don't move state
          state = resetState(a, b);
          break;
      }
    }
  }  
}

int resetState(int a, int b) { 
  Serial.println("Robot in Position");
  if (b < (h-3) && b > (h+3) && a < (x-3) && a > (x+3)) 
    return 2; 
  else 
    return 1; 
}

int moveRobot(int a, int b) { 
  int output = 0;
  if ( b < (h-3) ) {
    moveForward();
  } else if ( b > (h+3)) {
    moveBackwards();
  } else {
    Serial.println("Right Distance away");
    output++;
  } 

  if (a < (x-3)) {
    moveRight();
  } else if (a > (x+3)) {
    moveLeft();
  } else {
    Serial.println("Centered");
    output++;
  }
  if (output == 2) {
    return output;
  } else {
    return 1;
  }
}


// Moving commands 
void moveLeft() {
  Serial.println("Drive Left");
}
void moveRight() {
  Serial.println("Drive Right");
}
void moveForward() {
  Serial.println("Drive Forward");  
}
void moveBackwards() {
  Serial.println("Drive Backward");  
}



