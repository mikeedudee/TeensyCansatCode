// MS5611 — Altimeter


#include <Wire.h>
#include <MS5611.h>
MS5611 ms5611;
double referencePressure;
double realTemperature;
long realPressure;
float absoluteAltitude;
float relativeAltitude;

// GPS Global Variables and constants
#include <TinyGPS++.h>
TinyGPSPlus gps;
float latitudeVar, longitudeVar;
int MonthVar, DayVar, YearVar, HourVar, MinutesVar, SecondVar, CentiSecondVar;

// Time Elapsed ------------//
unsigned long TimeElapsedVar;

// GYRO -------------------//
#include <Arduino.h>
#include <Adafruit_BNO08x.h>
// For SPI mode, we need a CS pin
#define BNO08X_CS 21
#define BNO08X_INT 22
#define BNO08X_RESET -1

struct euler_t {
  float yaw;
  float pitch;
  float roll;
} ypr;

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

#ifdef FAST_MODE
  // Top frequency is reported to be 1000Hz (but freq is somewhat variable)
  sh2_SensorId_t reportType = SH2_GYRO_INTEGRATED_RV;
  long reportIntervalUs     = 2000;
#else
  // Top frequency is about 250Hz but this report is more accurate
  sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
  long reportIntervalUs     = 5000;
#endif
void setReports(sh2_SensorId_t reportType, long report_interval) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(reportType, report_interval)) {
    Serial.println("Could not enable stabilized remote vector");
  }
}

double sensorStatusValue, YawStat, PitchStat, RollStat, nowLast, AccelerometerX, AccelerometerY, AccelerometerZ, LinearAccelerationX, LinearAccelerationY, LinearAccelerationZ;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, OUTPUT);

  //setupGyro();
  MS5611Function();
  GPSFunction();
}

void loop() {
  //loopingGyroSensor();
  MS5611Readings();
  GPSSerialAvailability();

  TimeElapsedVar = millis() / 1000;

  // FORMAT: Average Temperature [0], Real Pressure [1], Relative Altitude [2], Latitude [3], Longitude [4], Month [5], Day [6], Year [7], Hour [8], Min [9], Sec [10], GyroSensorCalibration Status [11], Yaw [12], Pitch [13], Roll [14], Accelerometer (x,y,z) [15], Linear Acceleration (x,y,z) [16], Time Elapsed [17], Data Written (0 or 1) [18]
  double dataArray[] = {realTemperature, realPressure, relativeAltitude, latitudeVar, longitudeVar, 
  MonthVar, DayVar, YearVar, HourVar, MinutesVar, SecondVar, sensorStatusValue, YawStat, PitchStat, 
  RollStat, AccelerometerX, AccelerometerY, AccelerometerZ, TimeElapsedVar};
  
  for (int i = 0; i < 19; i++) {
    Serial.print(dataArray[i]);
    Serial.print("\t");
  }
  Serial.println(" ");
  digitalWrite(LED_BUILTIN, HIGH);
}
