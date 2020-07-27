//#include "Compass.h"

#include <Servo.h>

#ifndef ServoController_h
#define ServoController_h

#define SERVO_ID "org.rdm.aquabots.motion.servo"
#define SERVO "Servo Controller"

#define SPEED_OFFSET F("SPEED_OFFSET")//-4
#define HEADING_OFFSET F("HEADING_OFFSET")//-4

#define SERVO_RANGE 45 //The clip range of the servo (45-135 in this case)
#define TURN F("TURN")
#define TURN_OFFSET F("TURN_OFFSET") //-5
#define CLIP_RANGE F("CLIP_RANGE")

//The PWM outputs are the orange connectors on the Ethernet shield
#define PWM_OUT_HEADING 4 //White grove connection  (green)
#define PWM_OUT_SPEED   5 //Yellow grove connection (orange)

#define MIN_SERVO 10   // 32 USV_RDM
#define MAX_SERVO 170 // 160 USV_RDM


class ServoController {

 public: ServoController(void);
    virtual bool isReady();
    virtual void setup();
    virtual bool initialise();
    virtual double getHeading();
    virtual double getThrust();
    virtual bool maintenance();
    virtual void stop();
    virtual void toggle();
    
    /**
     * The ranges of the serve controller are defined as follows:
     * - angle (0-360)
     * - thrust -100% to 100%
     */
    virtual void loop( double angle, double thrust );
    virtual void loop( double angle );//convenience method..keeps the speed the same

  protected:
    double angle;//The rudder angle (0-360)
    double thrust;//the thrust
    int thrust_offset; //offset for speed motor
    int heading_offset;
    //Compass compass;
    Servo headingServo;  // create servo object to control the heading
    Servo thrustServo;  // create servo object to control the thrust
    bool initialised;
    bool ready;
    bool enable;

    /**
     * Converts an angle (0-360) to a form that fits the servo  
     */
    double getCorrectedAngle( double angle );
    
    //the offset between the bearing and the desired angle. Depends on the servo that is used
    //and/or the mounitng of the compass

  private:
    int clipRange;
};

#endif
