#ifndef AbstractGPS_h
#define AbstractGPS_h

#define GPS_NAME "GPS"
#define GPS_ID "gps.default"

#include <SoftwareSerial.h>

class AbstractGPS {

  protected:
    double bearing;
    double speed;
    double latitude;
    double longitude;

  private:
    bool complete; //general purpose flag for reading nmea sentences
    String sentence;
    //void sendNMEA();
    //bool readNMEA( char chr); //used by SerialEvent

  public: AbstractGPS(void);
    void setup();
    double getBearing();
    double getLatitude();
    double getLongitude();
    virtual double getBearing( double latFrom, double lonFrom, double latTo, double lonTo ) = 0;
    virtual double getDistance( double latFrom, double lonFrom, double latTo, double lonTo ) = 0;
    bool wait();//wait for processing of the nmea sentence
    virtual void loop() = 0;
};

#endif
