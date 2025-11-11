
#ifndef TRAFFIC_PHASES_H
#define TRAFFIC_PHASES_H

#include "QueueInt.h"
#include <Arduino.h>
#include "GPIO.h"


#define Pprint(...) Dprint(__VA_ARGS__);

class TrafficPhases {
private:
  void (*_cbPhaseChange)();
  void (*_cbPhaseAdd)();

  QueueInt _phases;
  QueueInt _durations;
  QueueInt _verticals;

  int _phaseCurrent = 0;
  int _durationCurrent = 0;
  int _verticalCurrent = 0;
  int _amount = 0;

  float _carPerPassFactor = 1;
  unsigned long _totalAmount = 0;
  
  void _addPhase(int phase, int vertical, int duration);

public:

  const int TIME_MIN[4] = { 
    5, // Clearance
    7, // Passenger
    10 // Car
  };
  
  const int TIME_MAX[4] = {
    10, // Clearance
    12, // Passenger
    20 // Car
  };
  TrafficPhases(
     void (*cbPhaseChange)(),
     void (*cbPhaseAdd)()
  );

  bool isPhase(int number, int duration) {
    if (number < 0 || number >= 4) { return false; }
    return (duration >= TIME_MIN[number] && duration <= TIME_MAX[number]);
  }

  int cleanDuration(int phase, int duration) {
    if (duration < TIME_MIN[phase]) {
      return TIME_MIN[phase];
    }
    if (duration > TIME_MAX[phase]) {
      return TIME_MAX[phase];
    }
    return duration;
  }

  int getPhase() {
    return _phaseCurrent;
  }

  int getDuration() {
    return _durationCurrent;
  }

  int getVertical() {
    return _verticalCurrent;
  }
        
  
  void add(int phase, int vertical, int duration);

  String toString();

  void tick();

};

#endif