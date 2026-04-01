#include <EEPROM.h>

// =================================================
// BLUETOOTH COMMAND HANDLER
// =================================================
void handleBluetooth() {

  if (!Serial.available()) return;

  bluetoothActive = true;

  String cmd = Serial.readStringUntil('\n');
  cmd.trim();

  if (cmd == "START") {
    pidRunning = true;
    previous_error = 0;
  }
  else if (cmd == "STOP") {
    pidRunning = false;
    motor(0, 0);
  }
  else if (cmd.startsWith("KP:")) {
    kp = constrain(cmd.substring(3).toInt(), 0, 100);
    EEPROM.put(EE_KP, kp);
  }
  else if (cmd.startsWith("KD:")) {
    kd = constrain(cmd.substring(3).toInt(), 0, 100);
    EEPROM.put(EE_KD, kd);
  }
  else if (cmd.startsWith("MS:")) {
    base_speed = constrain(cmd.substring(3).toInt(), 0, 250);
    EEPROM.put(EE_MS, base_speed);
  }
  else if (cmd.startsWith("TS:")) {
    turnSpeed = constrain(cmd.substring(3).toInt(), 0, 250);
    EEPROM.put(EE_TS, turnSpeed);
  }
  else if (cmd.startsWith("DBT:")) {
    delay_before_turn = constrain(cmd.substring(4).toInt(), 0, 1000);
    EEPROM.put(EE_DBT, delay_before_turn);
  }
  else if (cmd.startsWith("TT:")) {
    test_time = constrain(cmd.substring(3).toInt(), 0, 1000);
    EEPROM.put(EE_TT, test_time);
  }
  else if (cmd.startsWith("MD:")) {
    measured_distance = constrain(cmd.substring(3).toInt(), 0, 1000);
    EEPROM.put(EE_MD, measured_distance);
  }
}

// =================================================
// EEPROM LOAD FUNCTION
// =================================================
void loadFromEEPROM() {

  EEPROM.get(EE_KP, kp);
  EEPROM.get(EE_KD, kd);
  EEPROM.get(EE_MS, base_speed);
  EEPROM.get(EE_TS, turnSpeed);
  EEPROM.get(EE_DBT, delay_before_turn);
  EEPROM.get(EE_TT, test_time);
  EEPROM.get(EE_MD, measured_distance);

  // -------- SAFETY DEFAULTS --------
  if (kp <= 0 || kp > 100) kp = 8;
  if (kd <= 0 || kd > 100) kd = 100;
  if (base_speed <= 0 || base_speed > 250) base_speed = 220;
  if (turnSpeed <= 0 || turnSpeed > 250) turnSpeed = 200;
  if (delay_before_turn < 0 || delay_before_turn > 1000) delay_before_turn = 70;
  if (test_time <= 0 || test_time > 1000) test_time = 350;
  if (measured_distance <= 0 || measured_distance > 1000) measured_distance = 30;
}
