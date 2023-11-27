#include <WiFi.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <stdlib.h>
#include "hiddenVariable.h"

// Initizalize US-100 pins for hardware distance sensing
#define TRIG_PIN1 22 
#define ECHO_PIN1 23 
#define TRIG_PIN2 25 
#define ECHO_PIN2 26 
#define TRIG_PIN3 32 
#define ECHO_PIN3 33 
#define TRIG_PIN4 13 
#define ECHO_PIN4 35 

float duration_us1, duration_us2, duration_us3, duration_us4;
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
  delay(35000);
}

void wifiSetup() {
  WiFi.disconnect(true);
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
  digitalWrite(TRIG_PIN1, LOW);
  digitalWrite(TRIG_PIN2, LOW);
  digitalWrite(TRIG_PIN3, LOW);
  digitalWrite(TRIG_PIN4, LOW);
}