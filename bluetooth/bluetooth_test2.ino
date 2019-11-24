#define LED_PIN 13
 
char BTinput = '0';
byte speed = 200;

void setup() {
  Serial1.begin(9600);   // derial port Arduino Leonardo pin 0 and 1
}
 
void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    if (BTinput == 'A') 
    {
      digitalWrite(LED_PIN, HIGH);
      Serial1.write("ON");
    }
    if (BTinput == 'C') Serial.println("Here we go");
    if (BTinput == 'B')
    {
      digitalWrite(LED_PIN, LOW);
      Serial1.write("aus");
    }
    if (BTinput == 'E')// faster - plus 10 - triangle
    {
      speed = speed + 10;
    }
    if (BTinput == 'H')// slower - minus 10 - square
    {
      speed = speed - 10;
    } 
    if (BTinput == 'F')// maximum speed - circle
    {
      speed = 255;
    }
    if( speed > 255 ) speed = 255;
    Serial1.print( BTinput );
    Serial1.print("asdfghjkasdf");
  }
}
