void GPSFunction() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void GPSSerialAvailability() {
   while (Serial2.available() > 0){
  if (gps.encode(Serial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
   // while(true);
  }
}
}

void displayInfo()
{
  if (gps.location.isValid()) {
    latitudeVar  = (gps.location.lat() * 1000);
    longitudeVar = (gps.location.lng() * 1000);
  } else {
    latitudeVar  = 0;
    longitudeVar = 0;
  }


  if (gps.time.isValid()) {
    int timeH = gps.time.hour() + 8;
    if (timeH >= 24) {
      timeH = timeH - 24;
    }
    
    if (gps.time.hour() < 10);
    HourVar = timeH;

    if (gps.time.minute() < 10);
    MinutesVar = gps.time.minute();

    if (gps.time.second() < 10);
    SecondVar = gps.time.second();

    if (gps.time.centisecond() < 10);
    CentiSecondVar = gps.time.centisecond();
  } else {
    HourVar        = 0;
    MinutesVar     = 0;
    SecondVar      = 0;
    CentiSecondVar = 0;
  }

   if (gps.date.isValid()) {
    int timeH = gps.time.hour() + 8;
    MonthVar  = gps.date.month();
    DayVar    = gps.date.day();
    YearVar   = gps.date.year();

    if (timeH >= 24) {
      
    }
  } else {
    MonthVar = 0;
    DayVar   = 0;
    YearVar  = 0;
  }
}