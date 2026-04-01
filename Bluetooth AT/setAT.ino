#include <SoftwareSerial.h>

// Arduino RX, TX  -> HC-05 TX, RX
SoftwareSerial BT(10, 11);   // RX, TX

void setup() {
  Serial.begin(9600);
  BT.begin(38400);   // HC-05 AT mode speed is usually 38400

  Serial.println("HC-05 AT mode started");
  delay(1000);

  sendAT("AT");                  // test communication
  sendAT("AT+UART=38400,0,0");   // set baud rate to 38400
}

void loop() {
  // Print any response from HC-05 to Serial Monitor
  if (BT.available()) {
    Serial.write(BT.read());
  }

  // Send data from Serial Monitor to HC-05
  if (Serial.available()) {
    BT.write(Serial.read());
  }
}

void sendAT(String cmd) {
  Serial.print("Sending: ");
  Serial.println(cmd);
  BT.println(cmd);
  delay(1000);

  while (BT.available()) {
    Serial.write(BT.read());
  }
  Serial.println();
}
