SoftwareSerial compassSerial(10,11,true);

Compass::Compass() {
  start = false;
  amount = 1;
  counter = 0;
  bearing = 0;
};

//Repeatedly feed it characters from your
void Compass::setup( ) {
  compassSerial.begin(4800);
  Serial.println("Polling Compass");
}

float Compass::getHeading() {
  Serial.println("COMPASS: "); Serial.println( bearing);
  return bearing;
}

void Compass::setFilter( int amnt ) {
  counter = 0;
  amount = (amnt <= 0) ? 1 : amnt;
}

float Compass::getFiltered() {
  return filtered;
}

void Compass::loop() {
  Serial.print(F("READING COMPASS: "));
  nmea = "";
  if (compassSerial.available()) {
    char chr =  compassSerial.read();
    Serial.print( chr );
    nmea += chr;
  }
  if ( !nmea.startsWith( NMEA_COMPASS ))
    return;
  int bg = nmea.indexOf(',');
  int nd = nmea.indexOf(',', bg + 1);
  Serial.print(F("COMPASS SUB: ")); Serial.println(nmea.substring(bg + 1, nd));
  bearing = nmea.substring(bg + 1, nd).toFloat();
  if ( counter < amount )
    counter++;
  filtered = (filtered * (counter - 1) + bearing ) / counter;
  Serial.print(F(" = "));
  Serial.print( bearing);
  Serial.print(F(" ("));
  Serial.print( filtered );
  Serial.println(F(" ) DONE: "));

  if ( nmea.length() != 0 ) {
    data.sendNMEA(NASA_COMPASS_ID, NASA_COMPASS, nmea );
  }
  //Serial.println( Compass );
}
