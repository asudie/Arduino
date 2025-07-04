#define MOD 3

int ledOne = 13;
int ledTwo = 12;
int ledThree = 8;
int buttonPin = 2;

unsigned long lastRedBlinkTime = 0;
unsigned long redBlinkInterval = 500;
bool isRedOn = false;

unsigned long lastYellowBlinkTime = 0;
unsigned long yellowBlinkInterval = 2000;
bool isYellowOn = false;

bool ledMode = false;             
bool lastButtonState = HIGH;      
bool currentButtonState;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000;  // 1 second
bool isBlinkOn = false;

void setup()
{
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void checkState() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != currentButtonState) {
      currentButtonState = reading;
      if (currentButtonState == LOW) {
        ledMode = !ledMode;
        Serial.print("TOGGLED! Mode is now: ");
        Serial.println(ledMode ? "ON" : "OFF");
      }
    }
  }

  lastButtonState = reading;
}

void loop()
{
  checkState();

  if (!ledMode) {
    digitalWrite(ledThree, HIGH);
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    isBlinkOn = false;  // reset blinking state
  } else if(MOD == 1){
    digitalWrite(ledThree, LOW);

    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      isBlinkOn = !isBlinkOn;
    }

    digitalWrite(ledOne, isBlinkOn ? HIGH : LOW);
    digitalWrite(ledTwo, isBlinkOn ? HIGH : LOW);
  } else if(MOD == 2)
  {
    digitalWrite(ledThree, LOW);

    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      isBlinkOn = !isBlinkOn;
    }

    digitalWrite(ledOne, isBlinkOn ? HIGH : LOW);
    digitalWrite(ledTwo, isBlinkOn ? LOW : HIGH);
  } else if(MOD == 3)
  {
    digitalWrite(ledThree, LOW);

    unsigned long currentMillis = millis();

    if (currentMillis - lastRedBlinkTime >= redBlinkInterval) {
      lastRedBlinkTime = currentMillis;
      isRedOn = !isRedOn;
      digitalWrite(ledOne, isRedOn ? HIGH : LOW);
    }

    if (currentMillis - lastYellowBlinkTime >= yellowBlinkInterval) {
      lastYellowBlinkTime = currentMillis;
      isYellowOn = !isYellowOn;
      digitalWrite(ledTwo, isYellowOn ? HIGH : LOW);
    }
  }
}
