int red = 13;
int yellow = 12;
int green = 8;
int buttonPin = 2;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);
  Serial.print("BUTTON STATE: ");
  Serial.println(buttonState);
  if(buttonState == 1)
  {
    digitalWrite(green, 1);
  } else { // MANDATORY
    digitalWrite(green, 0);
    digitalWrite(red, 1);
    digitalWrite(yellow, 1);
    delay(1000);
    digitalWrite(red, 0);
    digitalWrite(yellow, 0);
    delay(1000);
  }
 /* else{ // BONUS 1
    digitalWrite(green, 0);
    digitalWrite(red, 1);
    delay(1000);
    digitalWrite(red, 0);
    digitalWrite(yellow, 1);
    delay(1000);
    digitalWrite(yellow, 0);
  }*/
  /*else{ // BONUS 2
    digitalWrite(green, 0);
    digitalWrite(red, 1);
    digitalWrite(yellow, 1);
    delay(500);
    digitalWrite(red, 0);
    delay(500);
    digitalWrite(red, 1);
    digitalWrite(yellow, 0);
    delay(500);
    digitalWrite(red, 0);
    delay(500);
  }*/

}
