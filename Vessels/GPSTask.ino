#include "GPSTask.h"

GPSTask::GPSTask() {};

//Repeatedly feed it characters from your
void GPSTask::setup( ) {
  gpsPort.begin(9600);
  Serial.println(F("GPSTask INITIALISED"));
  latitude = -1;
  longitude = -1;
  bearing = 0;
  speed = 0;
  complete = false;
}

double GPSTask::getBearing() {
  return bearing;
}

double GPSTask::getLatitude() {
  return latitude;
}

double GPSTask::getLongitude() {
  return longitude;
}
/*
  void GPSTask:: sendNMEA() {
  if ( !complete )
    return;
  data.sendNMEA( TINY_GPSTask_ID, TINY_GPSTask, sentence );
  complete = false;
  sentence = "";
  }
*/

bool GPSTask::wait() {
  return complete;
}

/*
  bool GPSTask::readNMEA( char chr ) {
  if ( complete )
    return false;
  sentence += chr;
  if (chr == 0x0A)
    complete = true;
  }
*/
double GPSTask::getBearing( double latFrom,  double lonFrom, double latTo, double lonTo ) {
  return 0;//GPSTask.courseTo( latFrom, lonFrom, latTo, lonTo );
}

double GPSTask::getDistance( double latFrom, double lonFrom, double latTo, double lonTo ) {
  return 0;//GPSTask.distanceBetween( latFrom, lonFrom, latTo, lonTo );
}

void GPSTask::update( const gps_fix & fix ) {
  Serial.println( fix.valid.location );
  if ( fix.valid.location ) {
    latitude = fix.latitudeL();
    longitude = fix.longitudeL();
    bearing = fix.heading();
    speed = fix.speed_kph();
    Serial.print(F("\n\nGPSTask Location Updated: "));
    Serial.print( latitude, 6 ); Serial.print("E ");
    Serial.print( longitude, 6 ), Serial.println("N\n\n "); // bearing, speed );
    vessel.update( latitude, longitude, bearing, speed, true );
  }
  //sendNMEA();
}

void GPSTask::loop() {
  Serial.println(F("CHECKING GPSTask"));
  bool updated = false;
  unsigned long current = millis();

  if( nmeagps.available( gpsPort )) {
    Serial.println(F("UPDATING GPS: "));
    update( nmeagps.read());
  }
  //Serial.println();

  //if (( latitude >= 0 ) && ( longitude >= 0 ))
  //if ( GPSTask.failedChecksum() ) {
  //  Serial.print(F("Sentences that failed checksum="));
  //  Serial.println(GPSTask.failedChecksum());
  //}
}
