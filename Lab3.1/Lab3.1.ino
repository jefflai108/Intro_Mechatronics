int LED = 9;
int Pinger = 7;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED, OUTPUT);
}

void loop() {
  int dist = getDist();
  Serial.println(dist);
  if (dist < 12) { 
    digitalWrite(LED, HIGH); 
  } else { 
    digitalWrite(LED, LOW); 
  }
  delay(750);
}

long getDist() {
  triggerPing();
  return uSToInches(echoTime());
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

