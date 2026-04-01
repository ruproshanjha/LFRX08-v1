# Firmware Documentation – LFRX08 v1

## 1. Board and Hardware Overview

The firmware is designed for:

| Component       | Details                        |
| --------------- | ------------------------------ |
| Microcontroller | Arduino / ESP-based board      |
| Sensors         | 8 Digital IR Sensors           |
| Motor Driver    | Dual H-Bridge (TB6612 / L298N) |
| Motors          | DC Geared Motors               |
| Communication   | Bluetooth via Serial           |

---

## 2. Pin Configuration (Based on Code Variables)

### Motor Pins

| Function       | Variable             |
| -------------- | -------------------- |
| Left Forward   | left_motor_forward   |
| Left Backward  | left_motor_backward  |
| Right Forward  | right_motor_forward  |
| Right Backward | right_motor_backward |
| Left PWM       | left_motor_speed     |
| Right PWM      | right_motor_speed    |

### Sensor Pins

| Parameter    | Description                   |
| ------------ | ----------------------------- |
| sensorPins[] | Array of 8 digital input pins |
| sensorNumber | Total sensors = 8             |

---

## 3. Project Structure (Firmware Files)

| File                 | Function                            |
| -------------------- | ----------------------------------- |
| Line Follower AH.ino | Main loop and system integration    |
| read_sensor.ino      | Reads sensors and builds bitmask    |
| PID_Controller.ino   | PID logic and decision making       |
| motor.ino            | Motor driving logic                 |
| Turns.ino            | Turning and movement functions      |
| Telemetry.ino        | Serial telemetry output             |
| Bluetooth_EEPROM.ino | Command handling and EEPROM storage |

---

## 4. Firmware Execution Flow

loop():

* handleBluetooth()
* read_black_line()
* runPIDStep()
* sendTelemetry()

---

## 5. Key Functional Blocks

### Sensor System

* Reads 8 digital sensors
* Creates bitmask (bitSensor)
* Calculates weighted position

### PID Control

* Uses error and derivative
* Computes correction
* Adjusts motor speeds

### Motor Control

* Direction via digital pins
* Speed via PWM
* Deadband prevents jitter

### Turning Logic

* Pattern-based detection
* Timeout safety (800 ms)

### Bluetooth Interface

* Receives commands (KP, KD, START, etc.)
* Updates runtime parameters

### EEPROM Storage

* Stores tuning values
* Loads on startup with safety defaults

---

## 6. Important Variables

| Variable       | Purpose              |
| -------------- | -------------------- |
| kp, kd         | PID gains            |
| base_speed     | Normal running speed |
| turnSpeed      | Turning speed        |
| error          | Line deviation       |
| previous_error | For derivative       |
| bitSensor      | Sensor state (8-bit) |
| inverseON      | Inversion mode       |
| pidRunning     | Run/Stop state       |

---

## 7. Summary

The firmware is modular, fast, and optimized for real-time control, making it suitable for competitive line follower robots.
