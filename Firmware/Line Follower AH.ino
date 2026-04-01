#include <EEPROM.h>

// =================================================
// FUNCTION DECLARATIONS
// =================================================
void handleBluetooth();
void loadFromEEPROM();
void read_black_line();
void runPIDStep();
void motor(int LPWM, int RPWM);
void sendTelemetry();

// =================================================
// MOTOR PINS
// =================================================
#define right_motor_forward A0
#define right_motor_backward A1
#define left_motor_forward A2
#define left_motor_backward A3

#define right_motor_speed 11
#define left_motor_speed 10



// =================================================
// SENSOR SETUP
// =================================================
#define sensorNumber 8
const uint8_t sensorPins[sensorNumber] = { 9, 8, 7, 6, 5, 4, 3, 2 };

// =================================================
// SENSOR VARIABLES
// =================================================
int sensorADC[sensorNumber];
int sensorDigital[sensorNumber];
int bitWeight[sensorNumber]   = { 1,2,4,8,16,32,64,128 };
int WeightValue[sensorNumber] = {10,20,30,40,50,60,70,80};

int sumOnSensor;
int sensorWight;
int bitSensor;

// =================================================
// PID VARIABLES
// =================================================
float line_position;
float error;
float derivative;
float previous_error;
float center_position = 45;

int kp;
int kd;
int base_speed;
int turnSpeed;
int delay_before_turn;
int test_time;
int measured_distance;

// =================================================
// DIRECTION & INVERSE MODE (REQUIRED GLOBALS)
// =================================================
String direction = "straight";   // left / right / straight
bool inverseON = false;          // normal line by default

// =================================================
// FLAGS
// =================================================
bool pidRunning = false;
bool bluetoothActive = false;

// =================================================
// BUTTON & LED
// =================================================
#define button2 12
#define led 13

// =================================================
// TELEMETRY
// =================================================
unsigned long lastTelemetryTime = 0;
const unsigned long telemetryInterval = 50;

int leftMotorPWM = 0;
int rightMotorPWM = 0;

// =================================================
// EEPROM ADDRESSES
// =================================================
#define EE_KP   0
#define EE_KD   2
#define EE_MS   4
#define EE_TS   6
#define EE_DBT  8
#define EE_TT   10
#define EE_MD   12

// =================================================
// SETUP
// =================================================
void setup() {

  Serial.begin(38400);

  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);

  for (int i = 0; i < sensorNumber; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  loadFromEEPROM();   // load last tuned values

  digitalWrite(led, LOW); // default = competition mode
}

// =================================================
// LOOP
// =================================================
void loop() {

  handleBluetooth();     // Bluetooth tuning mode
  read_black_line();     // Always update sensors

  // -------- COMPETITION MODE (NO BLUETOOTH) --------
  if (!bluetoothActive && !pidRunning) {
    if (digitalRead(button2) == LOW) {
      while (digitalRead(button2) == LOW); // wait release
      delay(200);

      previous_error = 0;
      pidRunning = true;
    }
  }

  if (pidRunning) {
    runPIDStep();
  } else {
    motor(0, 0);
  }

  sendTelemetry();
}
