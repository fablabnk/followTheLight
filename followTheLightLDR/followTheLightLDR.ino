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
