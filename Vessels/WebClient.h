#ifndef WebClient_h
#define WebClient_h

#include <SPI.h>
#include <Ethernet.h>

#define AQUABOTS_REGISTRATION_CONTEXT F("/arnac/registration/")
#define AQUABOTS_VESSEL_CONTEXT F("/arnac/rest/")
#define CONDAST_URL F("www.condast.com")

const unsigned long HTTP_TIMEOUT = 5000;// max respone time from server


//Condast SERVER
// Set the static IP address to use if the DHCP fails to assign
//const char server[] = "www.condast.com";
//IPAddress ip(79, 170, 90, 5);
//const int PORT = 8080;

//LOCALHOST
// Set the static IP address to use if the DHCP fails to assign
IPAddress server(192, 168, 178, 41);
IPAddress ip(192, 168, 178, 41);
const int PORT = 10080;

//Huawei
//IPAddress server(192,168,8,100);
//IPAddress ip(192,168,8,100);
//const int PORT = 10081;

//Havenlab
//IPAddress server(192,168,10,110);
//IPAddress ip(192,168,10,110);
//const int PORT = 10080;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
const byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

class WebClient {

  public: WebClient();
    enum request {
      UNKNOWN = 0,
      REGISTER_VESSEL = 1,
      VESSEL_CONFIG = 2,
      DEBUG = 3,
      FIELD = 4,
      UPDATE = 5,
      WAYPOINTS = 6,
      DATA = 7,
      NMEA = 8,
      OPTIONS = 9,
      LOG = 10,
      WAYPOINT = 11
     };

    const unsigned long HTTP_TIMEOUT = 5000;// max respone time from server

    EthernetClient client;
    void setup();
    bool connect();
    void disconnect();
    void setAuthentication( long id, String token ); 
    void setContext( String context ); 
    bool requestLog();
    bool logMessage( String message );
    bool getWaypoint();
    bool sendUpdate( String url );
    bool sendHttp( int request, String msg );
    bool sendHttp( int request, boolean post, String attrs );
    String urlencode(String str);
    String printResponse( int request );
    void logRequest( int request, boolean post, String attrs );//for debugging
    void logRequestStr( int request ); //dito
    void loop();

  private:
    String host;
    int port;
    bool connected;
    String context;
    long id;
    String token;

    // Initialize the Ethernet client library
    // with the IP address and port of the server
    // that you want to connect to (port 80 is default for HTTP):
    void requestService( int request );
    bool processResponse( int request );
    boolean update( JsonObject& root );
    String urldecode(String str);
    unsigned char h2int(char c);
};

#endif
