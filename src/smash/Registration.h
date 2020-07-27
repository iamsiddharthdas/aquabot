#ifndef Registration_h
#define Registration_h

#define REGISTRATION "Registration"
#define REGISTRATION_ID "registration"

class Registration {

  private:
    bool enabled; //general purpose flag 
    long vesselId; 

  public: Registration(void);
    void setup();
    long registerVessel( String name, String passphrase, double latitude, double longitude);
    bool getConfig();
};

#endif
