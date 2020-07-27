#ifndef Data_h
#define Data_h

#define REQ_NMEA F("nmea")

class Data {

  public: Data(void);
    void send( int request, String deviceName, String deviceId, String type, String sentence );
    void send( int request, String senderId, String senderName, String deviceId, String deviceName, String type, String sentence );
    void sendNMEA( String deviceId, String deviceName, String sentence );
};

#endif
