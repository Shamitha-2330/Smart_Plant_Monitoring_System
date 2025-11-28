Smart Plant Monitoring System
1. Introduction

The Smart Plant Monitoring System is designed to continuously track soil moisture, temperature, humidity, and overall plant health using sensors connected to an ESP32 microcontroller. Real-time data is displayed on an OLED screen and can be monitored remotely through the Blynk IoT application. Additional alert mechanisms such as an RGB LED and buzzer help users take immediate action when plant conditions become unfavorable.

2. Components Required

ESP32 Microcontroller – Main controller for processing sensor data.

Soil Moisture Sensor – Measures soil water level.

DHT11 Sensor – Reads temperature and humidity.

0.96" OLED Display (I2C) – Displays real-time sensor readings.

RGB LED – Indicates plant status (Green = Good, Blue = Moderate, Red = Critical).

Buzzer – Alerts user in extreme temperature or dry soil conditions.

Connecting Wires

Breadboard

Power Supply (5V)

3. Circuit Connections
DHT11 Sensor

VCC → 3.3V

GND → GND

DATA → GPIO 4

Soil Moisture Sensor

VCC → 3.3V / 5V

GND → GND

A0 → GPIO 34

OLED Display (I2C)

VCC → 3.3V

GND → GND

SCL → GPIO 22

SDA → GPIO 21

RGB LED

RED → GPIO 15

GREEN → GPIO 2

BLUE → GPIO 5

GND → GND

Buzzer

Signal → GPIO 18

GND → GND

4. Working Process
1. Initialization

When powered on, the ESP32 initializes all sensors, OLED display, and Blynk connection. If the OLED is not detected, the system stops to avoid faulty readings.

2. Sensor Readings

Soil moisture is read as an analog value and converted to percentage.

Temperature and humidity are read using the DHT11 sensor.

Data refreshes every 2 seconds.

3. OLED Display Output

The OLED shows:

Soil Moisture (%)

Temperature (°C)

Humidity (%) All values are displayed in clear readable text.

4. RGB LED Indication

Green: Healthy moisture and temperature.

Blue: Moderately dry soil or slight temperature deviations.

Red: Critical dryness or temperature beyond 20–30 °C.

5. Buzzer Alerts

The buzzer activates when:

Soil moisture falls below the set threshold.

Temperature exceeds ideal plant conditions.

6. Blynk App Integration

Sensor readings are sent to the Blynk app using virtual pins. Users can view:

Soil Moisture Gauge

Temperature Display

Humidity Display

Notification Alerts (when critical values occur)

This allows remote monitoring from anywhere using the Blynk mobile app.

5. Results and Discussion

The ESP32 successfully captured soil moisture, temperature, and humidity values with stable readings. Soil moisture changed dynamically as expected, and the DHT11 showed reliable environmental data. The RGB LED provided immediate visual status indication without requiring the user to check the display. The buzzer provided timely alerts for extreme dryness or temperature issues. The Blynk app displayed all sensor values accurately, making remote monitoring simple and effective.

6. Conclusion

This Smart Plant Monitoring System provides an efficient and low-cost solution for ensuring plant health. It offers on-device display, sensor-based alerts, and remote mobile-based monitoring. The combination of sensors, ESP32 controls, OLED visualization, and Blynk IoT integration creates a complete automated care system suitable for home gardening, agriculture, and research applications.
