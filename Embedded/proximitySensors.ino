// Get seating occupancy data from US-100 prox sensors
// All measurements are in centimeters
void GetSensorData() { 
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
  
  seat1 = seatOccupied(duration_us1/29/2);
  seat2 = seatOccupied(duration_us2/29/2);
  seat3 = seatOccupied(duration_us3/29/2);
  seat4 = seatOccupied(duration_us4/29/2);
  Serial.print("Seat 1 Occupied:");
  Serial.println(duration_us1/29/2);
  Serial.print("Seat 2 Occupied:");
  Serial.println(duration_us2/29/2);
  Serial.print("Seat 3 Occupied:");
  Serial.println(duration_us3/29/2);
  Serial.print("Seat 4 Occupied:");
  Serial.println(duration_us4/29/2);
}
bool seatOccupied(long distance) {
  return (distance < 75 && distance > 4); 
}