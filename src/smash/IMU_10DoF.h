#ifndef Imu10DoF_h
#define Imu10DoF_h

#include "Wire.h"

// I2Cdev and MPU9250 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU9250.h"
#include "BMP280.h"

#define IMU_10_DOF_ID F("com.seeed.grove.imu10dof")
#define IMU_10_DOF F("IMU_10_DOF")
#define IMU_10_DOF_DATA F("imu-data")

#define SAMPLE_NUM_MDATE  5000

/**
 * 10 degrees of Freedom board.
 * @See: http://wiki.seeedstudio.com/Grove-IMU_10DOF/
 */
class Imu10DoF {

  public: Imu10DoF(void);
    void setup();
    bool isEnabled();
    double getHeading(void);
    void getTiltHeading(void);
    void Mxyz_init_calibrated ();
    void getCalibrationData();
    void get_one_sample_date_mxyz();
    void getAccelData(void);
    void getGyroData(void);
    void getCompassData(void);
    void getCompassDateCalibrated ();
    void loop();

  private: bool enabled;
    // class default I2C address is 0x68
    // specific I2C addresses may be passed as a parameter here
    // AD0 low = 0x68 (default for InvenSense evaluation board)
    // AD0 high = 0x69
    MPU9250 accelgyro;
    I2Cdev   I2C_M;

    uint8_t buffer_m[6];


    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t   mx, my, mz;

    float heading;
    float tiltheading;

    float Axyz[3]; //Acceleration
    float Gxyz[3]; //Gyro
    float Mxyz[3];

    volatile float mx_sample[3];
    volatile float my_sample[3];
    volatile float mz_sample[3];

    static float mx_centre = 0;
    static float my_centre = 0;
    static float mz_centre = 0;

    volatile int mx_max = 0;
    volatile int my_max = 0;
    volatile int mz_max = 0;

    volatile int mx_min = 0;
    volatile int my_min = 0;
    volatile int mz_min = 0;


    float temperature;
    float pressure;
    float atm;
    float altitude;
    BMP280 bmp280;
};

#endif
