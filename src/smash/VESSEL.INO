//Constructor
Vessel::Vessel() {};

void Vessel::setup() {
  Serial.println(F("SETUP VESSEL" ));
  enable = true;//sdcard.readBoolean( CONFIG, AUTONOMY );
  Serial.print(F("VESSEL ENABLED: ")); Serial.println( enable );
  if (!enable )
    return;
  speed = 0;
  range = DEFAULT_RANGE;
  waypointIndex = 0;

  Serial.print(F("MAINTENANCE MODE: ")); Serial.println( maintenance );

  bool init = false;//!sdcard.readBoolean( CONFIG, INITIALISE );
  Serial.print(F("INITIALISING VESSEL: ")); Serial.println( !init );
  while (!init) {
    init = initialise();
  }
  controller.setup();
  Serial.print(F("VESSEL READY ")); Serial.println( init );
  delay( 1000);
}

boolean Vessel::initialise() {
  if (!enable || initialised )
    return true;
  bool ready = controller.initialise();
  return ready;
}

bool Vessel::runMaintenance( unsigned int counter ) {
  if (!enable || !maintenance )
    return true;
  bool ready = controller.isReady();
  controller.loop( bearing, data.thrust);
  int thrust = 0;
  Serial.print(F("MAINTENANCE: ")); Serial.println( ready );
  if ( counter > 0) {
    Serial.print(F("COUNTING: ")); Serial.print( counter );
    if ( counter < 720 ) {
      int cnt_bearing = counter % 720;
      bearing = ( cnt_bearing < 360 ) ? cnt_bearing++ : cnt_bearing--;
      bearing = ( bearing > 360 ) ? 0 : ( bearing < -360) ? 0 : bearing;
      Serial.print(F(" BEARING ")); Serial.print( bearing ); // Serial.print(F(", TURN ")); Serial.println( turn_active );
    } else if ( counter < 820 ) {
      bearing = 0;
      Serial.print(F("THRUST INCREASING")); Serial.println( thrust );
      thrust++;
    } else if ( counter < 1020 ) {
      Serial.print(F("THRUST DECREASING")); Serial.println( thrust );
      thrust--;
    } else if ( counter < 1120 ) {
      Serial.print(F("THRUST INCREASING")); Serial.println( thrust );
      thrust++;
    }
    counter %= 1120;
  }
  setCourse( 0, 40 );
  return true;
}

void Vessel::setCourse( double heading, double thrst ) {
  // Serial.print(F("Bearing: ")); Serial.print( bearing ); Serial.print(F(", Thrust: ")); Serial.println( thrst );
  bearing = heading;
  controller.loop( heading, thrst );
  Serial.print(F("\nCourse updated (")); Serial.print( bearing); Serial.print(F(", "));
  Serial.print( thrst ); Serial.println(F(")\n"));
  String log = "COURSE(" + String(heading) + ", " + String(thrst);
}


/**
   Send the current location and get a stack with the next steps to take.
   The first latlnh should be entered last, so that the can be popped
*/
bool Vessel::update( double latitde, double longitde, double bearing, double speed, bool updated ) {
  if ( ! webClient.connect() )
    return false;
  webClient.setContext( AQUABOTS_VESSEL_CONTEXT );
  data.latitude = latitde;
  data.longitude = longitde;
  String url = F("&lo=");
  url += String( data.longitude, 8 );
  url += F("&la=");
  url += String( data.latitude, 8);
  url += F("&b=");
  url += bearing;
  url += F("&s=");
  url += speed;
  url += F("&u=");
  url += updated;
  //Serial.print(F("UPDATE VESSEL: "));
  //Serial.println( url);

  boolean result = webClient.sendHttp( WebClient::UPDATE, false, url);
  if (!result ) {
    webClient.disconnect();
    return false;
  }

  //String response = webClient.printResponse( WebClient::UPDATE );
  //Serial.print(F("\n\nHEADING: \n")); Serial.println( response);

  size_t capacity = JSON_OBJECT_SIZE(11) + 79;
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, webClient.client);
  if (error) {
    Serial.println(F("Parsing update failed!"));
    webClient.disconnect();
    return false;
  }
  JsonObject root = doc.as<JsonObject>();
  data.heading = root["h"];
  data.thrust = root["t"];
  data.time = root["tm"];
  data.manual = root["mn"];
  webClient.disconnect();
  setCourse( data.heading, data.thrust);
  return true;
}

