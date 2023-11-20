#include <WiFi.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <stdlib.h>
#include <hiddenVariables.h>

#define TRIG_PIN1 23 
#define ECHO_PIN1 22 
#define TRIG_PIN2 26 
#define ECHO_PIN2 27 
#define TRIG_PIN3 33 
#define ECHO_PIN3 25 
#define TRIG_PIN4 32 
#define ECHO_PIN4 13 

float duration_us1, duration_us2, duration_us3, duration_us4;
float distance_cm1, distance_cm2, distance_cm3, distance_cm4;
bool  seat1, seat2, seat3, seat4; // occupied if TRUE, empty if false 

WiFiClientSecure client;
HTTPClient http;
String DBASE = MyMONGO_DBASE;

void setup() {
  Serial.begin(115200);
  wifiSetup();
  pinSetup();
  DBASE = MyMONGO_DBASE;
}

void loop() {
  GetSensorData();
  SendSensorData();
  delay(40000);
}

void wifiSetup() {
  WiFi.disconnect(true);
  //esp_wifi_start();
  Serial.println("POST test program");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(1000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("Connecting to:   ");
  Serial.print(WiFi.SSID());
  Serial.print("\n");
  Serial.print("This device IP address: ");
  Serial.println(WiFi.localIP());
}

void pinSetup() {
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);  
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT); 
  pinMode(TRIG_PIN4, OUTPUT);
  pinMode(ECHO_PIN4, INPUT); 
}