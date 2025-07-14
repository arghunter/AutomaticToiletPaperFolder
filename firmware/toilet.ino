// Define pin connections & motor's steps per revolution
#include <TM1637Display.h>
const int dirPin = 2;

const int stepPin = 5;
const int enaPin=8;
const int lowPin=10;
const int midPin=11;
const int highPin=12;
const int stepsPerRevolution = 200;
const int triggerLowPin=25;
int sensorValue = 0;  // value read from the pot
int outputValue = 0;
const int analogInPin = A0;
const int lowRots=1;
const int midRots =2;
const int highRots=3;
bool lastPress =false;
int count=0;
TM1637Display display(13, 14);
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
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
   count+=revs;
    data[0] = display.encodeDigit(count/1000 % 10);
    data[1] = display.encodeDigit(count/100 %10);
    data[2] = display.encodeDigit(count/10 %10);
    data[3] = display.encodeDigit(count%10);
    display.setSegments(data);
    display.setBrightness(0x0f);
    for (int i=0; i<revs;i++){
      digitalWrite(dirPin, LOW);
      digitalWrite(enaPin, LOW);
      digitalWrite(enaPin+1, HIGH);
      for (int x = 0; x < stepsPerRevolution; x++) {

        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
    }
      delay(50);  // Wait a second

      digitalWrite(dirPin+1, LOW);
      digitalWrite(enaPin, HIGH);
      digitalWrite(enaPin+1, LOW);
      // Spin motor quickly
      for (int x = 0; x < stepsPerRevolution; x++) {
        digitalWrite(stepPin+1, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin+1, LOW);
        delayMicroseconds(1000);
      }
   
    delay(50);
    }
    digitalWrite(enaPin, LOW);
    digitalWrite(enaPin+1, HIGH);
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < stepsPerRevolution/2; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(900);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(900);
    }
   
  }


void loop() {



  if(digitalRead(lowPin)==0){
    rollTP(lowRots);
  }

  if(digitalRead(midPin)==0){
    rollTP(midRots);
  }

  if(digitalRead(highPin)==0){
    rollTP(highRots);
  }
}
