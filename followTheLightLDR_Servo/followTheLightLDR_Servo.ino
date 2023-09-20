#include <Servo.h>

#define LDRpin1 A0
#define LDRpin2 A1
int LDRValue1 = 0;
int LDRValue2 = 0;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  LDRValue1 = analogRead(LDRpin1);
  LDRValue2 = analogRead(LDRpin2);
  Serial.print("1: ");
  Serial.print(LDRValue1);
  Serial.print("\n");  
  Serial.print("2: ");
  Serial.print(LDRValue2);
  Serial.print("\n"); 
  delay(2);

  if (LDRValue1 > 800)
  {
      pos++; 
  }
  if (LDRValue2 > 800)
  {
      pos--;
  }
  myservo.write(pos);
}
