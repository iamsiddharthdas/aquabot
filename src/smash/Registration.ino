Registration::Registration() {};

void Registration::setup( ) {
  enabled = true;
}

long Registration::registerVessel( String vesselName, String passphrase, double latitude, double longitude ) {
  if ( !enabled )
    return -1;
  if ( !webClient.connect() )
    return -2;

  webClient.setContext( AQUABOTS_REGISTRATION_CONTEXT ); 
  Serial.print(F("Registering Vessel: ")); Serial.println( vesselName );
  String url = F("&name=");
  url += String( vesselName );
  url += F("&passphrase=");
  url += String( passphrase);
  url += F("&latitude=");
  url += String( latitude);
  url += F("&longitude=");
  url += String( longitude);

  boolean result = webClient.sendHttp( WebClient::REGISTER_VESSEL, false, url);
  if (!result ) {
    webClient.disconnect();
    return -3;
  }
  String retval = "";
  while (webClient.client.available()) {
    char c = webClient.client.read();
    retval += c;
  }
  Serial.println( retval);
  vesselId = atol( retval.c_str() );
  webClient.disconnect();
  Serial.print(F("Vessel Registered: ")); Serial.println( vesselId );
  return vesselId;
}

bool Registration::getConfig() {
}
