// =================================================
// TELEMETRY SENDER (Robot -> App)
// =================================================

void sendTelemetry() {

  // limit telemetry rate
  if (millis() - lastTelemetryTime < telemetryInterval) {
    return;
  }
  lastTelemetryTime = millis();

  // ---------------- SENSOR BITS ----------------
  Serial.print("S:");

  // ensure exactly 8 bits, MSB first
  for (int i = sensorNumber - 1; i >= 0; i--) {
    Serial.print(bitRead(bitSensor, i));
  }

  Serial.print(";LM:");
  Serial.print(leftMotorPWM);

  Serial.print(";RM:");
  Serial.print(rightMotorPWM);

  Serial.print(";E:");
  Serial.print((int)error);

  Serial.print('\n');  // END OF TELEMETRY LINE
}
