#define E1 10 // enable - with PWM
#define M1 12
#define E2 11
#define M2 13

void setup() {
  pinMode(M1, OUTPUT); // no need for analog output
  pinMode(M2, OUTPUT);
  delay(3000);         // wait a 3 seconds  
  // enable
  analogWrite(E1, 128); // not so fast - down by 50%
  analogWrite(E2, 128);
}

void loop() {
  digitalWrite(M1, HIGH);  // forward
  digitalWrite(M2, HIGH);
  delay(1000);
  digitalWrite(M1, LOW);  // backward
  digitalWrite(M2, LOW);
  delay(1000);
  digitalWrite(M1, LOW);  // left
  digitalWrite(M2, HIGH);
  delay(1000);
  digitalWrite(M1, HIGH);  // right
  digitalWrite(M2, LOW);
  delay(1000);  
}
