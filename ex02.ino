#include <Servo.h>

Servo myServo;

const int leftLDR = A0;
const int centerLDR = A1;
const int rightLDR = A2;
int pos = 90;

int leftVal, centerVal, rightVal;
int leftPrev, centerPrev, rightPrev;

void setup() {
  myServo.attach(9); // Servo signal pin
  myServo.write(90); // Center position
  Serial.begin(9600);
}

void loop() {
  // Read light values
  leftVal = analogRead(leftLDR);
  centerVal = analogRead(centerLDR);
  rightVal = analogRead(rightLDR);

  Serial.print("L:");
  Serial.print(leftVal);
  Serial.print(" C:");
  Serial.print(centerVal);
  Serial.print(" R:");
  Serial.print(rightVal);
  Serial.print(" P:");
  Serial.println(pos);


if(centerVal > rightVal && centerVal > leftVal){
  if(centerVal - rightVal < 20)
    pos = 45;
  else if(centerVal - leftVal < 20)
    pos = 135;
  else
    pos = 90;
} else if(leftVal > centerVal){
  if(leftVal - centerVal < 20)
    pos = 135;
  else
    pos = 180;
} else{
  if(rightVal - centerVal < 20)
    pos = 45;
  else
    pos = 0;
}
  myServo.write(pos);
  delay(200); // small delay for stability
}
