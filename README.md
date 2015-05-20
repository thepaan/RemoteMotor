## RemoteFocus
This project is for remotely controlling a motor attached to an arduino via an nRF24 module.

###Requirements
- [TMRh20/RF24](https://github.com/TMRh20/RF24)
- [TMRh20/RF24Network](https://github.com/TMRh20/RF24Network)

###Hardware configuration
#####R-Pi model B rev2 <-> nRF24
* pin 20 (gnd) <-> pin 1 (gnd)
* pin 17 (3v3) <-> pin 2 (vcc)
* pin 22 (GPIO25, CE) <-> pin 3 (CE)
* pin 24 (GPIO8, CE0) <-> pin 4 (CSN)
* pin 23 (GPIO11, SCLK) <-> pin 5 (SCK)
* pin 19 (GPIO10, MOSI) <-> pin 6 (MOSI)
* pin 21 (GPIO9, MISO) <-> pin 7 (MISO)
#####Arduino Micro <-> nRF24
* gnd pin <-> pin 1 (gnd)
* 3v3 pin <-> pin 2 (vcc)
* pin 9 (CE) <-> pin 3 (CE)
* pin 10 (CSN) <-> pin 4 (CSN)
* SCK pin <-> pin 5 (SCK)
* MOSI pin <-> pin 6 (MOSI)
* MISO pin <-> pin 7 (MISO)

