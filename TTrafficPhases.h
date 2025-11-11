

#include "TL_Test.h"
#include "TrafficPhases.h"



class TTrafficPhases : public TL_Test {
  public:

    static void onChange() {
      Tprint("\n\t\tONCHANGE\n");
    }

    static void onAdd() {
      Tprint("\n\t\tONADD\n");
    }

    bool exec() {
      Tprint("\nTesting Traffic");

      TrafficPhases _phases = TrafficPhases(onChange, onAdd);

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
};