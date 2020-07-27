#ifndef Options_h
#define Options_h

#include "Arduino.h"
#include <avr/pgmspace.h>

#define OPTIONS_STORE 1

class Options {

  public: Options(void);

    void setup();
    bool isLogging();
    bool isDebugging();
    bool isAutonomous();
    bool hasVisual();
    bool hasBathymetry();
    bool getOptions( int request, String data, bool compound );
    void getOptions();

  private: long options;
};

#endif
