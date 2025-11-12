#ifndef PASSLIGHT_H
#define PASSLIGHT_H
#include "TrafficLight.h"


class PassengerLight : public TrafficLight {
private:
  int pinRed;
  int pinGreen;

  bool stateRed;
  bool stateGreen;

  void _setStatus(int status) override {
    switch (status) {
    case (LIGHT_STOP):
      stateRed = true;
      stateGreen = false;
      GPIO::pinWrite(pinRed, HIGH);
      GPIO::pinWrite(pinGreen, LOW);
      break;
    case (LIGHT_PREPARE):
      stateRed = true;
      stateGreen = false;
      GPIO::pinWrite(pinRed, HIGH);
      GPIO::pinWrite(pinGreen, LOW);
      break;
    case (LIGHT_MOVE):
      stateRed = false;
      stateGreen = true;
      GPIO::pinWrite(pinRed, LOW);
      GPIO::pinWrite(pinGreen, HIGH);
      break;
    case (LIGHT_WAIT):
      stateRed = true;
      stateGreen = false;
      GPIO::pinWrite(pinRed, HIGH);
      GPIO::pinWrite(pinGreen, LOW);
      break;
    }
  }
  
public:
 // PassengerLight() {}

  PassengerLight(bool isVertical) {
    if (isVertical == true) {
      this->pinRed = PassLedVerticalRed;
      this->pinGreen = PassLedVerticalGreen;
    } else {
      this->pinRed = PassLedHorizontalRed;
      this->pinGreen = PassLedHorizontalGreen;
    }
    this->stateRed = false;
    this->stateGreen = false;
    this->_setStatus(0);
  }
  
  

  String toString() override {
    String result = "{PAS} R G: ";
    result += (stateRed ? "X" : "_");
    result += "_";
    result += (stateGreen ? "X" : "_");
    result += " // ";
    result += String(pinRed) + ", " + String(pinGreen) + "   ";
    return result;
  }
};
#endif