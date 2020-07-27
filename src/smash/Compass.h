#ifndef Compass_h
#define Compass_h

#include "Arduino.h"

#define NASA_COMPASS_ID F("com.nasa.marine.compass")
#define NASA_COMPASS F("NASA Marine Compass")

#define NMEA_COMPASS F("$HCHDG")

class Compass {

  private: bool enabled;
    bool start;
    int amount;
    int counter;
    String nmea;
    float offset;
    float bearing;
    float filtered;// weighed average with the given amount

  public: Compass(void);
    void setFilter( int amount );
    float getFiltered();
    float getHeading();
    void setup();
    void loop( );
};

#endif
