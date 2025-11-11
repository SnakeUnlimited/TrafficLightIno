
#ifndef TL_TEST_H
#define TL_TEST_H

#define DEBUG_TEST 1 
#if DEBUG_TEST
  #define Tprint(...) Serial.print(__VA_ARGS__);
  #define Tprintln(...) Serial.println(__VA_ARGS__);
#else
  #define Tprint(...)
  #define Tprintln(...)
#endif

class TL_Test {
public:
  virtual bool exec() = 0;
};

#endif