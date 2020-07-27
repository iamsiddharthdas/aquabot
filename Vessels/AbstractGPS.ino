#include "AbstractGPS.h"

AbstractGPS::AbstractGPS() {};

//Repeatedly feed it characters from your
void AbstractGPS::setup( ) {
  Serial.println(F("AbstractGPS INITIALISED"));
  latitude = -1;
  longitude = -1;
  bearing = 0;
  speed = 0;
  complete = false;
}

double AbstractGPS::getBearing() {
  return bearing;
}

double AbstractGPS::getLatitude() {
  return latitude;
}

double AbstractGPS::getLongitude() {
  return longitude;
}
/*
  void AbstractGPS:: sendNMEA() {
  if ( !complete )
    return;
  data.sendNMEA( TINY_AbstractGPS_ID, TINY_AbstractGPS, sentence );
  complete = false;
  sentence = "";
  }
*/

bool AbstractGPS::wait() {
  return complete;
}

/*
  bool AbstractGPS::readNMEA( char chr ) {
  if ( complete )
    return false;
  sentence += chr;
  if (chr == 0x0A)
    complete = true;
  }
*/
double AbstractGPS::getBearing( double latFrom,  double lonFrom, double latTo, double lonTo ) {
  return 0;//AbstractGPS.courseTo( latFrom, lonFrom, latTo, lonTo );
}

double AbstractGPS::getDistance( double latFrom, double lonFrom, double latTo, double lonTo ) {
  return 0;//AbstractGPS.distanceBetween( latFrom, lonFrom, latTo, lonTo );
}
