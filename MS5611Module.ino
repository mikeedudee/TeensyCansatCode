void MS5611Function(){
Serial.begin(9600);

  // Initialize MS5611 sensor
  //Serial.println("Initialize MS5611 Sensor");

  while(!ms5611.begin()) {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }

  // Get reference pressure for relative altitude
  referencePressure = ms5611.readPressure();

  // Check settings
  checkSettings();
}

void checkSettings() {
  //Serial.print("Oversampling: ");
  //Serial.println(ms5611.getOversampling());o-
}

void MS5611Readings() {
  uint32_t rawTemperature = ms5611.readRawTemperature();
  uint32_t rawPressure    = ms5611.readRawPressure();
  realTemperature         = ms5611.readTemperature();
  realPressure            = ms5611.readPressure();
  absoluteAltitude        = ms5611.getAltitude(realPressure);
  relativeAltitude        = ms5611.getAltitude(realPressure, referencePressure);
}