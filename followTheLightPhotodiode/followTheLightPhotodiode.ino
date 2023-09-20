
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
        delay(250); //delay 2000ms to prevent any duplicates

}
