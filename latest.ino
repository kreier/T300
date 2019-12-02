// Setup with 10 keys as defined in the root folder and used with kreier/remote and BitBlue on iOS

#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // for I2C expander

#define PIN_BUZZER     4
#define PIN_TRIGGER    7
#define PIN_ECHO       8
#define PIN_SERVO      9
#define PIN_E1        10 // enable - with PWM
#define PIN_M1        12
#define PIN_E2        11
#define PIN_M2        13
#define MAX_DISTANCE 350

int  spd = 0;
char BTinput = '0';
int  pos = 0;
int  mode = 1;
String message = "Stop   ";

hd44780_I2Cexp lcd; // declare lcd object:
NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);
Servo myservo;  

int distance() {
   return sonar.ping_cm(); // 10 pings per second  
}

void buz() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(20);
    digitalWrite(PIN_BUZZER, LOW);
}

void beep(int beeps) {
  for(int i = 0; i < beeps; i++) {
    buz();
    delay(80);
  }
}

void disp(int lcd_x, int lcd_y, String text) {
  Serial1.print( text );
  lcd.setCursor(lcd_x, lcd_y);
  lcd.print( text );
}

void setup() {
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  analogWrite(PIN_E1, spd);
  analogWrite(PIN_E2, spd);
  myservo.attach(PIN_SERVO);
  myservo.write(90);

  beep(2);
  Serial1.begin(9600);  // HC-10 BLE on pin 0 and 1
  lcd.begin(16,2);
  disp(0, 0, "T300 robot car");
}
 
void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    // MODE 1: Drive
    if(BTinput == 'F'  && mode == 1) { // up - forward
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_M2, HIGH);
        message = "forward ";
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'B' && mode == 1) { // down - backward
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_M2, LOW);
        message = "backward";
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'L' && mode == 1) { // left turn
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_M2, LOW);
        message = "left    ";
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'R' && mode == 1) { // right turn
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_M2, HIGH);
        message = "right   ";
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'S') {          // square  - A - autonomus with the servo
      for (pos = 30; pos <= 150; pos += 1) { 
        myservo.write(pos);   
        delay(15);      
      }
      for (pos = 150; pos >= 30; pos -= 1) { 
         myservo.write(pos);              
         delay(15);    
      }
      myservo.write(90);
      message = "scanning";
    }
    if(BTinput == 'T') {
      spd = 255; // triangle - B - FAST
      message = "Fast    ";
    }
    if(BTinput == 'M') {          // circle   - Y - SELECT
      // what is my mode? Beep 1 for remote 2 for autonomus and 3 for autonomus with ultrasonic beep
      mode++;
      if(mode > 4) mode = 1;
      beep(mode);
      message = "Mode ";
      message += String(mode);
      message += "   ";
    }
    if(BTinput == 'X') {
      spd = 0;   // cross   - X - STOP
      message = "Stop    ";
    }
    if(BTinput == 'Q') message = "square  ";
    if(BTinput == 'C') message = "circle  ";
    disp(0, 1, message);
    analogWrite(PIN_E1, spd);
    analogWrite(PIN_E2, spd);
  }
  distance();
}
