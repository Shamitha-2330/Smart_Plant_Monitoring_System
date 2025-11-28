/********* Blynk & WiFi CONFIG *********/
#define BLYNK_TEMPLATE_ID "TMPL3lP8gAaJK"
#define BLYNK_TEMPLATE_NAME "Smart Plant Monitoring System"
#define BLYNK_AUTH_TOKEN "0Us-gxc4NTeMEIGsBirH-7vFfiRBzxcy"

#define BLYNK_FIRMWARE_VERSION "1.0.0"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

/********* OLED & SENSOR INCLUDES *********/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED CONFIG
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// PINS
#define SOIL_MOISTURE_PIN 34
#define DHT_PIN           4
#define DHT_TYPE          DHT11
#define BUZZER_PIN        15

// 3 Separate LEDs
#define RED_LED    13
#define GREEN_LED  2
#define BLUE_LED   5

DHT dht(DHT_PIN, DHT_TYPE);

// Calibration (UPDATE AFTER TESTING)
int dryValue = 3600;   // sensor reading in dry soil
int wetValue = 1500;   // sensor reading in wet soil

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Blynk timer
BlynkTimer timer;

/********* HELPER: LED COLOR *********/
void setColor(bool red, bool green, bool blue) {
  digitalWrite(RED_LED,   red   ? HIGH : LOW);
  digitalWrite(GREEN_LED, green ? HIGH : LOW);
  digitalWrite(BLUE_LED,  blue  ? HIGH : LOW);
}

/********* SEND DATA TO BLYNK *********/
void sendToBlynk() {
  int rawMoisture = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercentage = map(rawMoisture, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 ERROR (Blynk send)!");
    return;
  }

  // Send to Blynk virtual pins
  Blynk.virtualWrite(V0, moisturePercentage);  // Soil moisture %
  Blynk.virtualWrite(V1, temperature);         // Temperature °C
  Blynk.virtualWrite(V2, humidity);            // Humidity %
}

/********* SETUP *********/
void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }
  display.clearDisplay();
  display.display();
  Serial.println("System Ready!");

  // Connect to WiFi + Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Call sendToBlynk every 2 seconds
  timer.setInterval(2000L, sendToBlynk);  // 2000 ms = 2s[web:39]
}

/********* MAIN LOOP *********/
void loop() {
  Blynk.run();
  timer.run();

  // Read soil moisture
  int rawMoisture = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Raw Moisture Value: ");
  Serial.println(rawMoisture);

  int moisturePercentage = map(rawMoisture, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 ERROR!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.print("DHT ERROR!");
    display.display();
    delay(2000);
    return;
  }

  Serial.print("Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Update OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 10);
  display.print("Moisture: ");
  display.print(moisturePercentage);
  display.println("%");

  display.setCursor(10, 30);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(10, 50);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.display();

  // Thresholds
  bool tempBad         = (temperature < 20 || temperature > 30);
  bool moistTooDry     = (moisturePercentage < 30);
  bool moistGettingDry = (moisturePercentage >= 30 && moisturePercentage < 40);
  bool moistGood       = (moisturePercentage >= 40 && moisturePercentage <= 80);
  bool moistTooWet     = (moisturePercentage > 80);

  // LED & Buzzer logic
  if (moistTooDry || moistTooWet || tempBad) {
    setColor(true, false, false);   // RED
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (moistGettingDry && !tempBad) {
    setColor(false, false, true);   // BLUE
    digitalWrite(BUZZER_PIN, LOW);
  }
  else if (moistGood && !tempBad) {
    setColor(false, true, false);   // GREEN
    digitalWrite(BUZZER_PIN, LOW);
  }
  else {
    setColor(false, false, true);   // BLUE
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  // small delay; main timing for Blynk is via timer
}
