#ifndef LatLng_h
#define LatLng_h

#include "math.h"

/**
   the length of one degree of latitude (and one degree of longitude at equator) in meters.
*/
#define DEGREE_DISTANCE_AT_EQUATOR 111329
/**
   the radius of the earth in meters.
*/
#define EARTH_RADIUS 6371370 //meters
/**
   the length of one minute of latitude in meters, i.e. one nautical mile in meters.
*/
#define MINUTES_TO_METERS 1852d
/**
   the amount of minutes in one degree.
*/
#define DEGREE_TO_MINUTES 60d

#define RADIAN_CONVERSION  71/4068

class LatLng {

  public: LatLng(void);

    double toRadians( int degree );
    int toDegrees( double radians );
    double haversin(double val);
    double haversine( double rlat1, double rlat2, double dLat, double dLon, double el1, double el2);
    double lngDistance( double lat1, double lon1, double lat2, double lon2, double el1, double el2 ) ;
    double latDistance( double lat1, double lon1, double lat2, double lon2, double el1, double el2 );
    struct VesselData getVesseldata( double rlat1, double rlat2, double dLat, double dLon );
};

#endif
