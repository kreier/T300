// Setup with 10 keys as defined in the root folder and used with kreier/remote and BitBlue on iOS
//
// Matrix for control - mode1 - 2019/12/12
//
// key index M1 M2 SPED text
//  F    0   1  1  255  forward
//  B    1   0  0  255  backward
//  L    2   1  0  255  left
//  R    3   0  1  255  right
//
//
//


#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

#define PIN_BUZZER     4
#define PIN_TRIGGER    7
#define PIN_ECHO       8
#define PIN_SERVO      9
#define PIN_E1        10 // enable - with PWM
#define PIN_M1        12
#define PIN_E2        11 // PWM
#define PIN_M2        13
#define MAX_DISTANCE  50
#define RELAX_SONAR  200 // ms to check for obstacles
#define RELAX_DRIVE  412 // ms to drive until check direction

const char keyindex[] = "FBLRTCXQMS";
const int motor1[] = {1, 0, 1, 0};
const int motor2[] = {1, 0, 0, 1};
const String text[] = {"forward","backward","left","right","triange","circle","  X  ","square","select","start"};

int verzug = 200;

char BTinput = '0';  // char input via bluetooth
int  BTkey = 0;      // converted to numerical value
int  pos = 0;
int  spd = 0;
int  mode = 1;
String message = "Stop   ";
// int sped[] = {255, 255, 200, 200};
unsigned long timer_sonar;
unsigned long timer_drive;
int DistanceCm;
boolean selbst = LOW;

hd44780_I2Cexp lcd; 
NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);
Servo myservo;  

void distance() {
  DistanceCm = sonar.ping_cm(); // 10 pings per second
  if (DistanceCm == 0) DistanceCm = MAX_DISTANCE;
  lcd.setCursor(11,0);
  lcd.print(DistanceCm); 
  lcd.print(" cm  ");
  if(DistanceCm < 20) {
    if(mode == 3) beep(1);
    timer_sonar -= (RELAX_SONAR - DistanceCm * 19);
    if(DistanceCm < 10) { // please stop
      spd = 0;
      analogWrite(PIN_E1, spd);
      analogWrite(PIN_E2, spd);
    }
  }   
}

void beep(int beeps) {
  for(int i = 0; i < beeps; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    lcd.noBacklight();
    delay(20);
    digitalWrite(PIN_BUZZER, LOW);
    lcd.backlight();    
    delay(80);
  }
}

void disp(int lcd_x, int lcd_y, String text) {
  Serial1.print( text );        // return via bluetooth
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
  timer_sonar = millis();
  timer_drive = millis();

  beep(2);
  Serial1.begin(9600);  // HC-10 BLE on pin 0 and 1
  lcd.init();
  //lcd.backlight();
  disp(0, 0, "T300 robot car");
  Serial.begin(115200);
}

void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    for(BTkey = 0; BTkey < 9; BTkey += 1) {
      if(BTinput == keyindex[BTkey]) {
        Serial.print("Verstanden: ");
        Serial.print(BTkey);
        Serial.print("  ");
        Serial.print(text[BTkey] + "\n");
        message = text[BTkey];
        break;
      }
    }
    if(mode == 1) {
      digitalWrite(PIN_M1, motor1[BTkey]);
      digitalWrite(PIN_M2, motor2[BTkey]);
      spd = 255;
    }
    if(BTinput == 'S') {          // Start  -  autonomus with the servo
        for(spd = 255; spd > 0; spd -= 16) {
          analogWrite(PIN_E1, spd);
          analogWrite(PIN_E2, spd);
          Serial.print("PWM: ");
          Serial.print(spd);
          Serial.print("\n");
          delay(verzug);
        }
        for(spd = 0; spd < 255; spd += 16) {
          analogWrite(PIN_E1, spd);
          analogWrite(PIN_E2, spd);
          Serial.print("PWM: ");
          Serial.print(spd);
          Serial.print("\n");
          delay(verzug);
        }
    }
    if(BTinput == 'S' && mode == 4) {          // Start  -  autonomus driving  
      selbst = HIGH;  
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
    if(BTinput == 'Q' && mode == 1) { // slower
      spd -= 15;
      if(spd < 30) spd = 30;
      message = "square ";
      message += spd;
      message += " ";
    }
    if(BTinput == 'C' && mode == 1) { // faster
      spd += 15;
      if(spd > 255) spd = 255;      
      message = "circle ";
      message += spd;
      message += " ";
    }
    disp(0, 1, message);
    analogWrite(PIN_E1, spd);
    analogWrite(PIN_E2, spd);
  }
  if(millis() > timer_sonar + RELAX_SONAR) {
    timer_sonar = millis();
    distance();
  }
}
