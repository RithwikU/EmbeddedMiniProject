/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

String stations[5] = {"A","B","C","D","E"};
double Lat[5]= {5,7,9,11,13};
double Long[5] = {67,69,71,73,75};
int nextStationIndex=0;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}
float degtoRadians(float a)
{
  return a*PI/180.0;
}
float calcDist(float lat1,float long1,float lat2,float long2)
{
  float del_phi = lat2- lat1;
  float del_lambda = long2-long1;
  float a = pow(sin(del_phi/2),2) + cos(lat1)*cos(lat2)*pow(sin(del_lambda),2);
  float c= 2*atan2(sqrt(a),sqrt(1-a));
  float d = 6371000*c;
  return d;
}
void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  //Serial.println(calcDist(degtoRadians(12.980308),degtoRadians(74.803310),degtoRadians(12.899663),degtoRadians(74.843304)));
  //while (ss.available() > 0){
  while(Serial.available()>0){
    
    gps.encode(ss.read());
    //if (gps.location.isUpdated()){
      float minDist=1000000000;
      int minIndex=nextStationIndex;
      float currentLat = 8;//Serial.parseFloat();//gps.location.lat();
      Serial.println(currentLat);
      float currentLong = 70;//Serial.parseFloat();//gps.location.lng();
      Serial.println(currentLong);
      for(int i=nextStationIndex+1;i<5;i++)
      {
        float dist = calcDist(degtoRadians(currentLat),degtoRadians(currentLong),degtoRadians(Lat[i]),degtoRadians(Long[i]));
        Serial.print("Distance=");
        Serial.println(dist);
        if( dist < minDist)
        {
          minDist = dist;
          minIndex = i;
        }
      }
      nextStationIndex = minIndex;
      //Serial.print("Latitude= "); 
      //Serial.print(gps.location.lat(), 6);
      //Serial.print(" Longitude= "); 
      //Serial.println(gps.location.lng(), 6);
      Serial.print("Next stop is ");
      Serial.println(stations[nextStationIndex]);
      }
//    if(gps.location.lat()>= 12.9 && gps.location.lat()<=13.1 && gps.location.lng()>=73.0 && gps.location.lng()<=75.0)
//    {Serial.println("Surathkal");}
    if(gps.speed.isValid())
    {
      Serial.print("Speed=");
      Serial.println(gps.speed.kmph(),6);
      }
    //}
  }
