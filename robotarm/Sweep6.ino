#include <Servo.h>

#define MIN1 5  // left and right
#define MAX1 175
#define MIN2 45 // up and down
#define MAX2 120
#define MIN3 65 // forward and back
#define MAX3 140
#define MIN4 90 // open and close
#define MAX4 125

Servo serv1;  // left and right  45 to 135 
Servo serv2;  // up and down     80 to 100
Servo serv3;  // forward and back 80 to 100
Servo serv4;  // open and close  80 to 100
Servo serv5;
// twelve servo objects can be created on most boards

int pos1 = 90;    // variable to store the servo position
int pos2 = 90;
int pos3 = 90;
int pos4 = 90;

void setup() {
  pinMode(4, OUTPUT);
  serv1.attach(A0);  // attaches the servo on pin 9 to the servo object
  serv2.attach(A1);
  serv3.attach(A2);
  serv4.attach(A3);
  serv5.attach(9);
  serv1.write(90);
  serv2.write(MIN2);
  serv3.write(MIN3);
  serv4.write(MIN4);
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
  for (pos1 = 90; pos1 <= MAX1; pos1 += 1) { // turn left
    serv1.write(pos1);
    delay(15);
  }
  for (pos1 = MAX1; pos1 >= MIN1; pos1 -= 1) { // all the way back to right
    serv1.write(pos1);
    delay(15);
  }
  for (pos1 = MIN1; pos1 <= 90; pos1 += 1) { // back to center
    // in steps of 1 degree
    serv1.write(pos1); 
    delay(15); 
  }
  for (pos2 = MIN2; pos2 <= MAX2; pos2 += 1) { // up 
    serv2.write(pos2);
    delay(15);
  }
  for (pos2 = MAX2; pos2 >= MIN2; pos2 -= 1) { // down
    serv2.write(pos2);
    delay(15);
  }
  for (pos3 = MIN3; pos3 <= MAX3; pos3 += 1) { // forward 
    serv3.write(pos3);
    delay(15);
  }
  for (pos3 = MAX3; pos3 >= MIN3; pos3 -= 1) { // back
    serv3.write(pos3);
    delay(15);
  }
  for (pos4 = MIN4; pos4 <= MAX4; pos4 += 1) { // close
    serv4.write(pos4);
    delay(15);
  }
  for (pos4 = MAX4; pos4 >= MIN4; pos4 -= 1) { // open
    serv4.write(pos4);
    delay(15);
  }
  // lets go ------------------------------------------------------
  for (pos2 = MIN2; pos2 <= MAX2; pos2 += 1) { // up 
    serv2.write(pos2);
    delay(15);
  }
  for (pos3 = MIN3; pos3 <= MAX3; pos3 += 1) { // forward 
    serv3.write(pos3);
    delay(15);
  }
  for (pos4 = MIN4; pos4 <= MAX4; pos4 += 1) { // close
    serv4.write(pos4);
    delay(15);
  }
  for (pos2 = MAX2; pos2 >= MIN2; pos2 -= 1) { // down
    serv2.write(pos2);
    delay(15);
  }
  for (pos3 = MAX3; pos3 >= MIN3; pos3 -= 1) { // back
    serv3.write(pos3);
    delay(15);
  }
  for (pos4 = MAX4; pos4 >= MIN4; pos4 -= 1) { // open
    serv4.write(pos4);
    delay(15);
  }
  // lets go ------------------------------------------------------ left!
  for (pos1 = 90; pos1 <= MAX1; pos1 += 1) { // turn left
    serv1.write(pos1);
    delay(15);
  }
  for (pos2 = MIN2; pos2 <= MAX2; pos2 += 1) { // up 
    serv2.write(pos2);
    delay(15);
  }
  for (pos3 = MIN3; pos3 <= MAX3; pos3 += 1) { // forward 
    serv3.write(pos3);
    delay(15);
  }
  for (pos4 = MIN4; pos4 <= MAX4; pos4 += 1) { // close
    serv4.write(pos4);
    delay(15);
  }
  for (pos3 = MAX3; pos3 >= MIN3; pos3 -= 1) { // back
    serv3.write(pos3);
    delay(15);
  }
  for (pos2 = MAX2; pos2 >= MIN2; pos2 -= 1) { // down
    serv2.write(pos2);
    delay(15);
  }
  for (pos4 = MAX4; pos4 >= MIN4; pos4 -= 1) { // open
    serv4.write(pos4);
    delay(15);
  }
  for (pos1 = MAX1; pos1 >= MIN1; pos1 -= 1) { // all the way back to right
    serv1.write(pos1);
    delay(15);
  }
  for (pos2 = MIN2; pos2 <= MAX2; pos2 += 1) { // up 
    serv2.write(pos2);
    delay(15);
  }
  for (pos3 = MIN3; pos3 <= MAX3; pos3 += 1) { // forward 
    serv3.write(pos3);
    delay(15);
  }
  for (pos4 = MIN4; pos4 <= MAX4; pos4 += 1) { // close
    serv4.write(pos4);
    delay(15);
  }
  for (pos3 = MAX3; pos3 >= MIN3; pos3 -= 1) { // back
    serv3.write(pos3);
    delay(15);
  }
  for (pos2 = MAX2; pos2 >= MIN2; pos2 -= 1) { // down
    serv2.write(pos2);
    delay(15);
  }
  for (pos4 = MAX4; pos4 >= MIN4; pos4 -= 1) { // open
    serv4.write(pos4);
    delay(15);
  }
  for (pos1 = MIN1; pos1 <= 90; pos1 += 1) { // back to center
    // in steps of 1 degree
    serv1.write(pos1); 
    delay(15); 
  }
  delay(1000);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
}
