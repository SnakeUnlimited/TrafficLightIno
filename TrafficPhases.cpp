
#include "TrafficPhases.h"
#include "GPIO.h"

void TrafficPhases::_addPhase(int phase, int vertical, int duration) {
    if (phase == _phaseCurrent) { Dprint(" This exact phase currently running"); return; } //
    int existingIndex = _phases.doesExist(phase);
    if (existingIndex != -1 && vertical == _verticals.getElement(existingIndex)) { Dprint("// "); Dprint(existingIndex); Dprint("\n"+_phases.toString()); Dprint(" This exact phase already in queue"); return; } //

    if (_amount <= 0) {
      _phaseCurrent = phase;
      _durationCurrent = duration;
      _verticalCurrent = vertical;
      Dprint("\n---INIT ---");
      Dprint(toString());
      Dprint("\n --- INIT END---");
    } else {
      _phases.enqueue(phase);
      _durations.enqueue(duration);
      _verticals.enqueue(vertical);
    }

    _amount += 1;
    _totalAmount += 1;
    _cbPhaseAdd();

    Dprint(toString());
}


void TrafficPhases::tick()  {
    if (_amount <= 0) {
    //  Pprint("TrafficPhases: No Amount in Tick?\n");
      return; // No new phases => stay on old one
    }
    _durationCurrent--;
    //Pprint("\n..");
    if (_durationCurrent > 0) { return; }
    
    int head = _phases.getHead();

    Pprint(".....");

    if (_phaseCurrent != 0 && head != 0) {
      Pprint("Clearance System Triggered!!");

      // No clearance!
      _phaseCurrent = 0;
      _durationCurrent = 10;
      _cbPhaseChange();
      return;
    }

    Pprint(" // Amount: ");
   
    Pprint(_amount);
    Pprint(" // ");
    if (_phases.itemCount() > 0) { 
        Pprint("-------------\n");
      Pprint("Dequeued: PHASE=");
      Pprint(_phaseCurrent);
      Pprint(" // DURR=");
      Pprint(_durationCurrent);
      Pprint(" // VERT=");
      Pprint(_verticalCurrent);
      Pprint(" \n // AFTER::::::: > \n");
      Pprint("\n HEAD:::> ");
      Pprint(_durations.getHead());
      _phaseCurrent = _phases.dequeue();
      _durationCurrent = _durations.dequeue();
      _verticalCurrent = _verticals.dequeue();
      _amount--;
      Pprint("Dequeued: PHASE=");
      Pprint(_phaseCurrent);
      Pprint(" // DURR=");
      Pprint(_durationCurrent);
      Pprint(" // VERT=");
      Pprint(_verticalCurrent);
    } else {
      Pprint("AUTO FILL>> (PHASE/DURR)=> \t");
      // NO OTHER JOB:
      // Create phase
      int newPhase = (
        _phaseCurrent == 0 ? 2 : 
        _phaseCurrent == 1 ? 2: 1
      );

      int newDurr = TIME_MIN[newPhase];
      Pprint(newPhase);
      Pprint(", ");
      Pprint(newDurr);
      Pprint("\n");
      add(newPhase, (_verticalCurrent > 0 ? 1 : 0), newDurr);
      }
    
    _cbPhaseChange();
  }

  void TrafficPhases::add(int phase, int vertical, int duration)
  { 
    
    duration = cleanDuration(phase, duration);
    if (!isPhase(phase, duration)) { Pprint("Phase Add: Bad phase: "); Pprint(phase); Pprint(" // "); Pprint(duration); Pprint("\n"); return; }
      Pprint(" // Phase: ");
    Pprint(phase);
    Pprint(" // ");
    Pprint(vertical);
    Pprint(" // Durr: ");
    Pprint(duration);
    Pprint("\n");
    
    _addPhase(phase, vertical, duration);
  }

TrafficPhases::TrafficPhases(void (*cbPhaseChange)(),
     void (*cbPhaseAdd)())
{
    _cbPhaseChange = cbPhaseChange;
    _cbPhaseAdd = cbPhaseAdd;
     _phaseCurrent = 0;
    _durationCurrent = TIME_MIN[_phaseCurrent];
    _verticalCurrent = 0;
    _amount = 1;

    _carPerPassFactor = 1;
    _totalAmount = 0;

    _cbPhaseAdd();
    _cbPhaseChange();
  }

 String TrafficPhases::toString() 
  {
    String result = ">> TrafficPhase <<";
    result += ";\nCurrPhase: \t";
    result += String(getPhase());
    result += ";\nAmount: \t";
    result += String(_amount);
    result += ";\nQAmount.: \t";
    result += String(_phases.itemCount());
    result += ";\nDuration: \t";
    result += String(_durationCurrent);
    result += ";\nVertical: \t";
    result += String(_verticalCurrent);
    if (_phases.itemCount() > 0) {
      result += ";\nNext Phase: \t";
      result += String(_phases.getHead());
      result += ";\nNext Duration: \t";
      result += String(_durations.getHead());
    } else {
      result += "\n/NO NEXT/\n/NO NEXT/";
    }
    result += ";\n";
    return result;
  }