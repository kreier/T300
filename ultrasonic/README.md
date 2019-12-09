# Ultrasonic

We have a servo connected to pin 9 and mounted an ultrasonic distance sensor on top of it with trigger on pin 7 and the echo on pin 8. The buzzer on pin 4 can give us acoustic feedback. The 1602 display on I2C on pin 2 and 3 gives optic feedback. Now even the backlight flickers if an obstacle is detected.

## Code with 1602 display on I2C

```c
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
#include <NewPing.h>

#define  PIN_BUZZER     4
#define  PIN_TRIGGER    7
#define  PIN_ECHO       8
#define  MAX_DISTANCE  70 // Maximum distance we want to ping for (in centimeters).
                          // Maximum sensor distance is rated at 400-500cm.
#define  RELAXTIME    200 // milliseconds between ultrasonic distance checks

int DistanceCm;
unsigned long zeit;

NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

void distance() {
  DistanceCm = sonar.ping_cm(); // 10 pings per second
  if (DistanceCm == 0) DistanceCm = MAX_DISTANCE;
  lcd.setCursor(0,1);
  lcd.print("Ping: ");
  lcd.print(DistanceCm); 
  lcd.print(" cm  ");
  if(DistanceCm < 20) {
    beep(1);
    zeit -= (RELAXTIME - DistanceCm * 19);
  }
}

void beep(int beeps) {
  for(int i = 0; i < beeps; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    lcd.noBacklight();
    delay(20);
    digitalWrite(PIN_BUZZER, LOW);
    lcd.backlight();
    delay(100);
  }
}

void setup()
{
  pinMode(PIN_BUZZER, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
  lcd.print("T300 ultrasonic");
  beep(2);
  zeit = millis();
}

void loop()
{
  if(millis() > zeit + RELAXTIME) { // no delay function - not blocking the robot
    zeit = millis();
    distance();
  }
}
```

## Used library

I tried to use the LiquidCrystal_I2C library, but it has sometimes still the same mistake and displays only the first character. No update to 1.1.2 from Frank de Brabander helped. So I switched back to hd44780.h from Bill Perry 1.1.0.

## Use the servo to sweep

Will be updated later, as for now, just turn left.
