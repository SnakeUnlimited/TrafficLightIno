#ifndef CROSS_H
#define CROSS_H

#include "Loop.h"
#include "Buttons.h"
#include "TrafficPhases.h"
#include "TrafficLight.h"
#include <Arduino.h>

#define CROSS_LIGHT_AMOUNT 4

class Cross {

private:
  
  

public:
  static Loop _loopButtons;
  static Loop _loopLights;
  static Loop _loopPhases;

  // Road Phases Queue
  static TrafficPhases _phases;

  // Trigger for button events
  static Buttons _buttons;
  
  // Light Output
  static TrafficLight *_lights[CROSS_LIGHT_AMOUNT];

  static void init();

  static void onPhaseChange();
  static void onPhaseAdd();
  static void onBtnPressed(int i);
  static void onBtnReleased(int i);


  static void tickBtn();
  static void tickLight();
  static void tickPhase();  
  static void loop();       // Tick as fast as possible from Arduino Loop!

  static String toToggleStatement(int c, bool exp);

};

#endif