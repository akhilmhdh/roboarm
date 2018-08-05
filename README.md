
# Robo Arm
A 4-axis robotic arm controlled via smartphone using esp8266,servos and websockets.
# Getting Started
## Softwares
- Arduino IDE
## Hardwares
- ESP8266(mine was -01 version)
- Usb-ttl
- Arduino uno or any other versions
- 4 servos and its required power supply
- Necessary body
## Files
### esp.ino
It contains the code to be flashed on to esp8266.
Completes following tasks:
- Creates a webserver and sets up the esp
- Opens a websockets and provides a web page for smartphone
- Handles the input data
- Sends it to arduino(i used arduino to control my servos)
### esp-to-arduino.ino
It receives the data and controls the servos depending on data received
### data
It contains the html,css and js files for the server routes of esp.Needs to flash in on esp using spiff file system.
It has well designed button layout system with touch support systems.

