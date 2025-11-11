#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#define BUTTON_AMOUNT 2

class Buttons {
private:
  

public:

  volatile int _pins[BUTTON_AMOUNT];
  volatile bool _pressed[BUTTON_AMOUNT];
  volatile int _bounceDelay[BUTTON_AMOUNT];
  volatile int _bounce[BUTTON_AMOUNT];
  volatile unsigned long _lastTime;
  void (*_callbackPressed)(int);
  void (*_callbackReleased)(int);

  bool _getPressed(int i);
  
  Buttons(
    void (*callbackPressed)(int),
    void (*callbackReleased)(int),
    const int pin1, 
    const int pin2, 
    const int debounceDelay1,
    const int debounceDelay2 = -1
  ); 
  
  void tick(); // Tick as fast as possible

  int isAnyPressed();
  int handlePressed();

  bool getPressed(const int i);
  static bool checkIndex(const int i);

  String toString();
};
#endif