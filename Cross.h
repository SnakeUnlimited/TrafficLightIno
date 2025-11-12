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
  static Loop _loopDebug;

  static bool _isInit;

  // Road Phases Queue
 // 

  // Trigger for button events
  static TrafficPhases _phases;
  static Buttons _buttons;
  static TrafficLight *_lights[CROSS_LIGHT_AMOUNT];
  // Light Output
  //
  ////////////////////////
  static void init(); 
  static void onBtnPressed(int i);
  static void onBtnReleased(int i);
  static void onPhaseChange(int phase);  
  static void onPhaseAdd(int phase);  
  //////////////////////////
  
  // SYSCALL
  static void loop();       // Tick as fast as possible from Arduino Loop!

  static String toToggleStatement(int c, bool exp);

  // Loops
  static void tickBtn();
  static void tickLight();
  static void tickPhase();   
  static void tickDebug() { 
    return; 
    Dprint("\n_\n"); 
  }

};

#endif