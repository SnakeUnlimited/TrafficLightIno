
#include "TL_Test.h"
#include "GPIO.h"
#include "TrafficLight.h"
#include "CarLight.h"
#include "PassengerLight.h"

///#define PRINT_TRAFFIC 1
#if PRINT_TRAFFIC
    #define TR_Lprint(...) Serial.print(__VA_ARGS__);
    #define TR_Lprintln(...) Serial.println(__VA_ARGS__);
#else
    #define TR_Lprint(...)
    #define TR_Lprintln(...)
#endif


class TTrafficLight : public TL_Test {

private:

public:

    TrafficLight* tl[4];

    void printLights() {
        String car, pass;
        for (int c=0;c<2;c++) {
            TR_Lprint("\n");
            car = tl[c]->toString();
            pass = tl[c+2]->toString();
            TR_Lprint(car);
            TR_Lprint("\t\t// Status= ");
            TR_Lprint(tl[c]->getCurrentStatus());
            TR_Lprint("\t// getIsMove= ");
            TR_Lprint((tl[c]->getIsMove() ? "true" : "false"));
            TR_Lprint("\n");
            TR_Lprint(pass);
            TR_Lprint("\t\t// Status= ");
            TR_Lprint(tl[c+2]->getCurrentStatus());
            TR_Lprint("\t// getIsMove= ");
            TR_Lprint((tl[c+2]->getIsMove() ? "true" : "false"));
        }
    }

    bool exec() override {
        TR_Lprintln("--- Init TrafficLight");
        int c;
        for (c=0;c<2;c++) {
            tl[c] = new CarLight(c%2);
            tl[c+2] = new PassengerLight(c%2);

            tl[c]->toggle(false);
            tl[c+2]->toggle(false);
        }

        TR_Lprintln("-Print");
        String car;
        String pass;
        for (c=0;c<2;c++) {
            printLights();
        }

        TR_Lprint("\n-Set");
        for (c=0;c<2;c++) {
            TR_Lprint("\n");
           // tl[c]->toggle();
            //tl[c+2]->toggle();
        }
        
        int ticks = 0;

        while (true) {
            TR_Lprint("\n\n**TICK** ")
            TR_Lprint(ticks);
            TR_Lprint("\n");
            for (c=0;c<2;c++) {
                tl[c]->tick();
                tl[c+2]->tick();
            }

            if (ticks == 5) {
               // TR_Lprint("\nTOGGLE\n");
              //  tl[0]->toggle();
 
                //tl[c+2]->toggle();
            }
            if (ticks == 5) {
                tl[0]->toggle();
                tl[1]->toggle();
                tl[2]->toggle();
                tl[3]->toggle();
            }
            
            if (ticks == 7) {
              //  tl[1]->toggle();
                tl[0]->toggle();
                tl[1]->toggle();
                tl[2]->toggle();
                tl[3]->toggle();
            }
            if (ticks == 13) {
                tl[0]->toggle();
                tl[1]->toggle();
                tl[2]->toggle();
                tl[3]->toggle();
            }
            if (ticks == 21) {
                tl[0]->toggle();
                tl[1]->toggle();
             //   tl[2]->toggle();
             //   tl[3]->toggle();
            }
            printLights();


            if (ticks == 40) {
                if (tl[0]->getCurrentStatus() == 0) {
                    if (tl[1]->getCurrentStatus() == 0) {
                        if (tl[2]->getCurrentStatus() == 2) {
                            if (tl[3]->getCurrentStatus() == 2) {
                                TR_Lprintln("\n\n");
                                return true;
                            }
                        }
                    }
                }
                TR_Lprintln("TraffResult:\t RESULT:::");
                TR_Lprintln(tl[0]->getCurrentStatus());
                TR_Lprintln(tl[1]->getCurrentStatus());
                TR_Lprintln(tl[2]->getCurrentStatus());
                TR_Lprintln(tl[3]->getCurrentStatus());
                
                return false;
            }
            
            ticks++;
           // delay(400);
        }
        

        return false;
    }
};