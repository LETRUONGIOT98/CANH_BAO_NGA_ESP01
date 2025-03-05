 
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define WIFI_SSID "Thu Thao"
#define WIFI_PASSWORD "917664ab"
#define DATABASE_URL "esp01-e45db-default-rtdb.firebaseio.com"
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");}
  // put your setup code here, to run once:
 config.database_url = DATABASE_URL;

  config.signer.test_mode = true;
  Firebase.reconnectWiFi(true);

  /* Initialize the library with the Firebase authen and config */
  Firebase.begin(&config, &auth);
Wire.begin(0,2);
  delay(1000);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    }}
  

}

void loop() {
  sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);
  // put your main code here, to run repeatedly:
  float giatocx = a.acceleration.x;
  float giatocy = a.acceleration.y;
  float giatocz = a.acceleration.z;
  Serial.println("GIA TOC X " + String(giatocx) +  String(" - GIA TOC Y ") + String(giatocy) + String(" - GIA TOC Z ") + String(giatocz));
  if(giatocx > 15.0 || giatocy > 15.0 || giatocz > 15.0 ){ //nếu gia tốc lớn hơn 15 m/s^2 thfi đc coi là hành động ngã
 Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/DATA/val", 1) ? "ok" : fbdo.errorReason().c_str());
  delay(1000);
  }
}
