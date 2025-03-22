const int Button1 = 2; // ปุ่มที่่ 1 อยู่ที่ pin 2
const int Button2 = 3; // ปุ่มที่่ 2 อยู่ที่ pin 3
const int LED_PIN = 4; // LED ควบคุมด้วย pin 4

void setup() 
{
  Serial.begin(9600);
  pinMode(Button1, INPUT); 
  pinMode(Button2, INPUT);   
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // ถ้าปุ่มที่ 1 ถูกกด หรือ ปุ่มที่ 2 ถูกกด 
  bool LED_state = digitalRead(Button1) + \
                      digitalRead(Button2) == HIGH;
  
  // แสดงผลตาม LED_state
  digitalWrite(LED_PIN, LED_state);
}
