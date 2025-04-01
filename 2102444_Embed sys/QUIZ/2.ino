#include "DHT.h"
#include <LiquidCrystal_I2C.h>

const int Buzzer = 2;       // Set Buzzer in D2 PIN
const int Sensor = 3;       // Set Sensor in D3 PIN
const int DHT_PIN = 4;      // Set DHT11  in D4 PIN
const int BUTTON_PIN = 5;   // Set Button in D5 PIN

const int Vibrate_LED = 8;  // Set Vibrate_LED in D8 PIN
const int Humidity_LED = 9; // Set Humidity_LED in D9 PIN
const int Temp_LED = 10;    // Set Temp_LED in D10 PIN

bool RESET = true;

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  pinMode(Sensor, INPUT);  // Sensor PIN as INPUT
  pinMode(Buzzer, OUTPUT); // Buzzer PIN as OUTPUT
  pinMode(BUTTON_PIN, INPUT);
  pinMode(Vibrate_LED, OUTPUT);
  pinMode(Humidity_LED, OUTPUT);
  pinMode(Temp_LED, OUTPUT);

  dht.begin(); // Start DHT11
  lcd.init();  // Start LCD
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  bool overtemp = (t >= 32 && t <= 36);
  bool overhum = (h >= 50 && h <= 60);
  bool Vibra = (digitalRead(Sensor) == HIGH);
  
  if (overtemp || overhum || Vibra)
  {
    lcd.clear();
    while(digitalRead(BUTTON_PIN) != HIGH)
    {
      h = dht.readHumidity();
      t = dht.readTemperature();
      f = dht.readTemperature(true);
      
      overtemp = (t >= 32 && t <= 36);
      overhum = (h >= 50 && h <= 60);
      Vibra = (digitalRead(Sensor) == HIGH);

      Serial.println(h, t);
      Serial.println(Vibra);

      if(overtemp)
      { 
        digitalWrite(Temp_LED, HIGH);
        digitalWrite(Buzzer, HIGH);
        lcd.setCursor(8, 0);
        lcd.print("Over Temp");
      }
      
      if(overhum)
      {
        digitalWrite(Humidity_LED, HIGH);
        digitalWrite(Buzzer, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Over Humidity");
      }

      if(Vibra)
      {
        digitalWrite(Vibrate_LED, HIGH);
        digitalWrite(Buzzer, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Vibrate");
      }
    }
    RESET = true;
  }

  if(RESET)
  {
    for(int i=8;i<=10;i++)
      digitalWrite(i, LOW);
    digitalWrite(Buzzer, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Have a good Day!!");
    RESET = false;
  }
  delay(3000);
}
