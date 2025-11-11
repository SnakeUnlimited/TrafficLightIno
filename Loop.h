#ifndef LOOP_H
#define LOOP_H

#include "GPIO.h"


class Loop {
  private:
    unsigned long _timeReference;
    unsigned long _timeCurrent;
    unsigned long _deltaCounter = 0;
    unsigned long _timeStep;

    void (*_callback)();

  public:
    bool isRunning = false;

    Loop(
      void (*callback)(),
      const unsigned long timeStep, // in MS
      const bool running = true
    ) {
      _callback = callback;
      _timeReference = GPIO::getMS();
      _timeStep = timeStep;
      isRunning = running;
    }


    void tick() {
      if (!isRunning) { return; }
      const unsigned long timeCurrent = GPIO::getMS();
      if (timeCurrent + _timeStep >= _timeReference) {
        _timeReference += _timeStep; // TODO: oder auto sum = timeCurrent+_timeStep; _timeReference = sum;
        _callback();
        _deltaCounter += 1;
      }
    }
};
#endif