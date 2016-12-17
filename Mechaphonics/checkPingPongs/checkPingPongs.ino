#include <SPI.h>  
#include <Pixy.h>

/*
 * Test Code for checkPingPongs() function 
 * Author: Jeff Lai 
 */

Pixy pixy; // create a Pixy object
// We compare height and width to determine if an object is being thrown to the robot 
int prev_height1, prev_width1, prev_height0, prev_width0; 

void setup() { 
  Serial.begin(9600); 
  Serial.println("Start Pixy"); 

  pixy.init(); // initiate Pixy 

  if (checkPingPongs()) { 
    Serial.println("We successfully detect two ping pong balls thrown toward the robot."); 
  }
}

void loop() { 
  // none 
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
          Serial.println("not enought ping pong balls"); 
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
