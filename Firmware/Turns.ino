// =================================================
// TURN & MOVEMENT FUNCTIONS (SAFE + COMPETITION)
// =================================================

void turnRight(int L, int R) {

  unsigned long startTime = millis();

  while (sensorDigital[3] != 1 && pidRunning) {

    // safety timeout (prevents infinite spin)
    if (millis() - startTime > 800) break;

    motor(L, -R);
    read_black_line();
  }

  motor(0, 0);   // ensure stop after turn
}

void turnLeft(int L, int R) {

  unsigned long startTime = millis();

  while (sensorDigital[4] != 1 && pidRunning) {

    // safety timeout
    if (millis() - startTime > 800) break;

    motor(-L, R);
    read_black_line();
  }

  motor(0, 0);
}

// =================================================
// SAFE STOP FUNCTIONS
// =================================================

void stop() {
  motor(0, 0);
}

// ❌ NO infinite loops allowed anymore
void hard_stop() {
  pidRunning = false;
  motor(0, 0);
}

// =================================================
// DISTANCE MOVEMENT
// =================================================

void distance_calibration(uint16_t test_time) {

  unsigned long startTime = millis();

  while (millis() - startTime < test_time && pidRunning) {
    motor(base_speed, base_speed);
  }

  motor(0, 0);
}

void distance(uint16_t dist) {

  if (measured_distance <= 0) return;

  int time_per_cm = test_time / measured_distance;
  unsigned long moveTime = dist * time_per_cm;
  unsigned long startTime = millis();

  while (millis() - startTime < moveTime && pidRunning) {
    motor(base_speed, base_speed);
  }

  motor(0, 0);
}
