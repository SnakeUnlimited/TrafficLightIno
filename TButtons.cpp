
#include "TButtons.h"
#include "Buttons.h"
#include "Loop.h"

Buttons TButtons::buttons = Buttons(TButtons::pressed, TButtons::released, 5, 11, 50, 50);
Loop TButtons::tloop = Loop(TButtons::tick, 1);

TButtons::TButtons() {

}

void TButtons::released(int i) {
  Bprint("Button (");
  Bprint(String(i));
  Bprint(") released \n");
}

void TButtons::pressed(int i) {
  Bprint("Button (");
  Bprint(String(i));
  Bprint(") pressed \n");
 // Bprintln(Buttons::toString());
}

void TButtons::tick() {
  
}

bool TButtons::exec()
{
  int time = GPIO::getMS();
  int delta = 1000;
    while (true) {
      tloop.tick();
      buttons.tick();
      if (GPIO::getMS() - time >= 1500) {
        break;
      }
    }
    Bprintln("FERTIG");
    return true;
  }