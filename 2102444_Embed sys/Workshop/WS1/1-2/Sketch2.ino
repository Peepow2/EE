const int LDR_PIN = A2;  // Analog pin for LDR
const int LED_PIN = 7;   // Digital pin for LED
const int THRESHOLD = 500; // Adjust based on environment

void setup() 
{
  Serial.begin(9600);  
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int ldrValue = analogRead(LDR_PIN); // Read ldrValue
  Serial.println(ldrValue);

  bool LED_State = (ldrValue < THRESHOLD); 
  digitalWrite(LED_PIN, LED_State); // Turn on or off LED

  delay(100);
}
