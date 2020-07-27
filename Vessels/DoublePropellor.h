#ifndef DoublePropellor_h
#define DoublePropellor_h

#define SERVO_ENCODER_ID "org.rdm.aquabots.motion.servo.encoder"
#define SERVO "Servo Controller for the Encoder"

#define TURN_ACTIVE F("TURN_ACTIVE")
#define TURN_SPEED F("TURN_SPEED")//25
#define TURN_ANGLE F("TURN_ANGLE")//3

class DoublePropellor : ServoController {

  public: DoublePropellor(void);
    //Encoder encoder;
    void setup() override;
    bool initialise() override;
    virtual bool isReady() override;
    bool maintenance() override;
    void stop() override;
    void loop( double angle, double thrust ) override;
};

#endif
