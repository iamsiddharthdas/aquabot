ServoController::ServoController() {};

void ServoController::setup( ) {
  //compass.setup();
  //compass.setFilter( 10 );
  heading_offset = -5;
  clipRange = SERVO_RANGE;
  heading_offset = 0;//sdcard.read( CONFIG, CLIP_RANGE ).toInt();
  headingServo.attach( PWM_OUT_HEADING );
  headingServo.write( 90 );//Standard servo range is 0 - 180, with 90 being stop
  angle = 0;
  enable = true;
  thrust_offset = 0;

  thrustServo.attach( PWM_OUT_THRUST );
  //only need to be set once
  //referenceServo.write( 90 );
  thrustServo.write( 90 );
}

boolean ServoController::initialise() {
  ready = true;
  return ready;
}

bool ServoController::maintenance() {
  int counter = 0;
  int br = 0;
  do {
    Serial.print("Moving to: "); Serial.println( br );
    do {
      counter++;
      counter %= 100;
      int speed = -100 + 2 * counter;
      angle = br;
      loop( br, 0);
      delay(100);
    } while ( counter != 0 );
    br -= 10;
    br = ( 360 + br ) % 360;
  } while (true);
}

double ServoController::getHeading( ) {
  return angle;
}

double ServoController::getThrust( ) {
  return thrust;
}
/**
   Used by interrupt handler
*/
void ServoController::toggle( ) {
  /* Default nothing */
}

bool ServoController::isReady() {
  return ready;
}

/**
   Converts an angle (0-360) to a form that fits the servo
   (0 - 180 ) => 90 - 180
   (181-360)  => 0 - 90
*/
double ServoController::getCorrectedAngle( double a ) {
  return 90-a;
}

/**
   get the angle for the servo, based on the desired heading
*/
void ServoController::stop( ) {
  headingServo.write( 90 ); //only needs to be set once
  thrustServo.write( 90 );
  angle = 0;
  thrust = 0;
}

void ServoController::loop( double a, double t) {
  angle = getCorrectedAngle( a);
  thrust = map( t, -100, 100, 0, 180 );
  Serial.print(F("\n\nCourse: (")); Serial.print( angle); Serial.print(F(", ")); Serial.println( thrust);

  //compass.loop();
  //if ( compass.isEnabled() ) {
  //  heading = compass.getFiltered();
  //} else if ( tendof.isEnabled() ) {
  //  heading = tendof.getHeading();
  //} else {
  //heading = heading;
  //}
  //double diff = heading - heading;
  //erial.print(F("\n\nCorrecting: ")); Serial.println( diff + heading_offset);
  //int newheading = map(( heading_offset + diff ), 0, 360, clipRange, 180 - clipRange );
  Serial.print( "Angle: " ); Serial.println( angle + heading_offset ); 
  Serial.print( "Thrust: " ); Serial.println( thrust + thrust_offset ); 
  headingServo.write( angle + heading_offset );
  thrustServo.write( thrust + thrust_offset );
}

void ServoController::loop( double h) {
  loop( h, thrust );
}
