#ifndef Interrupts_h
#define Interrupts_h

#define SECONDS 10 //0.1 sec
#define TEN_SEC 40
#define MINUTES 600

class Interrupts {

  private:
    //Create a sempahore
    bool lock;

  public: Interrupts(void);
    int int_counter;
    bool flank; //10Hz
    bool sec_flank;//seconds
    bool min_flank;//minutes
    bool tensec_flank;//10 sec.

    void setup();
    void clear();
    bool getLock();
    void setLock( bool lock );
    bool getFlank();
    bool getSecondsFlank();
    void clearSecondsFlank();
    void clearFlank();
    int getCounter();
};
#endif
