# 🌱 Smart Plant Monitoring System (ESP32 + IoT)

## 📌 Introduction
The **Smart Plant Monitoring System** is an IoT-based solution designed to monitor plant health in real-time using sensors and an ESP32 microcontroller.

It tracks:
- 🌿 Soil Moisture  
- 🌡️ Temperature  
- 💧 Humidity  

Data is displayed locally on an OLED screen and remotely via the Blynk IoT app. Alerts are provided using an RGB LED and buzzer when plant conditions become critical.

---

## 🎯 Features
-  Real-time monitoring using ESP32  
-  Remote access via Blynk IoT app  
-  OLED display for live data  
-  Buzzer alerts for critical conditions  
-  RGB LED status indication  
-  Auto-refresh every 2 seconds  

---

## 🛠️ Components Required
- ESP32 Microcontroller  
- Soil Moisture Sensor  
- DHT11 Temperature & Humidity Sensor  
- 0.96" OLED Display (I2C)  
- RGB LED  
- Buzzer  
- Breadboard
- Resistors  
- Connecting Wires   

---

## 🔌 Circuit Connections

### 🌡️ DHT11 Sensor
- VCC → 3.3V  
- GND → GND  
- DATA → GPIO 4  

### 🌱 Soil Moisture Sensor
- VCC → 3.3V / 5V  
- GND → GND  
- A0 → GPIO 34  

### 📺 OLED Display (I2C)
- VCC → 3.3V  
- GND → GND  
- SCL → GPIO 22  
- SDA → GPIO 21  

### 🌈 RGB LED
- RED → GPIO 15  
- GREEN → GPIO 2  
- BLUE → GPIO 5  
- GND → GND  

### 🔔 Buzzer
- Signal → GPIO 18  
- GND → GND  

---

## ⚙️ Working Process

### 1️⃣ Initialization
- ESP32 initializes sensors, OLED display, and Blynk connection  
- System stops if OLED is not detected  

### 2️⃣ Sensor Readings
- Soil moisture is read as analog value and converted to percentage  
- Temperature and humidity are read using DHT11  
- Data updates every **2 seconds**  

### 3️⃣ OLED Display
Displays:
- Soil Moisture (%)  
- Temperature (°C)  
- Humidity (%)  

---

### 4️⃣ RGB LED Indication

| Color | Status |
|------|--------|
| 🟢 Green | Healthy |
| 🔵 Blue | Moderate |
| 🔴 Red | Critical |

---

### 5️⃣ Buzzer Alerts
The buzzer activates when:
- Soil moisture is too low  
- Temperature exceeds threshold  

---

### 6️⃣ 📱 Blynk App Integration
- Displays real-time sensor data:
  - Soil Moisture  
  - Temperature  
  - Humidity  
- Sends alerts for critical conditions  
- Enables remote monitoring from anywhere  

---

## 📊 Results
- Stable and accurate sensor readings observed  
- Soil moisture responded dynamically  
- DHT11 provided consistent environmental data  
- OLED displayed clear real-time values  
- RGB LED gave instant visual feedback  
- Buzzer alerts worked effectively  
- Blynk app displayed data accurately in real time  

---

## ✅ Conclusion
This project provides a **low-cost, efficient IoT-based plant monitoring system** combining:
- Real-time sensing  
- Local display  
- Smart alerts  
- Remote monitoring  

It is suitable for:
- 🌿 Home gardening  
- 🌾 Agriculture  
- 🔬 Research applications  

---

## 📸 Project Images
![System Setup](images/setup.jpg)
![Circuit Diagram](images/circuit.png)
![OLED Output](images/oled.jpg)

---

## 🎥 Project Demo Video

[Watch Demo Video](https://youtube.com/shorts/3U2IQZvxFuo?feature=share)

---

## 🚀 Future Improvements
-  Cloud data logging  
-  Data analytics dashboard  
-  AI-based plant recommendations  
-  Automatic irrigation system  

---
