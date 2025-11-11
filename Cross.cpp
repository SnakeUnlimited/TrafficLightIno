#include "Cross.h"
#include "Buttons.h"
#include "CarLight.h"
#include "PassengerLight.h"

/*
0 = CLEARANCE
1 = GO PASS 
2 = GO CAR

*/


Loop Cross::_loopButtons(Cross::tickBtn, 1);
Loop Cross::_loopLights(Cross::tickLight, 1000);
Loop Cross::_loopPhases(Cross::tickPhase, 1000);
Buttons Cross::_buttons(Cross::onBtnPressed, Cross::onBtnReleased, 5, 11, 50);
TrafficPhases Cross::_phases(Cross::onPhaseChange, Cross::onPhaseAdd);
TrafficLight* Cross::_lights[CROSS_LIGHT_AMOUNT];


void Cross::init() {
  Dprint("Cross Init Start\n");
  Cross::_lights[0] = new PassengerLight(false);
  Cross::_lights[1] = new PassengerLight(true);
  Cross::_lights[2] = new CarLight(false);
  Cross::_lights[3] = new CarLight(true);
  /*
    PHASE:
      0 = CLEARANCE
      1 = GO_PASS
      2 = GO_CAR
  */

  Cross::_phases.add(2, 0, -1);
  Dprint("\nCross Init Done\n");
}

String Cross::toToggleStatement(int c, bool exp) {
  String result = "";
  result += String(c);
  result += " -> ";
  result += String((exp ? "X" : "_"));
  return result;
}

void Cross::onPhaseChange() {
  Dprint(">>> Phase Change");
  Dprint("[["+toToggleStatement(0, false)+"]]\n");
  int phase = _phases.getPhase();
  Dprint("\n\n[[[[\n");
  Dprint("\t"+_phases.toString());
  Dprint("\n]]]]\n\n");
  int c;
  const bool neutral = false;
  bool neutralCurrent = neutral;
  

  if (_phases.getVertical()) {
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
        _lights[c]->toggle(!neutralCurrent); // PASS ON
        _lights[c+2]->toggle(false); // CAR OFF
        Dprint("Toggle "+toToggleStatement(c+2, false)+" // GO PASSENGER \n");
        Dprint("Toggle "+toToggleStatement(c, !neutralCurrent)+" // GO PASSENGER \n");
        Dprint(c);
      }
      break;
    case 2:
    // GO CAR
      for (c=0;c<2;c++) {
        _lights[c]->toggle(false); // PASS OFF
        _lights[c+2]->toggle(!neutralCurrent); // CAR ON
        Dprint("Toggle "+toToggleStatement(c+2, !neutralCurrent)+" // GO CAR \n");
        Dprint("Toggle "+toToggleStatement(c, false)+" // GO CAR \n");
      }
      break;
  }
  Dprint("<<<\n");
  for (c=0;c<4;c++) {
    Dprint("\t");
    //Dprint(_lights[c]->toString());
    Dprint("\n");
  }
  Dprint(">>>\n");
}



void Cross::onPhaseAdd() {
  Dprint("--- PHASE ADD ---\n");
}

void Cross::onBtnPressed(int i) {
  Dprint("~~~ BTN PRESS\n");
}

void Cross::onBtnReleased(int i) {
  Dprint("~~~ BTN RELEASE\n");
}

void Cross::tickBtn() {

  Cross::_buttons.tick();
}

void Cross::tickLight() {
  for (int c = 0; c<2;c++) {
    _lights[c]->tick();
    _lights[c+2]->tick();
    
  }
}

void Cross::tickPhase() {
  _phases.tick();
 // Dprint("\n.");
 // Dprint(_phases.getDuration());
}

// Timer
void Cross::loop() {
  _loopButtons.tick();
  _loopLights.tick();
  _loopPhases.tick();
}
