const int LDR_PIN = A2;  // Analog pin for LDR
const int LED_PIN = 7;   // Analog pin for LED
const int ButtonPin = 2; // Digital pin for Button

bool state = true;
int LED_val = 0;

void setup() 
{
  Serial.begin(9600);  
  pinMode(ButtonPin, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int ldrValue = analogRead(LDR_PIN); // Read ldrValue

  if (digitalRead(ButtonPin) == HIGH)
    state = !state;

  if (state)
    LED_val = map(ldrValue, 200, 700, 0, 255);
  else
    LED_val = map(ldrValue, 700, 200, 0, 255);

  analogWrite(LED_PIN, LED_val);
}
