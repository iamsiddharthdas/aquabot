#include "DoublePropellor.h"

/**
   This servo controller is used for boats with two propellors, who'se heading is determined by the relative speed.
*/
DoublePropellor::DoublePropellor() {
};

void DoublePropellor::setup( ) {
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

bool DoublePropellor::initialise() {
  if (ServoController::initialise())
    return true;
  bool ready = ServoController::isReady();
  Serial.print(F("INITIALISING... "));
  ready = false;
  //while ( !ready ) {
  //  ready = encoder.initOffset();
  //}
  Serial.print( " Offset: "); //Serial.println( encoder.getOffset());
  return true;
}

bool DoublePropellor::maintenance() {
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
bool DoublePropellor::isReady( ) {
  return ServoController::isReady();
}
/**
    Used by interrupt handler
*/
void DoublePropellor::stop( ) {
  ServoController::stop();
}

void DoublePropellor::loop( double angle, double thrust  ) {
  Serial.print(F("SERVO: (")); Serial.print( angle ); Serial.print( ", "); Serial.print( thrust ); Serial.println( F(")"));
  //correct the angle to the thrust (0-180 => 0-90; 181-360 => -90-0)
  double corr = (( angle <= 180 ) ? angle : angle - 360) / 2;

  //Adjust the thrust to standard servo parameters
  double adjusted = map( thrust, -100, 100, 0, 180);
  double thrustLeft = ( adjusted - corr ) < 90 ? ( adjusted - corr) : ( adjusted - corr );
  if ((thrustLeft > (90 - heading_offset )) && (thrustLeft < 90 ))
    thrustLeft = thrustLeft - heading_offset;
  else if ((thrustLeft < (90 + heading_offset )) && (thrustLeft > 90 ))
    thrustLeft = thrustLeft + heading_offset;
  double thrustRight = ( adjusted + corr ) < 90 ? ( adjusted + corr) : ( adjusted + corr );
  if ((thrustRight > (90 - thrust_offset )) && (thrustRight < 90 ))
    thrustRight = thrustRight - thrust_offset;
  else if ((thrustRight < (90 + thrust_offset )) && (thrustRight > 90 ))
    thrustRight = thrustRight + thrust_offset;
  Serial.print(F("SETTING COURSE: (")); Serial.print( angle ); Serial.print( ", "); Serial.print( thrust );
  Serial.print(F("= ")); Serial.print( thrustLeft ); Serial.print( ", "); Serial.print( thrustRight ); Serial.println( ") ");
  //double diff = 0;//encoder.getDifferenceInPercent( bearing );
  //int turnSpeed = getTurnSpeed( diff );
  //Serial.print(F("Check angle for  ")); Serial.print( encoder.getEncoder()); Serial.print( F( " diff = " ));
  //Serial.print( diff ); Serial.print(F(": Turn Speed ")); Serial.println( turnSpeed );
  headingServo.write( thrustLeft );
  thrustServo.write( thrustRight );
}
