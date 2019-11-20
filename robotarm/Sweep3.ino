/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo serv1;  // create servo object to control a servo
Servo serv2;
Servo serv3;
Servo serv4;
Servo serv5;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  pinMode(4, OUTPUT);
  serv1.attach(A0);  // attaches the servo on pin 9 to the servo object
  serv2.attach(A1);
  serv3.attach(A2);
  serv4.attach(A3);
  serv5.attach(9);
  serv5.write(90);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
}

void loop() {
  for (pos = 45; pos <= 135; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    serv1.write(pos);              // tell servo to go to position in variable 'pos'
    serv2.write(pos);
    serv3.write(pos);
    serv4.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 135; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
    serv1.write(pos);              // tell servo to go to position in variable 'pos'
    serv2.write(pos);
    serv3.write(pos);
    serv4.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
}
