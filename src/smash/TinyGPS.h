#ifndef TinyGPS_h
#define TinyGPS_h

#define TINY_GPS "TinyGPS"
#define TINY_GPS_ID "gps.tiny"

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class TinyGPS{

  private:
    TinyGPSPlus gps;
    double latitude;
    double longitude;
    double heading;
    double speed;

  public: TinyGPS(void){};
    void setup();
    double getLatitude();
    double getLongitude();
    double getHeading();
    double getHeading( double latFrom, double lonFrom, double latTo, double lonTo );
    double getDistance( double latFrom, double lonFrom, double latTo, double lonTo );
    bool wait();//wait for processing of the nmea sentence
    
    //If NMEA is true, nmea messages are transmitted
    void loop( bool nmea );
};

#endif
