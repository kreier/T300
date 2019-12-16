// Setup with 10 keys as defined in the root folder and used with kreier/remote and BitBlue on iOS
//
// Matrix for control - mode1
//
// key index text     M1[] M2[] SPD 
//  F    0   forward  HIGH HIGH 255  
//  B    1   backward LOW  LOW  255  
//  L    2   left     HIGH LOW  255  
//  R    3   right    LOW  HIGH 255  
//  T    4   triangle
//  C    5   circle
//  X    6   stop
//  Q    7   square
//  M    8   menu
//  S    9   start

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
const int  motor1[] = {1, 0, 1, 0};
const int  motor2[] = {1, 0, 0, 1};
const String text[] = {"forward","backward","left","right","triange","circle","stop","square","select","start"};

char BTinput = '0';  // char input via bluetooth
int  BTkey   = 0;    // converted to numerical value
int  pos = 0;
int  spd = 0;
int  mode = 1;
String message = "stop";
int verzug = 200;

unsigned long timer_sonar;
unsigned long timer_drive;
int DistanceCm = 99;

hd44780_I2Cexp lcd; 
Servo myservo;  

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
  lcd.print("    ");
}

void statuslcd() {
  lcd.setCursor(5, 0);              // Mode 1-4
  lcd.print(mode);
  lcd.setCursor(10, 0);
  if(spd < 100) lcd.print(" ");     // Speed 10-255
  lcd.print(spd);
  lcd.setCursor(14, 0);
  lcd.print(digitalRead(PIN_M1));   // Motor 1 and 2
  lcd.print(digitalRead(PIN_M2));   // forward (1) or backward (0)
}

void setup() {
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_E1, OUTPUT);
  pinMode(PIN_E2, OUTPUT);
  analogWrite(PIN_E1, spd);
  analogWrite(PIN_E2, spd);
  myservo.attach(PIN_SERVO);
  myservo.write(90);
  timer_sonar = millis();
  timer_drive = millis();

  beep(2);
  Serial1.begin(9600);  // HC-10 BLE on pin 0 and 1
  lcd.init();
  lcd.backlight();
  disp(0, 0, "T300");
}


void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    for(BTkey = 0; BTkey < 10; BTkey += 1) {
      if(BTinput == keyindex[BTkey]) {
        Serial.print("Verstanden: ");
        Serial.print(BTkey);
        Serial.print("  ");
        Serial.print(text[BTkey] + "\n");
        message = text[BTkey];
        break;
      }
    }
    if(mode == 1) { // Mode 1: Drive
      if(BTkey < 4) {
        digitalWrite(PIN_M1, motor1[BTkey]);
        digitalWrite(PIN_M2, motor2[BTkey]);
        spd = 255;       
      }
      if(BTkey == 4) {
        spd = 255;
      }
      if(BTkey == 5) {
        spd += 15;
      }
      if(BTkey == 7) {
        spd -= 15;
      }
      if(spd < 30) spd = 30;
      if(spd > 255) spd = 255;
      if(BTkey == 6) spd = 0;     
      if(BTkey == 8) {
        mode++;
        if(mode > 4) mode = 1;
      }
      if(BTkey == 9) {
        for(spd = 255; spd > 0; spd -= 16) {
          digitalWrite(PIN_M1, 1);
          digitalWrite(PIN_M2, 1);
          analogWrite(PIN_E1, spd);
          analogWrite(PIN_E2, spd);
          statuslcd();
          delay(verzug);
        }
        for(spd = 15; spd < 255; spd += 16) {
          digitalWrite(PIN_M1, 0);
          digitalWrite(PIN_M2, 0);
          analogWrite(PIN_E1, spd);
          analogWrite(PIN_E2, spd);
          statuslcd();
          delay(verzug);
        }
      }
    }
    disp(0, 1, message);
    digitalWrite(PIN_M1, motor1[BTkey]);
    digitalWrite(PIN_M2, motor2[BTkey]);
    analogWrite(PIN_E1, spd);
    analogWrite(PIN_E2, spd);
  }
  if(millis() > timer_sonar + RELAX_SONAR) {
    timer_sonar = millis();
    statuslcd();
  }
}
