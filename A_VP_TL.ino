/*
  Traffic Light System
  Made for Arduino Uno
  Tim Pape, 11.11.25
*/
#include <Arduino.h>    // For Strings, etc
#include "GPIO.h"       // OS specifics

//#define MAIN_TESTING 1    // Execute tests?

#ifdef MAIN_TESTING
  #include "TL_Tester.h"    // Tests
#endif


#include "Cross.h"          // Main Class


bool _isRunning;


void setup() {
  // put your setup code here, to run once:

  GPIO::init();
  
  _isRunning = true;


  // TESTS
  #ifdef MAIN_TESTING
    GPIO::println("--- Starting tests ---");
    TL_Tester tester;
    if (!tester.exec()) {
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
    GPIO::print("\nERROR TEST\n");
      _isRunning = false;
    }
  #endif

  GPIO::println("--- INIT DONE ---");
  Cross::init();
  
}



void loop() {
  if (!_isRunning) { return; }
  Cross::loop();
}

