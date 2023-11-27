// //*****************************   SENSOR  DATA TRANSMITTING   *****************************//
void SendSensorData() {
  client.setInsecure();
  http.begin(client, DBASE);
  http.addHeader("Content-Type", "application/json");      // SPECIFY JSON
  http.addHeader("api-key", MONGODB_KEY);  //specify API key

  DynamicJsonDocument payload(1024); // Create JSON file for post request
  payload["dataSource"] = "Thingy";
  payload["database"] = "Project";
  payload["collection"] = "Availability";
  payload["filter"]["_id"]["$eq"]["$oid"] = "655a9748344b3bb1f23c1beb";
  JsonArray data = payload["update"]["$set"].createNestedArray("seats");
  data.add(seatStatus(seat1));
  data.add(seatStatus(seat2));
  data.add(seatStatus(seat3));
  data.add(seatStatus(seat4));

  String JSONText;
  size_t JSONlength = serializeJson(payload, JSONText);
  Serial.println(JSONText);
  int httpCode = http.POST(JSONText);  //Send the request
  delay(2000);                         
  String payloads = http.getString();   //Get the response payload

  Serial.println(httpCode);  //Print HTTP return code
  Serial.println(payloads);   //Print request response payload

  http.end();  //Close connection
}

String seatStatus(bool status) {
    if (status) {
      return "Occupied";
    } else {
      return "Empty";
    }
}
