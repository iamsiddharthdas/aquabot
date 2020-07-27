#ifndef Vessel_h
#define Vessel_h

#include "ServoController.h"
#include "doublePropellor.h"

#define AUTONOMY F("AUTONOMY")
#define WAYPOINTS_FILE F("waypoints.cfg")

#define LOOP_TIMEOUT 6000 //6 sec to cut the engine
#define MAX_WAYPOINTS 6 //The maximum amount of waypoints that can be stored
#define DEFAULT_RANGE 12;//12 mtrs

class Vessel {
    /**
       Vessel Data object
    */
    struct VesselData {
      int time;
      double latitude;//current position
      double longitude;
      double heading;
      double thrust;
      bool manual;
    };
    
    struct Waypoint {
      String name;
      double latitude;
      double longitude;
      bool complete;
      bool last;
    };

  public: Vessel();

    void setup();
    bool maintenance;
    bool initialise();
    void setCourse( double bearing, double thrust );//returns true if the course is within the turn angle
    void setAutonomy( bool autonomy );
    bool update( double latitude, double longitude, double bearing, double speed, bool updated );
    bool getWaypoint();
    void loop( double bearing);
    void interrupt( unsigned int loopCounter );
    void stop();

  private:
    bool enable;
    bool initialised;
    double bearing;//0-360
    double speed;
    unsigned int range;//The range in between which a location has been reached
    VesselData data;
    Waypoint waypoints[ MAX_WAYPOINTS ];
    unsigned int waypointIndex;
    DoublePropellor controller;
    //Servo referenceServo; //The Anna uses two motors, of which this one controls the reference
    //Servo speedServo;  // create servo object to control the speed
    bool runMaintenance( unsigned int counter );
    bool updateWaypoints();
};

#endif
