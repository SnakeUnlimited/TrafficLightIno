#ifndef CARLIGHT_H
#define CARLIGHT_H

#include "GPIO.h"
#include "TrafficLight.h"



class CarLight : public TrafficLight
{
private:
	void _setStatus(int status) override {
		switch (status) {
		case LIGHT_STOP:
			stateRed = true;
			stateYellow = false;
			stateGreen = false;
			GPIO::pinWrite(pinRed, HIGH);
			GPIO::pinWrite(pinYellow, LOW);
			GPIO::pinWrite(pinGreen, LOW);
			break;
		case LIGHT_PREPARE:
			stateRed = true;
			stateYellow = true;
			stateGreen = false;
			GPIO::pinWrite(pinRed, HIGH);
			GPIO::pinWrite(pinYellow, HIGH);
			GPIO::pinWrite(pinGreen, LOW);
			break;
		case LIGHT_MOVE:
			stateRed = false;
			stateYellow = false;
			stateGreen = true;
			GPIO::pinWrite(pinRed, LOW);
			GPIO::pinWrite(pinYellow, LOW);
			GPIO::pinWrite(pinGreen, HIGH);
			break;
		case LIGHT_WAIT:
			stateRed = false;
			stateYellow = true;
			stateGreen = false;
			GPIO::pinWrite(pinRed, LOW);
			GPIO::pinWrite(pinYellow, HIGH);
			GPIO::pinWrite(pinGreen, LOW);
			break;
		default:
			return;
		}
	}

public:
	CarLight(bool isVertical) {
		if (isVertical) {
			this->pinRed = CarLedVerticalRed;
			this->pinYellow = CarLedVerticalYellow;
			this->pinGreen = CarLedVerticalGreen;
		} else {
			this->pinRed = CarLedHorizontalRed;
			this->pinYellow = CarLedHorizontalYellow;
			this->pinGreen = CarLedHorizontalGreen;
		}
		this->stateRed = false;
		this->stateYellow = false;
		this->stateGreen = false;
		this->_setStatus(0);
	}

	// INIT
	int pinRed;
	int pinYellow;
	int pinGreen;

	bool stateRed;
	bool stateYellow;
	bool stateGreen;
	int status;

	

	String toString() override {
		String result = "{CAR} RYG: ";
		result += (stateRed ? "X" : "_");
		result += (stateYellow ? "X" : "_");
		result += (stateGreen ? "X" : "_");
		result += " // ";
		result += String(pinRed) + ", " + String(pinYellow) + ", " + String(pinGreen);
		return result;
	}

};
#endif