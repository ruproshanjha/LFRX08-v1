LFRX08 v1 – PID Line Follower Robot
1. What is LFRX08 v1

LFRX08 v1 is a high-performance line follower robot designed for competitive robotics. It uses an 8-sensor digital array, a fast PID-based control loop, and Bluetooth-based real-time tuning.

The system is optimized for:

High speed
Stable tracking
Reliable turning
Minimal latency control
2. Features
8 Digital IR Sensor Processing
Bitmask-based fast line detection
PID (Proportional + Derivative) control
Smart turn detection using sensor patterns
Intersection handling logic
Real-time Bluetooth tuning
EEPROM parameter storage
Telemetry output for debugging
Safe motor control with deadband
3. How to Download and Use
Step 1: Download
Clone or download the repository
Extract the folder
Step 2: Open Firmware
Navigate to /Firmware
Open Line Follower AH.ino in Arduino IDE / PlatformIO
Step 3: Select Board
Choose your microcontroller (Arduino / ESP)
Select correct COM port
Step 4: Upload Code
Compile and upload firmware
Step 5: Connect Hardware
Connect sensors, motors, and Bluetooth module
Ensure proper power supply
Step 6: Use Mobile App
Open app from /Application
Connect via Bluetooth
Send commands (START, KP, KD, etc.)
4. Basic Usage Flow
Power ON robot
Connect Bluetooth app
Send START
Tune PID parameters
Monitor telemetry
5. Author

Author: Rup Roshan Jha
Team: Black Pearl Robotix
