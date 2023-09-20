Things to do:

Try the photo


# Setting up the Arduino IDE

In the IDE Tools menu ensure the board matches the board you are using

Problem uploading to Arduino WIFI:
avrdude: stk500_recv(): programmer is not responding
https://support.arduino.cc/hc/en-us/articles/4401874331410--Error-avrdude-when-uploading

# Getting a value from a Light Dependant Resistor

First place the LDR inside a breadboard, orientation is not important, same as normal resistors, LDR don't care about the polarity. (Image 1)
Place the 10 k Ohmresistor on one side of the LDR, this is our Pull Down resistor which we are going to connect with the ground. (Image 2)
Connect the other end of the 10 k Ohm resistor with the GND on the Arduino, and the other side of the LDR with the 5 V pin on the Arduino. (Image 3)
Now we need to insert an analog read jumper wire in parallel with the LDR. We do that by connecting the A0 with the LDR at the point before the 10 k Ohm resistor. (Image 4)

```
#define LDRpin A0
int LDRValue = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  LDRValue = analogRead(LDRpin);
  Serial.println(LDRValue);
  delay(2);
}
```

range is around 450-1000

# Getting a value from a Photodiode

5V pin from Arduino -> 1M resistor -> photodiode cathode (-, short leg) -> Arduino GND pin

Arduino Analog in pin A4 to between 1M resistor and photodiode

GND to anode

https://www.ee-diary.com/2021/08/photodiode-light-detector-with-arduino.html

range we get is 4-5V

```
//alias pin name for Photodiode
int photodiodePin = A4;

void setup(){
  Serial.begin(9600); //set Serial output baud rate
  //For output format
  Serial.println("\nVoltage(V):");
  Serial.print("--------------------------------------------------\n");
}

void loop() {
    int anaValue = analogRead(photodiodePin); // potentiometer voltage

    float voltage = 5-(anaValue/1024.0)*5;
        Serial.println(String(voltage,2)+"V");
        delay(2000); //delay 2000ms to prevent any duplicates

}
```

# Outputing a value to a servo

Three wires
- power red to 5V rail on breadboard
- ground black/brown to GND rail on breadboard
- signal yellow/orange to PWM pin 9

```
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
```

# LDR + Servo

```
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
```