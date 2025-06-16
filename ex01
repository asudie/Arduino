#include <LiquidCrystal.h>

#define MODE 2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = A0;
const int ledPin = 9;

int potValue = 0;
int ledBrightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  if(MODE == 2)
  {
    Serial.begin(9600);
  	Serial.println("Enter brightness (0-255):");
  }
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("LED Brightness:");
}

void loop() {
  if(MODE == 1)
  {
    potValue = analogRead(potPin);
  	ledBrightness = map(potValue, 0, 1023, 0, 255);
	analogWrite(ledPin, ledBrightness);
  } else if(MODE == 2)
  {
    if (Serial.available() > 0) {
    	String input = Serial.readStringUntil('\n');
      int value = input.toInt();
      value = constrain(value, 0, 255);
      ledBrightness = value;
      analogWrite(ledPin, ledBrightness);
      Serial.print("Brightness set to: ");
      Serial.println(ledBrightness);
  }
  }
  lcd.setCursor(0, 1);
  	lcd.print("Value: ");
  	lcd.print(ledBrightness);
  	lcd.print("   ");

  	delay(100);
}
