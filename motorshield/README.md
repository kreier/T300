# Motorshield L298P

This useful shield has a motor driver L298P with inverter, so only 4 digital pins are needed to drive 2 motors with PWM. The Bluetooth port has a voltage divider for 3.3 Volt to protect the modules. Header for 7 Servo motors are presend, as well as an ultrasonic sensor. And the motor output is visualized with colored LEDs.

More can be found at https://protosupplies.com/product/l298p-motor-driver-shield/

## Voltage drop

My measurements show 

... follows ...

## Limitations

The PWM for the two motors is connected to pin 10 and 11. But the PWM driver for pin 10 uses the timer 1 of the Arduino. Once a servo is activated this timer can no longer be used for PWM and the funtionality on pin 10 is lost. I had to program a reset into the program, since a `detach()` for the servo library does not work.

##
