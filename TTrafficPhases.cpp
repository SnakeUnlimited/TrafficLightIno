#include "TTrafficPhases.h"
#include "TrafficPhases.h"

// Define the static member variable
TrafficPhases TTrafficPhases::_phases(TTrafficPhases::onChange, TTrafficPhases::onAdd);
// --- Static Callback Implementations ---

void TTrafficPhases::onChange(int i) {
  Tprint("\n\t\tON CHANGE\n");
}

void TTrafficPhases::onAdd(int i) {
  Tprint("\n\t\tON ADD\n");
}

// --- Main Execution Function ---
bool TTrafficPhases::exec() {
  return TTrafficPhases::exec2();
}

bool TTrafficPhases::exec2() {
      Tprint("\nTesting Traffic");

    // _phases = new TrafficPhases(TTrafficPhases::onChange, TTrafficPhases::onAdd);

      Tprint("\n--- INIT PHASE");
      Tprint(_phases.toString());
      Tprint("-----\n");

      Tprint("> Adding Phase...");
      _phases.add(2, 0, -1);
      Tprint("\n> Adding Phase done...\n");
      //_phases.add(1, 0, -1);
     // _phases.add(2, 1, -1);
      unsigned long tick = 0;



      while (true) {
        if (tick >= 50) { break; }
        _phases.tick();
        Tprint(">>> TICK ");
        Tprint(String(++tick));
        Tprint(" <<< \n");
        Tprint(_phases.toString());
        Tprint("--\n");
       // delay(800);
      }

      return true;
    }
