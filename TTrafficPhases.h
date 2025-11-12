

#include "TL_Test.h"
#include "TrafficPhases.h"



class TTrafficPhases : public TL_Test {
  public:

    static TrafficPhases _phases;
    
    static void onChange(int i);
    static void onAdd(int i);

    static bool exec2();
    bool exec();
};