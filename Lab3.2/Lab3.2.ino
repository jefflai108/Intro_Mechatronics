const int LED = 9;
const int Pinger = 7;
const int IR = 2;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  for (int i = 0; i < 10; i++) {
    Serial.println(getPingDist());
    delay(10);
  }
}

void loop() {
delay(500);
}

/*************************
 * Infrared Code
 ************************/
long getInfraDist() {
  return analogRead(IR);
}

/*************************
 * Ultrasonic Code
 *************************/
long getPingDist() {
    triggerPing();
    return echoTime(); 
  //return uSToInches(echoTime());
}

//Initiates a ping
void triggerPing() {
  pinMode(Pinger, OUTPUT);
  digitalWrite(Pinger, LOW);
  delayMicroseconds(2);
  digitalWrite(Pinger, HIGH);
  delayMicroseconds(5);
  digitalWrite(Pinger, LOW);
}

long echoTime() {
  pinMode(Pinger, INPUT);
  return pulseIn(Pinger, HIGH);
}

long uSToInches(long duration) {
  //Ping travels at 74 uS/inches
  return duration/74/2;
}
