/*
  Traffic Light System
  Made for Arduino Uno
  Tim Pape, 11.11.25
*/
#include <Arduino.h>    // For Strings, etc

#include "GPIO.h"       // OS specifics




//#define MAIN_TESTING 1    // Execute tests?
#define MAIN_DEBUGGING 1    // Show Print Texts
#define MAIN_RUNNING 1      // Execute normal program


#ifdef MAIN_TESTING
  #include "TL_Tester.h"    // Tests
#endif
#include "Cross.h"          // Main Class


bool _isRunning;






void update() {
  // SUPER CROSS.update();

}


void setup() {
  // put your setup code here, to run once:
  GPIO::init();
  _isRunning = true;


  // TESTS
  #ifdef MAIN_TESTING
    TL_Tester tester;
    if (!tester.exec()) {
      Dprint("\nERROR TEST\n");
      _isRunning = false;
    }
  #endif

  GPIO::println("--- INIT DONE ---");

#ifdef MAIN_RUNNING
  Cross::init();
#endif
}



void loop() {
  if (!_isRunning) { return; }
  Cross::loop();
}

