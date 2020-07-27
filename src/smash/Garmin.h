#ifndef Garmin_h
#define Garmin_h

#include "Arduino.h"
#include "Vessel.h"

#define GARMIN_ID "com.garmin.echobeam.echobeam.sonar"
#define GARMIN "GARMIN ECHOBEAM DS70 SONAR"

class Garmin {

  public: Garmin(void);
    void setup();
    void loop( );

    private: bool enabled;
};

#endif
