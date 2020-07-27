Imu10DoF::Imu10DoF() {};

void Imu10DoF::setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  accelgyro.initialize();
  bmp280.init();

  // verify connection
  Serial.println(F("Testing device connections..."));

  enabled = accelgyro.testConnection();
  Serial.println(enabled ? F("MPU9250 connection successful") : F("MPU9250 connection failed"));

  Serial.println("     ");

  //  Mxyz_init_calibrated ();
}

bool Imu10DoF::isEnabled() {
  return enabled;
}

/**
   Get the heading of the vessel
*/
double Imu10DoF::getHeading(void)
{
  heading = 180 * atan2(Mxyz[1], Mxyz[0]) / PI;
  if (heading < 0) heading += 360;
  return heading;
}

void Imu10DoF::getTiltHeading(void)
{
  float pitch = asin(-Axyz[0]);
  float roll = asin(Axyz[1] / cos(pitch));

  float xh = Mxyz[0] * cos(pitch) + Mxyz[2] * sin(pitch);
  float yh = Mxyz[0] * sin(roll) * sin(pitch) + Mxyz[1] * cos(roll) - Mxyz[2] * sin(roll) * cos(pitch);
  float zh = -Mxyz[0] * cos(roll) * sin(pitch) + Mxyz[1] * sin(roll) + Mxyz[2] * cos(roll) * cos(pitch);
  tiltheading = 180 * atan2(yh, xh) / PI;
  if (yh < 0)    tiltheading += 360;
}

void Imu10DoF::Mxyz_init_calibrated ()
{
  Serial.println(F("Before using 9DOF,we need to calibrate the compass frist,It will takes about 2 minutes."));
  Serial.print("  ");
  Serial.println(F("During  calibratting ,you should rotate and turn the 9DOF all the time within 2 minutes."));
  Serial.print("  ");
  Serial.println(F("If you are ready ,please sent a command data 'ready' to start sample and calibrate."));
  while (!Serial.find("ready"));
  Serial.println("  ");
  Serial.println("ready");
  Serial.println("Sample starting......");
  Serial.println("waiting ......");

  getCalibrationData ();

  Serial.println("     ");
  Serial.println("compass calibration parameter ");
  Serial.print(mx_centre);
  Serial.print("     ");
  Serial.print(my_centre);
  Serial.print("     ");
  Serial.println(mz_centre);
  Serial.println("    ");
}


void Imu10DoF::getCalibrationData ()
{
  for (int i = 0; i < SAMPLE_NUM_MDATE; i++)
  {
    get_one_sample_date_mxyz();
    if (mx_sample[2] >= mx_sample[1])mx_sample[1] = mx_sample[2];
    if (my_sample[2] >= my_sample[1])my_sample[1] = my_sample[2]; //find max value
    if (mz_sample[2] >= mz_sample[1])mz_sample[1] = mz_sample[2];

    if (mx_sample[2] <= mx_sample[0])mx_sample[0] = mx_sample[2];
    if (my_sample[2] <= my_sample[0])my_sample[0] = my_sample[2]; //find min value
    if (mz_sample[2] <= mz_sample[0])mz_sample[0] = mz_sample[2];
  }
  mx_max = mx_sample[1];
  my_max = my_sample[1];
  mz_max = mz_sample[1];

  mx_min = mx_sample[0];
  my_min = my_sample[0];
  mz_min = mz_sample[0];

  mx_centre = (mx_max + mx_min) / 2;
  my_centre = (my_max + my_min) / 2;
  mz_centre = (mz_max + mz_min) / 2;
}

void Imu10DoF::get_one_sample_date_mxyz()
{
  getCompassData();
  mx_sample[2] = Mxyz[0];
  my_sample[2] = Mxyz[1];
  mz_sample[2] = Mxyz[2];
}

void Imu10DoF::getAccelData(void)
{
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  Axyz[0] = (double) ax / 16384;
  Axyz[1] = (double) ay / 16384;
  Axyz[2] = (double) az / 16384;
}

void Imu10DoF::getGyroData(void)
{
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  Gxyz[0] = (double) gx * 250 / 32768;
  Gxyz[1] = (double) gy * 250 / 32768;
  Gxyz[2] = (double) gz * 250 / 32768;
}

void Imu10DoF::getCompassData(void)
{
  I2C_M.writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01); //enable the magnetometer
  delay(10);
  I2C_M.readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);

  mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0] ;
  my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2] ;
  mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4] ;

  Mxyz[0] = (double) mx * 1200 / 4096;
  Mxyz[1] = (double) my * 1200 / 4096;
  Mxyz[2] = (double) mz * 1200 / 4096;
}

void Imu10DoF::getCompassDateCalibrated ()
{
  getCompassData();
  Mxyz[0] = Mxyz[0] - mx_centre;
  Mxyz[1] = Mxyz[1] - my_centre;
  Mxyz[2] = Mxyz[2] - mz_centre;
}

void Imu10DoF::loop() {
  temperature = bmp280.getTemperature(); //Get the temperature, bmp180ReadUT MUST be called first
  pressure = bmp280.getPressure();//Get the temperature
  altitude = bmp280.calcAltitude(pressure); //Uncompensated caculation - in Meters
  atm = pressure / 101325;
  Serial.print(F("IMU Board: t(")); Serial.print( temperature ); Serial.print(F("), P(")); Serial.print( pressure ); Serial.print(F("), alt(")); Serial.println( altitude );
  Serial.print(F("Compass: ")); Serial.println( getHeading() );
  String str = "a=" + String( altitude ) + ";p=" + String( pressure ) + ";t=" + String( temperature );// + F(",c=") + pressure + 
  data.send(WebClient::DATA, IMU_10_DOF_ID, IMU_10_DOF, IMU_10_DOF_DATA, str );

}
