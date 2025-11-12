
#include "TL_Test.h"
#include "Buttons.h"
#include "Loop.h"

#define PRINT_BUTTON 1
#if PRINT_BUTTON
    #define Bprint(...) Tprint(__VA_ARGS__);
    #define Bprintln(...) Tprintln(__VA_ARGS__);
#else
    #define Bprint(...)
    #define Bprintln(...)
#endif

class TButtons : public TL_Test {


public: 
  /*Button ns = GPIO::getButton(false);
  Button we = GPIO::getButton(true);


   void printBtns() {
    Bprint("-- Buttons: \n");
    Bprintln(ns.toString());
    Bprintln(we.toString());
  }
*/
  static Buttons buttons;
  static Loop tloop;
  TButtons();
  static void released(int i);
  static void pressed(int i);
  static void tick();

  bool exec();
};