#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <stdio.h>

using namespace std;

// Setup radio on R-PI v2 GPIO25 for CE, CE0 for CSN, and SPI @ 4Mhz
RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);
RF24Network network(radio);

// Addresses
const uint16_t local_node = 01;
const uint16_t remote_node = 00;

// Default parameters
unsigned long stp = 512;
unsigned long dir = 1;
unsigned long dly = 4;

// Payload format
struct payload_t {
  unsigned long motorStp;
  unsigned long motorDir;
  unsigned long motorDly;
};

void send_cmd (void) {
  payload_t payload = { stp, dir, dly };
  RF24NetworkHeader header (remote_node);
  bool ok = network.write(header,&payload,sizeof(payload));
  if (ok) {
    printf("ok.\n");
  } else {
    printf("failed.\n");
  }
  cout << ">";
}

void printData (void) {
  printf ("Steps: %lu\n", stp);
  printf ("Direction: %lu\n", dir);
  printf ("Delay: %lu\n", dly);
  cout << ">";
}

int main (void) {
  string cmd = "";
  radio.begin();
  delay(5);
  network.begin(90, local_node);
  radio.printDetails();
  cout << "Enter commands: w/s for +/- delay, W/S for +/- steps, a/d for turning (CTRL+C to exit) \n
>";
  while(1) {
    network.update();
    getline(cin,cmd);
    if (cmd.length() == 1) {
      switch (cmd[0]) {
      case 'w':
        if (dly < 50) {
          dly = dly + 1;
          printData();
        }
        break;
      case 's':
        if (dly > 2) {
          dly = dly - 1;
          printData();
        }
        break;
      case 'W':
        if (stp < 2048) {
          stp = stp + 64;
          printData();
        }
        break;
      case 'S':
        if (stp > 64) {
          stp = stp - 64;
          printData();
        }
        break;
      case 'a':
        dir = 0;
        printData();
        printf ("\nSending Data.\n");
        send_cmd ();
        break;
      case 'd':
        dir = 1;
        printData();
        printf ("Sending Data.\n");
        send_cmd ();
        break;
      }
    }
  }
 return EXIT_SUCCESS;
}
