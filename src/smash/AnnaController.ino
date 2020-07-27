#include "AnnaController.h"

/**
   This servo controller is used for boats with two propellors, who'se heading is determined by the relative speed.
*/
AnnaController::AnnaController() {
};

void AnnaController::setup( ) {
  referenceServo.attach( PWM_OUT_REFERENCE );
  referenceServo.write( 90 );
  Serial.println("REFERENCE SERVO SET");
  ServoController::setup();
  heading_offset = 6;
  thrust_offset = 6;

  //turn_active = sdcard.read( CONFIG, TURN_ACTIVE ).toInt();
  //turn_speed = sdcard.read( CONFIG, TURN_SPEED ).toInt();
  //turn_angle = sdcard.read( CONFIG, TURN_ANGLE ).toInt();
  //turn = sdcard.read( CONFIG, TURN ).toInt();
  //if ( turn < turn_active )
  //  turn = turn_active;
}

bool AnnaController::initialise() {
  if (ServoController::initialise())
    return true;
  bool ready = ServoController::isReady();
  Serial.print(F("INITIALISING... "));
  ready = false;
  Serial.print( " Offset: "); //Serial.println( encoder.getOffset());
  return true;
}

bool AnnaController::maintenance() {
  int counter = 0;
  int br = 0;
  do {
    Serial.print("Moving to: "); Serial.println( br );
    do {
      counter++;
      counter %= 100;
      int speed = -100 + 2 * counter;
      angle = br;
      loop( 90, 0);
      delay(100);
    } while ( counter != 0 );
    br -= 10;
    br = ( 360 + br ) % 360;
  } while (true);
}

/**
    Used by interrupt handler
*/
bool AnnaController::isReady( ) {
  return ServoController::isReady();
}
/**
    Used by interrupt handler
*/
void AnnaController::stop( ) {
  ServoController::stop();
}

void AnnaController::loop( double angle, double thrust  ) {
  ServoController::loop( angle, thrust );
}
