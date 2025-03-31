#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 RTC;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void print2digits(int number)
{
  if (number >= 0 && number < 10)
    lcd.print('0');
  lcd.print(number, DEC);
}


int ButtonPin = 2;

char sentence[] = "She sell seashell by the seashore.   ";
int len = 0;

int strlen(char *a)
{
  int L = 0;
  while(*a != '\0')
  {
    a++; L++;
  }
  return L;
}

void setup()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();

  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(F(__DATE__),F(__TIME__)));

  pinMode(ButtonPin, INPUT);

  len = strlen(sentence);
}

void loop()
{
  
  lcd.setCursor(0, 1);
  lcd.print(sentence);
  
  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  print2digits(now.hour());
  lcd.print(':');
  print2digits(now.minute());
  lcd.print(':');
  print2digits(now.second());

  lcd.setCursor(10, 0);
  print2digits(now.day());
  lcd.print('/');
  print2digits(now.month());

  if(digitalRead(ButtonPin) == HIGH)
  {
    for(int i=0;i<=len;i++)
    {
      lcd.setCursor(0, 1);
      char S[16] = "";
      for(int j=0;j<16;j++)
          S[j] = sentence[(i+j)%len];
      lcd.print(S);
      delay(400);
    }
  }
}
