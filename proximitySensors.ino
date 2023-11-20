// Get seating occupancy data from US-100 prox sensors
void GetSensorData() {
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  // duration_us1 = pulseIn(ECHO_PIN1, HIGH);

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
}
bool seatOccupied(float distance) {
  distance = rand()%200;
  if (distance < 75) {
    return true;
  } else {
    return false;
  }
}