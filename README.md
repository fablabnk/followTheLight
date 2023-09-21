This repo is a quick start guide for project ambassadors and educators to get up and running quickly with the [Follow the Light](https://www.notion.so/42wolfsburgberlin/Follow-the-Light-cfd6d5b28ad84da4ae6154757d6e9e80) project from the FabLab curriculum, so that they can support others.

In our training session we focussed on getting familiar with the Arduino IDE and breadboarding simple circuits using two light sensors and one servo, where the servo tracks one way when light exceed a threshold on one sensor and the other way when it exceeds a threshold on the other sensor. This is the minimum needed to be able to pass the project.

The two types of sensor we tried were Light Dependant Resistors (LDR's) and Photodiodes.

Things we still need to do:

- Try the photodiode with the 10K resistors specified in the project instead of the 1M resistor from the tutorial we tried
- Pinpoint the problem uploading to Arduino WIFI: avrdude: stk500_recv(): programmer is not responding. See: https://support.arduino.cc/hc/en-us/articles/4401874331410--Error-avrdude-when-uploading
- Check how many servos could typically be used when powering from your PC's USB port

# Setting up the Arduino IDE

In the IDE Tools menu ensure:
- the board matches the board you are using
- the correct port has been chosen (typically USB)
- "Programmer" doesn't seem to matter

If you are using the Serial Monitor to track values, make sure the baud rate in the program is set to the same baud rate as shown in the bottom right corner of the serial monitor (or vice versa).

# Getting a value from a Light Dependant Resistor

Wiring:
- 5V pin of Arduino -> LDR -> 10K resistor -> GND of Arduino
- to read the value, connect a point between the LDR and the 10K resistor to the analog pin A0 of the Arduino

Upload the following code to your board:
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

The response range for the LDR we tested was around 450-1000

# Getting a value from a photodiode

Wiring:
- 5V Arduino pin -> 1M resistor -> photodiode cathode (minus i.e. short leg)
- photodiode anode (plus i.e. long leg) -> Arduino GND pin
- to read the value, connect a point between 1M resistor and photodiode to Arduino analog pin A4

The response range for the photoresistor we tested was between 4-5 Volts

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
        Serial.println(String(voltage,4)+"V");
        delay(250);

}
```

# Outputing a value to a servo

Wiring of the three wires:
- 5V rail on breadboard goes to servo red wire (power)
- GND rail on breadboard goes to black/brown wire (ground)
- yellow/orange wire goes to PWM pin 9 (signal)

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

# Two LDR's plus Servo Example

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