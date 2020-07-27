#ifndef GPSTask_h
#define GPSTask_h

#define GPS_NAME "GPS"
#define GPS_ID "gps.default"

#include <SoftwareSerial.h>
#include <NMEAGPS.h>

#define gpsPort Serial1
#define GPS_PORT_NAME "Serial1"
#define DEBUG_PORT Serial

class GPSTask {

  private:
    bool complete; //general purpose flag for reading nmea sentences
    String sentence;
    double bearing;
    double speed;
    double latitude;
    double longitude;
    NMEAGPS nmeagps;
    //void sendNMEA();
    //bool readNMEA( char chr); //used by SerialEvent
    void update( const gps_fix & fix );

  public: GPSTask(void);
    void setup();
    double getBearing();
    double getLatitude();
    double getLongitude();
    double getBearing( double latFrom, double lonFrom, double latTo, double lonTo );
    double getDistance( double latFrom, double lonFrom, double latTo, double lonTo );
    bool wait();//wait for processing of the nmea sentence
    void loop();
};

#endif


