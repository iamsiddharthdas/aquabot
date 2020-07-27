Data::Data() {};

void Data:: send( int request, String senderId, String senderName, String deviceId, String deviceName, String type, String sentence ) {
  if ( sentence.length() == 0)
    return;
  String data = F("&sender-id=");
  data += senderId;
  data += F("&sender-name=");
  data += webClient.urlencode(senderName);
  data += F("&device-id=");
  data += deviceId;
  data += F("&device-name=");
  data += webClient.urlencode(deviceName);
  data+= F("&type="); 
  data += type;
  data += F("&data=");
  data += webClient.urlencode(sentence);  
  //Serial.print(F("READING ")); Serial.print(type); Serial.print(F(": ")); 
  //Serial.print(deviceName); Serial.print(F(" - "));Serial.print( sentence );
  //data += webClient.urlencode( data );
  //Serial.println( data );
  options.getOptions( request, data, true );
}

void Data:: send( int request, String deviceId, String deviceName, String type, String sentence ) {
  //Serial.print(F("\tSEND DATA:")); Serial.print(sentence); Serial.println(F("\n\n")); 
  send( request, VESSEL_ID, VESSEL, deviceId, deviceName, type, sentence );
}

void Data:: sendNMEA( String deviceId, String deviceName, String sentence ) {
  Serial.print(F("\tSEND NMEA: ")); Serial.print( deviceId); Serial.println(F(" ")); 
  Serial.print(deviceName); Serial.println(F(" ")); Serial.print(sentence); 
  Serial.println(F("\n\n")); 
  send( WebClient::NMEA, deviceId, deviceName, REQ_NMEA, sentence );
}
