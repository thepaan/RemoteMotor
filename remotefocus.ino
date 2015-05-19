// Include
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

// Define globals
const byte pinCount = 4;
const byte motorPins[] = {4, 5, 6, 7};
int lastMotorState = 0;

// Set up radio using pins 9 (CE) & 10 (CSN)
RF24 radio(9,10);
RF24Network network(radio);
const uint16_t local_node = 00;
const uint16_t remote_node = 01;

struct payload_t {
  unsigned long motorStp;
  unsigned long motorDir;
  unsigned long motorDly;
};

// Setup
void setup() {
  Serial.begin(57600);
  
  // Initialize motor
  for (byte thisPin = 0; thisPin < pinCount; thisPin++){
    pinMode(motorPins[thisPin], OUTPUT);
  }
  for (byte thisPin = 0; thisPin < pinCount; thisPin++){
    digitalWrite(motorPins[thisPin], LOW);
  }

  // Initialize radio
  SPI.begin();
  radio.begin();
  network.begin(90, local_node);
}

// Main loop
void loop() {
  network.update();
  while (network.available()) {
    RF24NetworkHeader header;  // What is this?
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Step Count: ");
    Serial.print(payload.motorStp);
    Serial.print(" Direction: ");
    Serial.print(payload.motorDir);
    Serial.print(" Step Delay: ");
    Serial.println(payload.motorDly);
    motorTurn(payload.motorStp, payload.motorDir, payload.motorDly);
  }
}

// Function to turn the motor
void motorTurn (int stp, int dir, int dly) {
  int cStep = lastMotorState;
  for (int x = 0; x < stp; x++) {
    switch (cStep) {
      case 0:
        setMotorState(1, 1, 0, 0);
      break;
      case 1:
        setMotorState(0, 1, 1, 0);
      break;
      case 2:
        setMotorState(0, 0, 1, 1);
      break;
      case 3:
        setMotorState(1, 0, 0, 1);
      break;
    }
    if (dir) {
      cStep = cStep + 1;
      if (cStep > 3) {
        cStep = 0;
      }
    } else {
      cStep = cStep - 1;
      if (cStep < 0) {
        cStep = 3;
      }
    }
  delay(dly);
  }
  setMotorState(0, 0, 0, 0);
  lastMotorState = cStep;
  Serial.print("Motor State: ");
  Serial.println(lastMotorState);
}

// Function to set the motor pins state
void setMotorState (byte p0S, byte p1S, byte p2S, byte p3S) {
  byte motorState[4] = {p0S, p1S, p2S, p3S};
  for (byte thisPin = 0; thisPin < pinCount; thisPin++) {
    if (motorState[thisPin] == 0) {
      digitalWrite(motorPins[thisPin], LOW);
   } else if (motorState[thisPin] == 1) {
      digitalWrite(motorPins[thisPin], HIGH);
    } else {
      Serial.println("Invalid seMotorState argument.");
    }
  }
}
