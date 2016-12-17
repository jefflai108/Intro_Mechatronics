int ledPin = 9; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT); 
  Serial.println("Start this shit, Bitch!"); 
  delay(100); 
}

void loop() {
  int x = analogRead(2); 
  if (x > 325) { // around 6.5cm 
    digitalWrite(ledPin, LOW); 
  } else { 
    digitalWrite(ledPin, HIGH); 
  }
  Serial.println(x); 
  delay(1000); 
}
