int ledOne = 13;
int ledTwo = 12;
int ledThree = 8;
int buttonPin = 2;

bool ledMode = false;
bool lastButtonState = HIGH;

void setup()
{
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
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
    digitalWrite(ledThree, 1);
    digitalWrite(ledOne, 0);
    digitalWrite(ledTwo, 0);
  } else {
    digitalWrite(ledThree, 0);
    digitalWrite(ledOne, 1);
    digitalWrite(ledTwo, 1);
    delay(1000);
    digitalWrite(ledOne, 0);
    digitalWrite(ledTwo, 0);
    delay(1000);
  }
}