/**
   Get the waypoint for this desired index location. The server may override this
   with a more pressing one (e.g after a clear)
*/
bool Vessel::getWaypoint() {
  if (!enable )
    return false;
  String url = F("&index=");
  url += String( waypointIndex++ );
  waypointIndex %= MAX_WAYPOINTS;
  if ( ! webClient.connect()) {
    return false;
  }
  boolean result = webClient.sendHttp( WebClient::WAYPOINT, false, url );
  if ( !result ) {
    webClient.disconnect();
    return result;
  }
  size_t capacity = JSON_OBJECT_SIZE(7);
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, webClient.client);
  if (error) {
    Serial.println(F("Parsing update failed!"));
    webClient.disconnect();
    return false;
  }
  JsonObject root = doc.as<JsonObject>();

  if ( root.size() < 1 ) {
    webClient.disconnect();
    stop();
    return false;
  }
  int index = root[F("i")];
  char* chr_arr = root[F("nm")];
  //sdcard.writeToIndex( WAYPOINTS_FILE, index, buffer );
  Waypoint wp;
  wp.name = String( chr_arr );
  wp.latitude = root[F("la")];
  wp.longitude = root[F("lo")];
  wp.complete = root["cp"];
  wp.last = root["last"];
  waypoints[index] = wp;
  webClient.disconnect();
  return true;
}

/**
   Send the current location and get a stack with the next steps to take.
   The first latlnh should be entered last, so that the can be popped
*/
bool Vessel::updateWaypoints( ) {
  Serial.print(F("UPDATE WAYPOINTS: "));

  if ( ! webClient.connect()) {
    //webClient.disconnect();
    return false;
  }
  boolean result = false;
  if ( webClient.client.connected() ) {
    result = webClient.sendHttp( WebClient::WAYPOINTS, false, "");
    if (!result ) {
      webClient.disconnect();
      setCourse(0, 0);
      return result;
    }

    size_t capacity = JSON_OBJECT_SIZE(9) + 100;
    DynamicJsonDocument doc(capacity);
    DeserializationError error = deserializeJson(doc, webClient.client);
    if (error) {
      Serial.println(F("Parsing update failed!"));
      setCourse(0, 0);
      webClient.disconnect();
      return false;
    }
    JsonObject root = doc.as<JsonObject>();
    data.heading = root["h"];
    data.thrust = root["t"];
    data.time = root["tm"];
    webClient.disconnect();
    result = true;
  }
  setCourse( data.heading, data.thrust);
  return result;
}

void Vessel::stop() {
  Serial.println("\n\nSTOPPING!!!");
  controller.stop();
  bearing = 0;
  speed = 0;
}

void Vessel::interrupt() {
  if ( !enable )
    return;

  if ( maintenance ) {
    setCourse( 0, -5 );
    //runMaintenance( counter );
    return;
  }

  //bearing = brng;
  //Serial.print( "Running vessel, bearing "); Serial.print( brng); Serial.print( " thrust "); Serial.println( thrust );
  //setCourse( brng, thrust );
  //getWaypoint();
}

void Vessel::loop( bool enable, double heading) {
  if ( !enable )
    return;
  bearing = heading;
  double diff = data.heading - heading;
  double hd = ( data.manual ) ? angle : diff;
  Serial.print(F("VESSEL: (")); Serial.print( heading ); Serial.print( ", "); Serial.print( hd ); Serial.print( ", "); Serial.print( data.thrust ); Serial.println( F(")"));
  logger.println("");
  controller.loop(  hd, data.thrust );
}

/*
  void Vessel::interrupt( unsigned int loopCounter ) {
  //synchronize();
  if ( !enable || ( loopCounter < LOOP_TIMEOUT ))
    return;
    Waypoint wp;
    for( int i=0; i<MAX_WAYPOINTS; i++ ){
      wp = waypoints[i];
      if( wp.complete == true )
        continue;
      double distance = tinyGPS.getDistance( latitude, longitude, wp.latitude, wp.longitude );
      double courseTo =   tinyGPS.getBearing( data.latitude, data.longitude, wp.latitude, wp.longitude );
      double newThrust = ( wp.last && ( distance < range ))? (thrust*distance/range): thrust;
      setCourse( courseTo, newThrust );
    }
  //getWaypoint();
*/
//}
