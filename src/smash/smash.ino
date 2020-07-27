#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "WebClient.h"
#include "Registration.h"
#include "TinyGPS.h"
#include "LatLng.h"
#include "Vessel.h"
#include "ServoController.h"
#include "Interrupts.h"
#include "Logger.h"
#include "Options.h"
#include "Data.h"
#include "Garmin.h"
#include "Compass.h"
#include "IMU_10DoF.h"

#define VESSEL_ID F("org.rdm.coe.anna")
#define VESSEL F("Anna")

#define PASSPHRASE F("AquabotsRule")
#define LATITUDE 51.2
#define LONGITUDE 4.2
#define TIME_OUT 3000 //msec
#define REFRESH 10

static WebClient webClient;
static Registration registration;
static TinyGPS gps;
static Vessel vessel;
static Interrupts interrupt;
static Logger logger;
static Options options;
static Data data;
static Compass compassModule;
static Garmin garminModule;
static Imu10DoF imuDofmodule;

long vesselId;
int load;

void setup() {
  load = 0;
  Serial.begin(9600);
  Serial.print(F("Setup Vessel: ")); Serial.println( VESSEL );
  vesselId = -1;
  webClient.setup();
  interrupt.setup();
  registration.setup();
  gps.setup();
  options.setup();
  compassModule.setup();
  garminModule.setup();
  vessel.setup();
}

void loop() {
  bool enabled = ( vesselId >= 0 );
  gps.loop( enabled);
  compassModule.loop( );
  //imu10DofModule.loop();
  if ( interrupt.getSecondsFlank()) {
    interrupt.clearSecondsFlank();
    load = ( load + 1 ) % 120;
    int balance = ( !enabled) ? 0 : load % REFRESH;
    //Serial.println( balance );
    switch ( balance ) {
      case 0:
        if ( !enabled ) {
          vesselId =  registration.registerVessel( VESSEL, PASSPHRASE, gps.getLatitude(), gps.getLongitude() );
          if ( vesselId >= 0 ) {
            Serial.print(F("REGISTERED VESSEL: ")); Serial.println( vesselId );
            webClient.setAuthentication( vesselId, PASSPHRASE );
          } else
            Serial.print(F("REGISTRATION FAILED: ")); Serial.println( vesselId );
        }
        //Serial.print(F("VESSEL: ")); Serial.println( vesselId );
        delay(1000);
        break;
      case 1:
        logger.setup();
        //Serial.println( "LOGGER SETUP COMPLETE" );
        break;
      case 2:
        //Serial.println( "Aquabots message" );
        logger.println("HELLO AQUABOTS");
        break;
      case 9:
        options.getOptions();
        //Serial.println( "OPTIONS RECEIVED" );
        break;
      default:
        break;
    }
    Serial.println( "\n\nUPDATING VESSEL" );
    vessel.loop( enabled, compassModule.getHeading());
  }
}
