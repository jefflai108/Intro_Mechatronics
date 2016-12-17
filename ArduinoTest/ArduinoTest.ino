  //int myPins[] = {0, 1};
  //int inPin = 11; 
    int outPin = 4; 
    int val = 0; 
    int potPin = 2; 

void setup() {
    Serial.begin(9600); 
    //pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);  
}
void loop() {
    val = analogRead(potPin); //read the value from the sesnor 
    digitalWrite(outPin, HIGH); 
    delay(val); 
    digitalWrite(outPin, LOW); 
    delay(val); 
//    if (reading == HIGH) { 
//      digitalWrite(outPin, HIGH); 
//      Serial.println(myPins[1]); 
//    } else { 
//      digitalWrite(outPin, LOW); 
//      Serial.println(myPins[0]);
//    }
}
