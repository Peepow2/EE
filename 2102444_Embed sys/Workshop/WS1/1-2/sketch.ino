const int LDR_PIN = A2;  // Analog pin for LDR
const int LED_PIN = 7;   // Digital pin for LED
const int THRESHOLD = 500; // Adjust based on environment

const float GAMMA = 0.7;
const float RL10 = 50;

float ldrVal2lux(int ldrVal) // ldrVal2lux Formula
{
  float voltage = ldrVal / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  return lux;
}

void setup() 
{
  Serial.begin(9600);  
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int ldrValue = analogRead(LDR_PIN); // Read ldrValue
  float lux = ldrVal2lux(ldrValue); // convert ldrValue to lux
  Serial.println(lux);

  bool LED_State = (int(lux) < THRESHOLD); 
  digitalWrite(LED_PIN, LED_State); // Turn on or off LED

  delay(100);
}
