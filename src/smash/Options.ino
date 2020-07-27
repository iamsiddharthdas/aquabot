#include "Options.h"

//Constructor
Options::Options() {
  options = 0;
};

/**
   Get the waypoints for this vessel
*/
void Options::setup( ) {
  getOptions();
  Serial.print(F("SETUP Options ")); Serial.println( options );
}

/**
   Get log selected
*/
bool Options::isLogging() {
  return ( options & 0x01 ) > 0;
}

/**
   Get debug selected
*/
bool Options::isDebugging() {
  return ( options & 0x02 ) > 0;
}

/**
   Get debug selected
*/
bool Options::isAutonomous() {
  return ( options & 10 ) > 0;
}

/**
   Get visual inspection
*/
bool Options::hasVisual() {
  return ( options & 20 ) > 0;
}

/**
   Get visual inspection
*/
bool Options::hasBathymetry() {
  return ( options & 40 ) > 0;
}

void Options::getOptions() {
  getOptions( WebClient::OPTIONS, "", false);
  //Serial.print(F("Get options ")); Serial.println( String( options ));
}

/**
   Get the options
*/
bool Options::getOptions( int request, String msg, bool compound) {
  if ( !webClient.connect()) {
    return false;
  }
  String message = F("&msg=");
  if ( !compound )
    message += webClient.urlencode(msg);
  else
    message = msg;
  //Serial.print( "options request ("); Serial.print( request); Serial.print(F("): |" )); Serial.print( msg ); Serial.println("|");

  webClient.setContext( AQUABOTS_OPTIONS_CONTEXT );
  boolean result = webClient.sendHttp( request, false, message );
  if ( !result ) {
    Serial.print(F("Request options failed: ")); Serial.println( msg );
    webClient.disconnect();
    return false;
  }

  size_t capacity = JSON_OBJECT_SIZE(1) + 80;
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, webClient.client);
  if (error) {
    Serial.println(F("Parsing update failed!"));
    webClient.disconnect();
    return false;
  }
  JsonObject root = doc.as<JsonObject>();
  options = root["o"];
  //Serial.print(F("OPTIONS DATA " )); Serial.print( request); Serial.print(F(": " )); Serial.println( options);
  //serializeJson(doc, Serial);
  webClient.disconnect();
  return true;
}
