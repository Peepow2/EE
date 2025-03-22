const int Button1 = 2; // ปุ่มที่่ 1 อยู่ที่ pin 2
const int Button2 = 6; // ปุ่มที่่ 2 อยู่ที่ pin 6
const int LED_PIN = 11; // LED ควบคุมด้วย pin 11

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
  bool LED_state = digitalRead(Button1) == HIGH || \
                    digitalRead(Button2) == HIGH;
  
  // แสดงผลตาม LED_state
  digitalWrite(LED_PIN, LED_state);
}
