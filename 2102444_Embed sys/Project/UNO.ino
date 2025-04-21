#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define TILT_PIN 11
#define LED_R 8
#define LED_G 10
#define LED_B 9

#define TEMP_THRESHOLD 35.0
#define HUMID_THRESHOLD 65.0
#define TILT_TRIGGER_LEVEL HIGH

bool lastAlertState = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TILT_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setRGB(0, 255, 0);  // Initial state = green
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  bool tilt = digitalRead(TILT_PIN);

  bool dangerDetected = false;
  if (!isnan(temp) && !isnan(humid)) {
    if (temp >= TEMP_THRESHOLD || humid >= HUMID_THRESHOLD || tilt == TILT_TRIGGER_LEVEL) {
      dangerDetected = true;
    }
  }

  // --- Send room data to MEGA ---
  Serial.print("DATA,");
  Serial.print(temp); Serial.print(",");
  Serial.print(humid); Serial.print(",");
  Serial.println(tilt ? "TRIGGER" : "SAFE");

  // --- Send status only on change ---
  if (dangerDetected != lastAlertState) {
    if (dangerDetected) {
      Serial.println("ALERT");
      setRGB(255, 0, 0);  // Red
    } else {
      Serial.println("SAFE");
      setRGB(0, 255, 0);  // Green
    }
    lastAlertState = dangerDetected;
  }

  delay(200);  // Short delay for rapid updates
}

void setRGB(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}
