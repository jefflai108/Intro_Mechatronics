/**
 * Bidirectional Control
 * 
 * Elijah Pivo and Jeff Lai
 * 9/23/14
 * 
 */

const int nodeA = 50;
const int nodeB = 52;
 
void setup()
{
  pinMode(nodeA, OUTPUT);
  pinMode(nodeB, OUTPUT);
}
 
void loop()
{

  turnClockwise();
  delay(1000);
  turnCounterclockwise();
  delay(1000);
  
}

void turnClockwise() {
  digitalWrite(nodeA, HIGH);
  digitalWrite(nodeB, LOW);
}

void turnCounterclockwise() {
  digitalWrite(nodeA, LOW);
  digitalWrite(nodeB, HIGH);
}

void stop() {
  digitalWrite(nodeA, LOW);
  digitalWrite(nodeB, LOW);
}

