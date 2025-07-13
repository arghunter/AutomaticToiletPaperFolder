// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 5;
const int enaPin=8;
const int lowPin=10;
const int midPin=11;
const int highPin=12;
const int stepsPerRevolution = 220;
const int triggerLowPin=25;
int sensorValue = 0;  // value read from the pot
int outputValue = 0;
const int analogInPin = A0;
const int lowRots=1;
const int midRots =2;
const int highRots=3;
bool lastPress =false;

void setup() {
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin+1, OUTPUT);
  pinMode(dirPin+1, OUTPUT);
  pinMode(lowPin, INPUT_PULLUP);
  pinMode(midPin, INPUT_PULLUP);
  pinMode(highPin, INPUT_PULLUP);
  Serial.begin(9600);



}

void rollTP(int revs){
    digitalWrite(dirPin, LOW);
    digitalWrite(enaPin, LOW);
    digitalWrite(enaPin+1, HIGH);
    for (int i=0; i<revs;i++){
      for (int x = 0; x < stepsPerRevolution; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(6000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(6000);
    }
      delay(250);  // Wait a second

      digitalWrite(dirPin+1, LOW);
      digitalWrite(enaPin, HIGH);
      digitalWrite(enaPin+1, LOW);
      // Spin motor quickly
      for (int x = 0; x < stepsPerRevolution; x++) {
        digitalWrite(stepPin+1, HIGH);
        delayMicroseconds(6000);
        digitalWrite(stepPin+1, LOW);
        delayMicroseconds(6000);
      }
   
    delay(250);
    }
    digitalWrite(enaPin+1, HIGH);
    digitalWrite(enaPin, LOW);
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < stepsPerRevolution/4; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(6000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(6000);
    }
  }


void loop() {


  if(digitalRead(lowPin)==1){
    rollTP(lowRots);
  }

  if(digitalRead(midPin)==1){
    rollTP(midRots);
  }

  if(digitalRead(highPin)==1){
    rollTP(highRots);
  }
}