int Buzzer = 2;
int Sensor = 3;

void setup() 
{
  pinMode(Sensor, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() 
{
  int val = digitalRead(Sensor);
  if (val == 1)
  {
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
  }
}
