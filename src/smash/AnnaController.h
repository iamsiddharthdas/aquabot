#ifndef AnnaController_h
#define AnnaController_h

#define SERVO_ENCODER_ID "org.rdm.aquabots.motion.servo.encoder"
#define SERVO "Servo Controller for the Encoder"

#define TURN_ACTIVE F("TURN_ACTIVE")
#define TURN_SPEED F("TURN_SPEED")//25
#define TURN_ANGLE F("TURN_ANGLE")//3

//The PWM outputs are the orange connectors on the Ethernet shield
#define PWM_OUT_REFERENCE 5 //White grove connection  (blue) thrust
#define PWM_OUT_AP_SELECT 7 //Yellow grove connection  (blue) 4 selectie ap...do not use

class AnnaController:ServoController {

  public: AnnaController(void);
    void setup() override;
    bool initialise() override;
    virtual bool isReady() override;
    bool maintenance() override;
    void stop() override;
    void loop( double angle, double thrust ) override;

  private: 
   //The Anna uses two motors, of which this one controls the reference
   Servo referenceServo;  //create servo object to activate the servos
};

#endif
