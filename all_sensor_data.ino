#define  ledYellow 6
#define ledRed 7
#define trigPin 10
#define echoPin 9
#define irPin 8
#define pirPin 11
#define tempSensorPin A0
#define rainPin A1
#define ldrPin A3

int isObstacle = LOW;
int pirState = LOW;
int val = 0;

int ldrIntensity;
int data;

float tempc;
float tempf;
float vout;

const int tempSensorPinMin = 0;     // tempSensorPin minimum
const int tempSensorPinMax = 1024;  // tempSensorPin maximum

#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
float lat = 28.5458, lon = 77.1703; // create variable for latitude and longitude object
SoftwareSerial EEBlue(2, 3);
SoftwareSerial gpsSerial(4, 5); //rx,tx
void setup() {
  Serial.begin (9600);
  EEBlue.begin(9600);
  gpsSerial.begin(9600);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(ldrPin, INPUT);

  pinMode(irPin, INPUT);
  delay(100);
}

void loop() {
  // ledAlternate();
  //ultraSonicData();
  //  irObstacle();
  //  pirData();
  //  tempData();
  //  ldrData();
  //  rainData();
  //  gpsData();

  Serial.println();
  Serial.print((String)ultraSonicData());
  Serial.print(',');
  Serial.print((String)irObstacleData());
  Serial.print(',');
  Serial.print((String)pirData());
  Serial.print(',');
  Serial.print((String)tempData());
  Serial.print(',');
  Serial.print((String)ldrData());
  Serial.print(',');
  Serial.print((String)rainData());
  Serial.print(',');
  Serial.print((String)gpsDataLatitude());
  Serial.print(',');
  Serial.print((String)gpsDataLongitude());
  Serial.print(',');
  delay(1000);
}



void ledAlternate() {
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledRed, LOW);
  delay(100);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, HIGH);
  delay(100);
}

long ultraSonicData() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

int irObstacleData() {
  isObstacle = digitalRead(irPin);
  if (isObstacle == HIGH)
  {
    //Serial.println("OBSTACLE!!");
    return 1;
  }
  else
  {
    //Serial.println("clear");
    return 0;
  }
}

int pirData() {
  val = digitalRead(pirPin);
  if (val == HIGH) {
    // digitalWrite(ledPin, HIGH);
    if (pirState == LOW) {
      //Serial.println("Motion detected!");
      pirState = HIGH;
      return 1;
    }
  } else {
    // digitalWrite(ledPin, LOW);
    if (pirState == HIGH) {
      //Serial.println("Motion ended!");
      pirState = LOW;
      return 0;
    }
  }
}

float tempData() {
  vout = analogRead(tempSensorPin);
  vout = (vout * 500) / 1023;
  tempc = vout;
  //tempf=(vout*1.8)+32; // Converting to Fahrenheit
  //Serial.println(tempc);
  return tempc;
}

int ldrData() {
  ldrIntensity = analogRead(ldrPin);
  //Serial.println("LDR Intensity");
  return ldrIntensity;
}

int rainData() {
  int sensorReading = analogRead(rainPin);
  // int range = map(sensorReading, sensorMin, sensorMax, 0, 3); // map the sensor range (four options)
  // switch (range) { // range value
  //  case 0:    // Sensor getting wet
  //   Serial.println("Flood");
  //   break;
  //  case 1:    // Sensor getting wet
  //   Serial.println("Rain Warning");
  //   break;
  //  case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
  //   Serial.println("Not Raining");
  //   break;
  // }
  //delay(1);
  return sensorReading;
}

String gpsDataLatitude() {
  while (gpsSerial.available()) { // check for gps data
    if (gps.encode(gpsSerial.read())) // encode gps data
    {
      gps.f_get_position(&lat, &lon); // get latitude and longitude
      //  Serial.print("Position: ");
      //  Serial.print("Latitude:");
      //  Serial.print(lat,6);
      //  Serial.print(";");
      //  Serial.print("Longitude:");
      //  Serial.println(lon,6);
      //  Serial.print(lat);
      //  Serial.print(" ");
    }
  }
  String latitude = String(lat, 6);
  String longitude = String(lon, 6);;
  //Serial.println(latitude+";"+longitude);
  //delay(1000);
  return  latitude;
}

String gpsDataLongitude() {
  while (gpsSerial.available()) { // check for gps data
    if (gps.encode(gpsSerial.read())) // encode gps data
    {
      gps.f_get_position(&lat, &lon); // get latitude and longitude
      //  Serial.print("Position: ");
      //  Serial.print("Latitude:");
      //  Serial.print(lat,6);
      //  Serial.print(";");
      //  Serial.print("Longitude:");
      //  Serial.println(lon,6);
      //  Serial.print(lat);
      //  Serial.print(" ");
    }
  }
  String latitude = String(lat, 6);
  String longitude = String(lon, 6);
  //Serial.println(latitude+";"+longitude);
  //delay(1000);
  return  longitude;
}

