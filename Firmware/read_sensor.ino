// =================================================
// DIGITAL SENSOR READING (8 IR, DIRECT)
// =================================================

void read_black_line() {

  sumOnSensor  = 0;
  sensorWight  = 0;
  bitSensor    = 0;

  for (int i = 0; i < sensorNumber; i++) {

    // -------------------------------------------------
    // READ DIGITAL SENSOR
    // Use !digitalRead(...) if BLACK = LOW on your board
    // -------------------------------------------------
    sensorDigital[i] = digitalRead(sensorPins[i]);
    // sensorDigital[i] = !digitalRead(sensorPins[i]);

    // Compatibility value (kept for legacy logic)
    sensorADC[i] = sensorDigital[i] ? 1023 : 0;

    // Inverse mode (black <-> white)
    if (inverseON) {
      sensorDigital[i] = !sensorDigital[i];
    }

    sumOnSensor  += sensorDigital[i];
    sensorWight  += sensorDigital[i] * WeightValue[i];

    // MSB = sensor 0, LSB = sensor 7
    bitSensor    |= (sensorDigital[i] << ((sensorNumber - 1) - i));
  }

  // -------------------------------------------------
  // SAFETY: NO SENSOR DETECTED
  // -------------------------------------------------
  if (sumOnSensor == 0) {
    bitSensor = 0b00000000;
  }
}
