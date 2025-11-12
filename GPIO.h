#ifndef GPIOMAP_H
#define GPIOMAP_H

/* Traffic Pins */
#define PassBtnVertical 11
#define PassBtnHorizontal 5

#define PassLedVerticalRed 12
#define PassLedVerticalGreen 13

#define PassLedHorizontalRed 6
#define PassLedHorizontalGreen 7

#define CarLedVerticalRed 2
#define CarLedVerticalYellow 3
#define CarLedVerticalGreen 4

#define CarLedHorizontalRed 8
#define CarLedHorizontalYellow 9
#define CarLedHorizontalGreen 10

/* Traffic Pins End */

#include <Arduino.h>
#define BAUD 9600

#define MAIN_DEBUGGING 1    // Show Print Texts

#ifdef MAIN_DEBUGGING
  #define Dprint(...) Serial.print(__VA_ARGS__);
  #define Dprintln(...) Serial.println(__VA_ARGS__);
#else
  #define Dprint(...)
  #define Dprintln(...)
#endif



class GPIO {
public:
  static void init();
  static unsigned long getMS(); // millis()

  static void print(String text); // Serial.print
  static void println(String text);
 // static void Tprint(String text);
  
  static bool isInput(int pin);
  static void pinWrite(int pin, bool mode);
  static bool pinRead(int pin);
};

#endif