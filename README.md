## RemoteMotor
This project is for remotely controlling a motor attached to an arduino via an nRF24 module. The programming is based on the getting started scenarios in the nRF24 libraries by TMRh20.

####Requirements
The following libraries are required for this project:
- [TMRh20/RF24](https://github.com/TMRh20/RF24)
- [TMRh20/RF24Network](https://github.com/TMRh20/RF24Network)

####Hardware configuration
The following hardware configuration was used:
######R-Pi model B rev2 <-> nRF24
* pin 20 (gnd) <-> pin 1 (gnd)
* pin 17 (3v3) <-> pin 2 (vcc)
* pin 22 (GPIO25, CE) <-> pin 3 (CE)
* pin 24 (GPIO8, CE0) <-> pin 4 (CSN)
* pin 23 (GPIO11, SCLK) <-> pin 5 (SCK)
* pin 19 (GPIO10, MOSI) <-> pin 6 (MOSI)
* pin 21 (GPIO9, MISO) <-> pin 7 (MISO)

######Arduino Micro <-> nRF24
* gnd pin <-> pin 1 (gnd)
* 3v3 pin <-> pin 2 (vcc)
* pin 9 (CE) <-> pin 3 (CE)
* pin 10 (CSN) <-> pin 4 (CSN)
* SCK pin <-> pin 5 (SCK)
* MOSI pin <-> pin 6 (MOSI)
* MISO pin <-> pin 7 (MISO)

######Arduino Micro <-> ULN2003 unipolar motor controller
The ULN2003 should be powered externally as the Micro is unable to source the required current.
* pin 4 <-> pin 1
* pin 5 <-> pin 2
* pin 6 <-> pin 3
* pin 7 <-> pin 4

