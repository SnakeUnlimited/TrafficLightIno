

#include "TL_Test.h"
#include "TQueueInt.h"
#include "TTrafficLight.h"
#include "TButtons.h"
#include "TTrafficPhases.h"


class TL_Tester : public TL_Test {

public:
  bool exec() {
    int testsAmount = 4;
    bool allTestsOk = true;

    //// TEST LIST ////
    TL_Test* tests[testsAmount] = {
      new TTrafficLight(),  // ok
      new TQueueInt(),      // ok
      new TButtons(),       // ok
      new TTrafficPhases()  // ok
    };
    //// //// //// ////
    
    for (int i=0; i < testsAmount; i++) {
      Dprint("Test ");
        
      Dprint(i+1);
      
      if (tests[i]->exec()) {
        Dprint(": OK");
      } else {
        allTestsOk = false;
        Dprint(": NOK");
      }
      Dprint("\n");
    }
    Dprint("~~ALL TEST PASS: (");
    Dprint((allTestsOk ? "OK" : "NOK"));
    Dprint(")\n");

    return allTestsOk;

  }
};