// =================================================
// PID CONTROLLER (NON-BLOCKING, STEP-BASED)
// =================================================

void runPIDStep() {

  // ---------- SAFE LINE POSITION CALC ----------
  if (sumOnSensor > 0 && sumOnSensor <= 2) {
    line_position = (float)sensorWight / (float)sumOnSensor;
  }

  error = center_position - line_position;

  // ---------- DIRECTION DETECTION ----------
  switch (bitSensor) {

    // left side detection
    case 0b11111000:
    case 0b11110000:
    case 0b11111100:
      direction = "left";
      break;

    // right side detection
    case 0b00011111:
    case 0b00001111:
    case 0b00111111:
      direction = "right";
      break;

    case 0b10011000:
    case 0b11011000:
      direction = "left" ;
      break ;

    case 0b00011001 :
    case 0b00011011 :
      direction = "right" ;
      break ;
  }

  // ---------- TURN LOGIC ----------
  if (bitSensor == 0) {

    error = 0;

    if (direction != "straight") {

      delay(delay_before_turn);

      if (direction == "right") {
        turnRight(turnSpeed, turnSpeed);
      } else {
        turnLeft(turnSpeed, turnSpeed);
      }

      direction = "straight";  // reset after turn
    }
    return; // skip PID this cycle
  }

  // ---------- STOP / INTERSECTION ----------
  if (bitSensor == 255) {

    digitalWrite(led, HIGH);

    distance(5);

    read_black_line();
    while (bitSensor == 255) {
      stop();
      read_black_line();
    }

    if (bitSensor == 0) {
      direction = "right";
    } else {
      direction = "straight";
    }

    digitalWrite(led, LOW);
    return;
  }

  // ---------- INVERSE DETECTION ----------
  if (
    bitSensor == 207 ||
    bitSensor == 231 ||
    bitSensor == 239 ||
    bitSensor == 247 ||
    bitSensor == 243
  ) {
    inverseON = !inverseON;
    digitalWrite(led, inverseON);
    return;
  }

  // ---------- PID COMPUTATION ----------
  derivative = error - previous_error;

  int correction = (error * kp) + (derivative * kd);

  int right_motor_correction = base_speed + correction;
  int left_motor_correction  = base_speed - correction;

  previous_error = error;

  motor(left_motor_correction, right_motor_correction);
}
