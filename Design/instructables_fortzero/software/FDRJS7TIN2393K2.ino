//Tomi Malkki 2016 (fortzero)
//May the force be with you
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo pinch;

int potpin = A7;
int ledPin1 = A4;
int ledPin2 = A5;

int valBase = 80;
int basePin = 2;

int valShoulder = 77;
int shoulderPin = 3;

int valElbow = 95;
int elbowPin = 4;

int valPinch = 100;
int pinchPin = 5;

int recPin = 7;
int runPin = 8;
int recState;
int runState;
int recLast;
int runLast;
int recCounter = 0;
int runCounter = 0;

long previousMillis = 0;
int pick[1][4];
int dep[1][4];

void setup() {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  Serial.begin(9600);
  base.attach(6, 550, 2700);
  shoulder.attach(9);
  elbow.attach(10);
  pinch.attach(11);

  base.write(valBase);
  shoulder.write(valShoulder);
  elbow.write(valElbow);
  pinch.write(valPinch);
  delay(100);
}

void loop() {

//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > 1000) {
//    previousMillis = currentMillis;
//
//
//    Serial.print("Base : ");
//    Serial.print(valBase);
//    Serial.print("\t");
//    Serial.print("Shou : ");
//    Serial.print(valShoulder);
//    Serial.print("\t");
//    Serial.print("Elbow : ");
//    Serial.print(valElbow);
//    Serial.print("\t");
//    Serial.print("Pinch : ");
//    Serial.println(valPinch);
//  }
//Un commenting above lines, will show you servo cordinates in serial monitor. Refress rate can be changed in millis fucntion




  while (digitalRead(basePin) == HIGH) {   // While u press and hold a button, u can set cords for the servo.Base, Shoulder, Elbow and Pinch
    valBase = analogRead(potpin);
    valBase = map(valBase, 0, 1023, 0, 179);
    base.write(valBase);
    delay(1);
  }


  while (digitalRead(shoulderPin) == HIGH) {
    valShoulder = analogRead(potpin);
    valShoulder = map(valShoulder, 0, 1023, 0, 179);
    shoulder.write(valShoulder);
    delay(1);
  }


  while (digitalRead(elbowPin) == HIGH) {
    valElbow = analogRead(potpin);
    valElbow = map(valElbow, 0, 1023, 0, 179);
    elbow.write(valElbow);
    delay(1);
  }


  while (digitalRead(pinchPin) == HIGH) {
    valPinch = analogRead(potpin);
    valPinch = map(valPinch, 0, 1023, 0, 179);
    pinch.write(valPinch);
    delay(1);
  }

  recording();
  Cords();
}



