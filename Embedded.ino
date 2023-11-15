#include <WiFi.h>

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

const char* ssid     = "Rasp";
const char* password = "rasperian120j";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);  
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT); 
  pinMode(TRIG_PIN4, OUTPUT);
  pinMode(ECHO_PIN4, INPUT); 
}

void loop() {
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  duration_us1 = pulseIn(ECHO_PIN1, HIGH);

  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration_us2 = pulseIn(ECHO_PIN2, HIGH);

  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  duration_us3 = pulseIn(ECHO_PIN3, HIGH);

  digitalWrite(TRIG_PIN4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN4, LOW);
  duration_us4 = pulseIn(ECHO_PIN4, HIGH);
  
  // calculate the distance
  distance_cm1 = 0.017 * duration_us1;
  distance_cm2 = 0.017 * duration_us2;
  distance_cm3 = 0.017 * duration_us3;
  distance_cm4 = 0.017 * duration_us4;
  // print the value to Serial Monitor
  seat1 = seatOccupied(distance_cm1);
  seat2 = seatOccupied(distance_cm2);
  seat3 = seatOccupied(distance_cm3);
  seat4 = seatOccupied(distance_cm4);
  Serial.print("Seat 1 Occupied:");
  Serial.println(seat1);
  Serial.print("Seat 2 Occupied:");
  Serial.println(seat2);
  Serial.print("Seat 3 Occupied:");
  Serial.println(seat3);
  Serial.print("Seat 4 Occupied:");
  Serial.println(seat4);
  delay(5000);
}
bool seatOccupied(float distance) {
  if (distance < 75) {
    return true;
  } else {
    return false;
  }
}