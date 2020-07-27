WebClient::WebClient() {}

void WebClient::setup() {
  host = CONDAST_URL;
  port = PORT;
  context = AQUABOTS_REGISTRATION_CONTEXT;

  // start the Ethernet connection:
  Serial.print(F("SETUP WEB CLIENT: ")); Serial.println( ip );
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  Serial.print(F("WEB CLIENT..."));
  delay(2000);
  Serial.println(Ethernet.localIP());
  Serial.println(F("connecting..."));
  connect();
}

bool WebClient::connect() {
  Serial.print(F("Connecting to: ")); Serial.print( server ); Serial.print(F(":")); Serial.print( port ); Serial.print(F(" ..."));
  //client.setTimeout(5000);
  int result = client.connect(server, port);
  Serial.print(F("Connected: ")); Serial.println( result );
  if ( result) {
    Serial.print(F("success! "));
    Serial.println(Ethernet.localIP());
    Serial.println(Ethernet.gatewayIP());
    connected = result;
    return result;
  } else {
    Serial.println(F("failed. "));
    client.stop();
  }
}

void WebClient::disconnect() {
  client.stop();
  //if ( connected )
  //  Serial.println(F("Disconnecting: Complete "));
  connected = false;
}

void WebClient::setAuthentication( long i, String t ){
    id = i;
    token = t;
}

void WebClient::setContext( String c ){
  context = c;  
}

void WebClient::requestService( int request ) {
  switch ( request ) {
    case REGISTER_VESSEL:
      client.print(F("register"));
      break;
    case VESSEL_CONFIG:
      client.print(F("config"));
      break;
    case DEBUG:
      client.print(F("debug"));
      break;
    case FIELD:
      client.print(F("field"));
      break;
    case DATA:
      client.print(F("data"));
      break;
    case NMEA:
      client.print(F("nmea"));
      break;
    case OPTIONS:
      client.print(F("options"));
      break;
    case LOG:
      client.print(F("log"));
      break;
    case WAYPOINTS:
      client.print(F("waypoints"));
      break;
    case WAYPOINT:
      client.print(F("waypoint"));
      break;
    case UPDATE:
      client.print(F("update"));
      break;
    default:
      client.print(F("unknown"));
      break;
  }
}

/**
   Is used to transform the int to a String
*/
void WebClient::logRequestStr( int request ) {
  switch ( request ) {
    case REGISTER_VESSEL:
      Serial.print(F("register"));
      break;
    case VESSEL_CONFIG:
      Serial.print(F("config"));
      break;
    case DEBUG:
      Serial.print(F("debug"));
      break;
    case FIELD:
      Serial.print(F("field"));
      break;
    case DATA:
      Serial.print(F("data"));
      break;
    case NMEA:
      Serial.print(F("nmea"));
      break;
    case LOG:
      Serial.print(F("log"));
      break;
    case WAYPOINTS:
      Serial.print(F("waypoints"));
      break;
    case WAYPOINT:
      Serial.print(F("waypoint"));
      break;
    case UPDATE:
      Serial.print(F("update"));
      break;
    case OPTIONS:
      Serial.print(F("options"));
      break;
    default:
      Serial.print(F("unknown (")); Serial.print( request ); Serial.print(F(")"));
      break;
  }
}

boolean WebClient::sendHttp( int request, String message ) {
  String msg = message;
  if ( msg.length() > 0 ) {
    msg = F("&msg=");
    msg += message;
  }
  return sendHttp( request, false, msg );
}

