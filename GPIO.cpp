#include <Arduino.h>
#include "GPIO.h"


void GPIO::init() {
  // Serial
  Serial.begin(BAUD);
  while (!Serial) {}

  // Buttons
  pinMode(PassBtnVertical, INPUT_PULLUP);
  pinMode(PassBtnHorizontal, INPUT_PULLUP);

  // LEDs
  pinMode(PassLedVerticalRed, OUTPUT);
  pinMode(PassLedVerticalGreen, OUTPUT);
  pinMode(PassLedHorizontalRed, OUTPUT);
  pinMode(PassLedHorizontalGreen, OUTPUT);
  pinMode(CarLedVerticalRed, OUTPUT);
  pinMode(CarLedVerticalYellow, OUTPUT);
  pinMode(CarLedVerticalGreen, OUTPUT);
  pinMode(CarLedHorizontalRed, OUTPUT);
  pinMode(CarLedHorizontalYellow, OUTPUT);
  pinMode(CarLedHorizontalGreen, OUTPUT);

  randomSeed(random(0,124)+analogRead(A0));
  for (int c=0;c<10;c++) {
    Dprintln("\n\n");
  }

  Dprint("------");
  Dprint(random(0,99));
  Dprint(" SETUP ");
  Dprint(millis());
  Dprint("------\n");
}

unsigned long GPIO::getMS() {
  return millis();
}

void GPIO::print(String text) {
  Serial.print(text);
}

void GPIO::println(String text) {
  Serial.println(text);
}

bool GPIO::isInput(int pin) {
  return digitalRead(pin);
}

void GPIO::pinWrite(int pin, bool mode) {
  digitalWrite(pin, mode);
}

bool GPIO::pinRead(int pin) {
  return digitalRead(pin);
}
