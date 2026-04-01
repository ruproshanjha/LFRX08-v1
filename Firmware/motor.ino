// =================================================
// MOTOR DRIVER + TELEMETRY SUPPORT
// =================================================

void motor(int LPWM, int RPWM) {

  // ---------- LEFT MOTOR ----------
  if (LPWM > 5) {
    digitalWrite(left_motor_forward, HIGH);
    digitalWrite(left_motor_backward, LOW);
  }
  else if (LPWM < -5) {
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(left_motor_backward, HIGH);
  }
  else {
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(left_motor_backward, LOW); // coast
    LPWM = 0;
  }

  // ---------- RIGHT MOTOR ----------
  if (RPWM > 5) {
    digitalWrite(right_motor_forward, HIGH);
    digitalWrite(right_motor_backward, LOW);
  }
  else if (RPWM < -5) {
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(right_motor_backward, HIGH);
  }
  else {
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(right_motor_backward, LOW);
    RPWM = 0;
  }

  // ---------- CONSTRAIN ----------
  LPWM = constrain(LPWM, -255, 255);
  RPWM = constrain(RPWM, -255, 255);

  // ---------- APPLY PWM ----------
  analogWrite(left_motor_speed, abs(LPWM));
  analogWrite(right_motor_speed, abs(RPWM));

  // ---------- TELEMETRY ----------
  leftMotorPWM  = abs(LPWM);
  rightMotorPWM = abs(RPWM);
}
