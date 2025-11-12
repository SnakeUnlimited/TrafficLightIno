#include "Cross.h"
#include "Buttons.h"
#include "TrafficLight.h"
#include "CarLight.h"
#include "PassengerLight.h"

/*
0 = CLEARANCE
1 = GO PASS 
2 = GO CAR

*/



TrafficLight* Cross::_lights[CROSS_LIGHT_AMOUNT] = { new PassengerLight(false), new PassengerLight(true), new CarLight(false), new CarLight(true) };
TrafficPhases Cross::_phases(Cross::onPhaseChange, Cross::onPhaseAdd);
Loop Cross::_loopButtons(Cross::tickBtn, 1);
Loop Cross::_loopLights(Cross::tickLight, 300);
Loop Cross::_loopPhases(Cross::tickPhase, 1000);
Loop Cross::_loopDebug(Cross::tickDebug, 7000);
bool Cross::_isInit(false);

Buttons Cross::_buttons(Cross::onBtnPressed, Cross::onBtnReleased, 5, 11, 50);

void Cross::init() {
  Dprint("Cross Init Start\n");
 /*

  new PassengerLight(false), 
  new PassengerLight(true), 
  new CarLight(false), 
  new CarLight(true)
*/

  /*
    PHASE:
      0 = CLEARANCE
      1 = GO_PASS
      2 = GO_CAR
  */

  _isInit = true;

 // Cross::_phases.add(2, 0, -1);
  Dprint("\nCross Init Done\n");
  Dprint("Lights:\n");
  for (int c=0;c<4;c++) {
    Dprint("\t");
    Dprint(_lights[c]->toString());
  }
  Dprint("\n\t");
  Dprint(_buttons.toString());

  Dprint("\n Phases: \n");
  Dprint(_phases.toString());
  Dprintln("------------------");

}

String Cross::toToggleStatement(int c, bool exp) {
  String result = "";
  result += String(c);
  result += " -> ";
  result += String((exp ? "X" : "_"));
  return result;
}

void Cross::onPhaseChange(int phase) {  
  int vertical = _phases.getVertical();
  int duration = _phases.getDuration();


  Dprint("\t\t--- PHASE CHANGE ");
  Dprint(phase);
  Dprint(", ");
  Dprint(vertical);
  Dprint(", ");
  Dprint(duration);
  
  Dprint(" ---\n");
  int c;
  

  const bool neutral = false;
  bool neutralCurrent = neutral;
  
  if (vertical != 0) {
    neutralCurrent = !neutralCurrent;
  }
  switch (phase) {
    case 0:
      for (c=0;c<4;c++) {
        _lights[c]->toggle(false);
         Dprint("Toggle "+toToggleStatement(c, false)+" // CLEARANCE \n");
      }
      break;
    case 1:
      // GO PASS
      for (c=0;c<2;c++) {
        _lights[c]->toggle((!c ^ !neutralCurrent)); // PASS ON
        _lights[c+2]->toggle(false); // CAR OFF
        Dprint("Toggle "+toToggleStatement(c+2, false)+" // GO PASS  \n");
        Dprint("Toggle "+toToggleStatement(c, !neutralCurrent)+" // GO PASS \n");
      }
      break;
    case 2:
    // GO CAR
      for (c=0;c<2;c++) {
        _lights[c]->toggle(false); // PASS OFF
        _lights[c+2]->toggle(((c == 0 ? false : true) ^ !neutralCurrent)); // CAR ON
       Dprint("Toggle "+toToggleStatement(c+2, !neutralCurrent)+" // GO CAR \n");
       Dprint("Toggle "+toToggleStatement(c, false)+" // GO CAR \n");
      }
      break;
  }
}

void Cross::onPhaseAdd(int phase) {
  Dprint("\t\t--- PHASE ADD ---\n");
}


void Cross::onBtnPressed(int i) {
  Dprint("~~~ BTN PRESS:   ");
  Dprint(i);
  Dprint("\n");
}

void Cross::onBtnReleased(int i) {
  Dprint("~~~ BTN RELEASED:   ");
  Dprint(i);
  Dprint("\n");

  _phases.add(1, i-1, -1);
}
void Cross::tickBtn() {
  Cross::_buttons.tick();
}


void Cross::tickLight() {
  //Dprint("------\n");
  for (int c = 0; c<2;c++) {
    _lights[c]->tick();
    _lights[c+2]->tick();
    
   // Dprintln(_lights[c]->toString());
   // Dprintln(_lights[c+2]->toString());
  }
}


void Cross::tickPhase() {
 _phases.tick();
}

// Timer
void Cross::loop() {
  if (!_isInit) { return; }
  _loopButtons.tick();
  _loopLights.tick();
  _loopPhases.tick();
  _loopDebug.tick();
}