boolean WebClient::sendHttp( int request, boolean post, String attrs ) {
  if ( client.connected()) {
    //if ( request != NMEA )
      //Serial.print(F("REQUEST ")); logRequestStr( request ); 
     // Serial.print(F(" ?id")); Serial.print( id );
      //Serial.print(F("&token")); Serial.print( token );
      //Serial.print(F(" ")); Serial.println(attrs );
    //logRequest( request, post, attrs );

    // Make a HTTP request:
    client.print( post ? F("POST ") : F("GET ") );
    client.print( context );
    //Serial.print(F("context: ")); Serial.print( context );
    requestService( request );
    client.print(F("?id=" ));
    client.print( id );
    client.print(F("&token="));
    client.print( token );
    if ( !post && ( attrs.length() > 0 )) {
      client.print( attrs );
    }
    client.println(F(" HTTP/1.1" ));

    client.print(F("Host: "));
    client.println( host );
    client.println(F("Connection: close\r\n"));
    if ( post && ( attrs.length() > 0 )) {
      client.println( F("Accept: */*"));
      client.println( F("Content-Type: application/x-www-form-urlencoded ; charset=UTF-8" ));
      client.print( F("Content-Length: "));
      client.println( attrs.length() );
      client.println();
      client.println( urlencode( attrs ));
    }
    client.println();
    return processResponse( request );
  }
  return false;
}

/**
   Handle the response, by taking away header info and such
*/
bool WebClient::processResponse( int request ) {
  // Check HTTP status
  char status[32] = {"\0"};
  client.setTimeout(HTTP_TIMEOUT);
  client.readBytesUntil('\r', status, sizeof(status));
  char http_ok[32] = {"\0"};
  strcpy( http_ok, "HTTP/1.1 200 OK");
  if (strcmp(status, http_ok) != 0) {
    Serial.print(F( "Unexpected response (" )); logRequestStr( request); Serial.print(F( "):" ));
    Serial.println(status);
    return false;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println( F( "Invalid response (" )); logRequestStr( request); Serial.print(F( "):" ));
    return false;
  }
  return true;
}

void WebClient::logRequest( int request, boolean post, String attrs ) {
  // Make a HTTP request:
  Serial.print( post ? F("POST ") : F("GET "));
  Serial.print( context );
  logRequestStr( request );
  Serial.print(F( "?id=" ));
  Serial.print( id );
  Serial.print(F( "&token=" ));
  Serial.print( token );
  if ( !post && ( attrs.length() > 0 )) {
    Serial.print( attrs );
  }
  Serial.print(F( " HTTP/1.1" ));
  Serial.println();
  Serial.print(F( "Host: "));
  Serial.println( host );
  Serial.println(F( "Connection: close" ));
  if ( post && ( attrs.length() > 0 )) {
    Serial.println(F( "Accept: */*" ));
    Serial.println(F( "Content-Type: application/x-www-form-urlencoded ; charset=UTF-8"));
    Serial.print(F( "Content-Length: "));
    Serial.println( attrs.length() );
    Serial.println();
    Serial.println( attrs );
  }
}

/**
   Creates a String request from the client
*/
String WebClient::printResponse( int request ) {
  Serial.print( F("RESPONSE TO "));
  logRequestStr( request );
  // Serial.print(" PROCESSING: ");
  //Serial.print( client.available() );
  String retval = "";

  //  Serial.println();
  while (client.available()) {
    char c = client.read();
    retval += c;
  }
  Serial.print( F( ": ")); Serial.println( retval );
}

void WebClient::loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (!client.connected()) {
    connect();
  }
}

/*
  ESP8266 Hello World urlencode by Steve Nelson
  URLEncoding is used all the time with internet urls. This is how urls handle funny characters
  in a URL. For example a space is: %20
  These functions simplify the process of encoding and decoding the urlencoded format.

  It has been tested on an esp12e (NodeMCU development board)
  This example code is in the public domain, use it however you want.
  Prerequisite Examples:
  https://github.com/zenmanenergy/ESP8266-Arduino-Examples/tree/master/helloworld_serial
*/
String WebClient::urldecode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == '+') {
      encodedString += ' ';
    } else if (c == '%') {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c = (h2int(code0) << 4) | h2int(code1);
      encodedString += c;
    } else {

      encodedString += c;
    }
    yield();
  }

  return encodedString;
}

String WebClient::urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;

}

unsigned char WebClient::h2int(char c)
{
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}
