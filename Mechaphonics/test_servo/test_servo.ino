#include <Servo.h> 

Servo mallet;

void setup() {
  // put your setup code here, to run once:
  mallet.attach(4);

}

void loop() {
  mallet.write(90); 
  delay(2000);
  mallet.write(180);
  delay(2000);
  mallet.write(90);  
  delay(2000);
    mallet.write(180);  
  delay(2000);
}
