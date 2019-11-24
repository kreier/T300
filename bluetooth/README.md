# Bluetooth BLE with CC2541 (HM-10)

The pins on the Arduino Leonardo that we use behaves different than the Arduino UNO we used in the past. The USB port is connected to Serial while the pins 0 and 1 are connected to Serial1. We use the latter for the bluetooth module and the wireless communication.

## Change the name of the bluetooth module

All we need is a few lines of code to bridge the USB port to the serial port of the Bluetooth module:



### Curiosity

The bluetooth module chip CC2541 has actually a microcontroller build in, the [Intel 8051](https://en.wikipedia.org/wiki/Intel_MCS-51) that has 128 bytes RAM and 4 KB ROM, so not as powerful as the Arduino itself. 
