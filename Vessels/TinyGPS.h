#ifndef TinyGPS_h
#define TinyGPS_h

#define TINY_GPS "TinyGPS"
#define TINY_GPS_ID "gps.tiny"

#include <SoftwareSerial.h>
#include "AbstractGPS.h"
#include <TinyGPS++.h>

class TinyGPS : public AbstractGPS{

  private:
    TinyGPSPlus gps;

  public: TinyGPS(void) : AbstractGPS(){};
    void setup();
    using AbstractGPS::getBearing;
    double getBearing( double latFrom, double lonFrom, double latTo, double lonTo ) override;
    double getDistance( double latFrom, double lonFrom, double latTo, double lonTo ) override;
    bool wait();//wait for processing of the nmea sentence
    void loop() override;
};

#endif


