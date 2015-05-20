// Include
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

// Set up radio using pins 9 (CE) & 10 (CSN)
RF24 radio(9,10);
RF24Network network(radio);
const uint16_t local_node = 01;
const uint16_t remote_node = 00;

// Default paramters
int cmd = 0;
unsigned long stp = 512;
unsigned long dir = 1;
unsigned long dly = 4;

// Network data payload format
struct payload_t {
  unsigned long motorStp;
  unsigned long motorDir;
  unsigned long motorDly;
};

// Setup
void setup() {
  Serial.begin(57600);
  Serial.println("Enter commands: w/s for +/- delay, W/S for +/- steps, a/d for turning.");

  // Initialize radio
  SPI.begin();
  radio.begin();
  network.begin(90, local_node);
}

// Main loop
void loop() {
  network.update();
  if (Serial.available()) {
    cmd = Serial.read();
    switch (cmd) {
      case 'w':
        if (dly < 50) {
          dly = dly + 1;
          printData();
        } else {
          printData();
        }
      break;
      case 's':
        if (dly > 2) {
          dly = dly - 1;
          printData();
        } else {
          printData();
        }
      break;
      case 'W':
        if (stp < 2048) {
          stp = stp + 64;
          printData();
        } else {
          printData();
        }
      break;
      case 'S':
        if (stp > 64) {
          stp = stp - 64;
          printData();
        } else {
          printData();
        }
      break;
      case 'a':
        dir = 0;
        printData();
        Serial.println("Sending data.");
        sendCmd();
      break;
      case 'd':
        dir = 1;
        printData();
        Serial.println("Sending data.");
        sendCmd();
      break;
    }
  }
}

// Function to send command
void sendCmd () {
  payload_t payload = {stp, dir, dly};
  RF24NetworkHeader header (remote_node);
  bool ok = network.write(header,&payload,sizeof(payload));
  if (ok) {
    Serial.println("ok.");
  } else {
    Serial.println("failed.");
  }
}

// Function to show settings
void printData () {
    Serial.print("Step Count: ");
    Serial.print(stp);
    Serial.print(" Direction: ");
    Serial.print(dir);
    Serial.print(" Step Delay: ");
    Serial.println(dly);
}
