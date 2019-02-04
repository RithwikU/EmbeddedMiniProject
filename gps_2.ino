/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
import <math.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      }
    if(gps.location.lat()>= && gps.location.lat()<=13.1 && gps.location.lng()>=73.0 && gps.location.lng()<=75.0)
    {Serial.println("Surathkal");}
    if(gps.speed.isValid())
    {
      Serial.print("Speed=");
      Serial.println(gps.speed.kmph(),6);
      }
    }
  }
}
