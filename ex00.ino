int red = 13;
int yellow = 12;
int green = 8;
int buttonPin = 2;

bool ledMode = false;
bool lastButtonState = HIGH;

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
  bool currentButtonState = digitalRead(buttonPin);
  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    ledMode = !ledMode;
    Serial.print("TOGGLED! Mode is now: ");
    Serial.println(ledMode ? "ON" : "OFF");
    delay(50);
  }

  lastButtonState = currentButtonState;

  if (!ledMode) {
    digitalWrite(green, 1);
    digitalWrite(red, 0);
    digitalWrite(yellow, 0);
  } else {
    // mandatory
    digitalWrite(green, 0);
    digitalWrite(red, 1);
    digitalWrite(yellow, 1);
    delay(1000);
    digitalWrite(red, 0);
    digitalWrite(yellow, 0);
    delay(1000);

    // bonus 1
    /*digitalWrite(green, 0);
    digitalWrite(red, 1);
    delay(1000);
    digitalWrite(red, 0);
    digitalWrite(yellow, 1);
    delay(1000);
    digitalWrite(yellow, 0);*/

    // bonus 2
    /*digitalWrite(green, 0);
    digitalWrite(red, 1);
    digitalWrite(yellow, 1);
    delay(500);
    digitalWrite(red, 0);
    delay(500);
    digitalWrite(red, 1);
    digitalWrite(yellow, 0);
    delay(500);
    digitalWrite(red, 0);
    delay(500);*/
  }
}
