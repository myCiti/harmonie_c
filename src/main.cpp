#include <Arduino.h>
#include <lcd.h>
#include <RotaryEncoder.h>

RotaryEncoder rotary(15, 8, 9,  RotaryEncoder::LatchMode::FOUR0);


void setup() {
  Serial.begin(9600);
  lcd.init(); // initialize lcd screen
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
}

