#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <RTClib.h>

// --- RFID ---
#define RST_PIN 5
#define SS_PIN 4
MFRC522 rfid(SS_PIN, RST_PIN);

// --- RTC ---
RTC_DS3231 rtc;

// --- LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- RGB LED ---
#define LED_R 5
#define LED_G 6
#define LED_B 7

// --- Buzzer ---
#define BUZZER A8

// --- Keypad ---
const byte ROWS = 2;
const byte COLS = 2;
char keys[ROWS][COLS] = {{'A', 'B'}, {'C', 'D'}};
byte rowPins[ROWS] = {10, 9};
byte colPins[COLS] = {11, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- Room Status ---
byte roomStatus[4] = {0, 0, 0, 0};  // Room A–D
bool systemPaused = false;

// --- Scrolling data ---
String roomAData = "DATA,N/A,N/A,N/A";
String scrollText = "";
int scrollIndex = 0;
unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 300;

// --- LCD Refresh Timer ---
unsigned long lastLCDUpdate = 0;
const unsigned long lcdRefreshInterval = 1000;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // From UNO → MEGA RX1 = D19

  SPI.begin();
  rfid.PCD_Init();
  rtc.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.clear();
  Serial.println("System Ready");
}

void loop() {
  const byte authorizedUID[4] = {0x5A, 0x83, 0x51, 0xB3};

  // --- RFID scan to toggle pause ---
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uidString = "";
    bool isAuthorized = true;

    if (rfid.uid.size != sizeof(authorizedUID)) {
      isAuthorized = false;
    } else {
      for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] != authorizedUID[i]) {
          isAuthorized = false;
          break;
        }
      }
    }

    for (byte i = 0; i < rfid.uid.size; i++) {
      if (rfid.uid.uidByte[i] < 0x10) uidString += "0";
      uidString += String(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) uidString += " ";
    }
    uidString.toUpperCase();

    lcd.clear();
    if (isAuthorized) {
      systemPaused = !systemPaused;

      if (systemPaused) {
        digitalWrite(BUZZER, LOW);
        setRGB(0, 0, 255);  // Blue
        lcd.setCursor(0, 0); lcd.print("Valid Card");
        lcd.setCursor(0, 1); lcd.print("System Reset");
        for (int i = 0; i < 3; i++) {
          tone(BUZZER, 1000, 150);
          delay(200);
        }
        noTone(BUZZER);
      } else {
        lcd.setCursor(0, 0); lcd.print("Valid Card");
        lcd.setCursor(0, 1); lcd.print("System Resumed");
        tone(BUZZER, 800, 600);
        delay(650);
        noTone(BUZZER);
      }

      Serial.print("UID: "); Serial.println(uidString);
    } else {
      lcd.setCursor(0, 0); lcd.print("Invalid Card");
      lcd.setCursor(0, 1); lcd.print(uidString);
      Serial.print("Rejected UID: "); Serial.println(uidString);
    }

    delay(1500);
    rfid.PICC_HaltA();
  }

  // ✅ Always read Serial1 from UNO
  while (Serial1.available()) {
    String input = Serial1.readStringUntil('\n');
    input.trim();

    if (input.startsWith("DATA")) {
      roomAData = input;

      // Extract status from DATA line
      int lastComma = input.lastIndexOf(',');
      String status = input.substring(lastComma + 1);

      if (status == "TRIGGER") {
        roomStatus[0] = 1;
        if (!systemPaused) digitalWrite(BUZZER, HIGH);
      } else if (status == "SAFE") {
        roomStatus[0] = 0;
        digitalWrite(BUZZER, LOW);  // Always allow buzzer to turn off
      }
    } else if (input == "ALERT") {
      roomStatus[0] = 1;
      if (!systemPaused) digitalWrite(BUZZER, HIGH);
    } else if (input == "SAFE") {
      roomStatus[0] = 0;
      digitalWrite(BUZZER, LOW);
    }
  }

  // --- Scroll during reset ---
  if (systemPaused) {
    showScrollingResetScreen();
    return;
  }

  // --- RGB LED reflects room A status ---
  if (roomStatus[0] == 1) {
    setRGB(255, 0, 0);  // Red
  } else {
    setRGB(0, 255, 0);  // Green
  }

  // --- Keypad room status check ---
  char key = keypad.getKey();
  if (key) {
    int roomIndex = -1;
    String roomName = "";

    switch (key) {
      case 'A': roomIndex = 0; roomName = "Room A"; break;
      case 'B': roomIndex = 1; roomName = "Room B"; break;
      case 'C': roomIndex = 2; roomName = "Room C"; break;
      case 'D': roomIndex = 3; roomName = "Room D"; break;
    }

    if (roomIndex >= 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(roomName);
      lcd.setCursor(0, 1);
      if (roomStatus[roomIndex] == 0) {
        lcd.print("Status: Safe");
      } else {
        lcd.print("Status: DANGER");
      }
      delay(1500);
    }
  }

  // --- Default display ---
  if (millis() - lastLCDUpdate >= lcdRefreshInterval) {
    showDefaultScreen();
    lastLCDUpdate = millis();
  }
}

// --- Scroll Room A Data during Reset Mode ---
void showScrollingResetScreen() {
  static String baseText = "";

  baseText = "A," + roomAData + " | B,DATA,N/A,N/A,N/A | C,DATA,N/A,N/A,N/A | D,DATA,N/A,N/A,N/A | ";

  if (millis() - lastScrollTime >= scrollInterval) {
    scrollText = baseText + baseText;
    String window = scrollText.substring(scrollIndex, scrollIndex + 16);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(window);
    lcd.setCursor(0, 1);
    lcd.print("System Reset");

    scrollIndex++;
    if (scrollIndex >= baseText.length()) scrollIndex = 0;
    lastScrollTime = millis();
  }
}

// --- RGB Helper ---
void setRGB(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

// --- LCD: Default display ---
void showDefaultScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (roomStatus[0] == 1) {
    lcd.print("DANGER");
  } else {
    lcd.print("Safe");
  }

  DateTime now = rtc.now();
  lcd.setCursor(0, 1);
  print2digits(now.hour());
  lcd.print(':');
  print2digits(now.minute());
  lcd.print(':');
  print2digits(now.second());
  lcd.print(" | ");
  print2digits(now.day());
  lcd.print('/');
  print2digits(now.month());
}

// --- Helper: 2-digit formatting ---
void print2digits(int number) {
  if (number < 10) lcd.print('0');
  lcd.print(number);
}
