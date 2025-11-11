#include "Buttons.h"
#include <Arduino.h>
#include "GPIO.h"

// Define static members
volatile int _pins[BUTTON_AMOUNT];
volatile bool _pressed[BUTTON_AMOUNT];
volatile int _bounceDelay[BUTTON_AMOUNT];
volatile int _bounce[BUTTON_AMOUNT];
volatile unsigned long _lastTime;
void (*_callbackPressed)() = nullptr;
void (*_callbackReleased)() = nullptr;

// Constructor
Buttons::Buttons(void (*callbackPressed)(int), void (*callbackReleased)(int), const int pin1, const int pin2, const int debounceDelay1, const int debounceDelay2)
{ 
    _callbackPressed = callbackPressed;
    _callbackReleased = callbackReleased;

    // Store pin mapping
    _pins[0] = pin1;
    _pins[1] = pin2;

    _bounceDelay[0] = debounceDelay1;
    _bounceDelay[1] = (debounceDelay2 < 0 ? debounceDelay1 : debounceDelay2);

    for (int i = 0; i < BUTTON_AMOUNT; i++) {
        _bounce[i] = 0;
        _pressed[i] = false;
    }
    _lastTime = GPIO::getMS();
}

bool Buttons::_getPressed(int i) {
    if (i < 0 || i >= BUTTON_AMOUNT) return false;
    return !_pressed[i];
}


void Buttons::tick() {
    unsigned long currentTime = GPIO::getMS();

    if (currentTime <= _lastTime) { 
      return;
    }
    for (int i = 0; i < BUTTON_AMOUNT; i++) {
        bool reading = !GPIO::isInput(_pins[i]);

        // If the reading is different from last stable state
        if (reading != _pressed[i]) {
            _bounce[i]++;
            if (_bounce[i] >= _bounceDelay[i]) {
                _pressed[i] = reading;
                _bounce[i] = 0;
                if (reading) {
                  _callbackPressed(i);
                } else {
                  _callbackReleased(i);
                }
            }
        } else {
            // Reset debounce counter if reading matches current state
            _bounce[i] = 0;
        }
    }
    _lastTime = currentTime;
}

// Returns index of any pressed button, -1 if none
int Buttons::isAnyPressed() {
    for (int i = 0; i < BUTTON_AMOUNT; i++) {
        if (_pressed[i]) return i;
    }
    return -1;
}

// Returns index of pressed button and resets it (like "handle once")
int Buttons::handlePressed() {
    int index = isAnyPressed();
    if (index >= 0) _pressed[index] = false;
    return index;
}

// Check if index is valid
bool Buttons::checkIndex(const int i) {
    return (i >= 0 && i < BUTTON_AMOUNT);
}

// Get current pressed state of a button
bool Buttons::getPressed(const int i) {
    if (!checkIndex(i)) return false;
    return _pressed[i];
}

// Optional: return pressed buttons as string
String Buttons::toString() {
    String s = "";
    for (int i = 0; i < BUTTON_AMOUNT; i++) {
        s += "\t Button " + String(i) + ": ";
        s += _pressed[i] ? "Pressed" : "Released";
        s += "\t";
        s += String(_bounce[i]);
        if (i < BUTTON_AMOUNT - 1) s += ", ";
    }
    return s;
}
