int Buzzer = 2; // Set Buzzer in D2 PIN
int Sensor = 3; // Set Sensor in D3 PIN

void setup() 
{
  pinMode(Sensor, INPUT);  // Sensor PIN as INPUT
  pinMode(Buzzer, OUTPUT); // Buzzer PIN as OUTPUT
}

void loop() 
{
  int val = digitalRead(Sensor); // Read the value from Sensor
  if (val == 1) // if found the vibration alert for 1 sec
  {
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
  }
}
