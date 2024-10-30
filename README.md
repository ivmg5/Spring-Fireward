# **Spring-Fireward**
> *An IoT-based system for forest fire prevention, detection, and management in the Bosque de La Primavera.*

## **Introduction**
Spring-Fireward is designed to address the critical issue of frequent forest fires in Jalisco's Bosque de La Primavera by leveraging the Internet of Things (IoT) for real-time monitoring and alerting. This system integrates sensors and data analysis to enhance early detection capabilities, aiming to significantly mitigate fire risks and manage incidents more effectively.

## **Project Description**
- **Main functionality:** Real-time monitoring and alert system for forest fires, using smoke, temperature/humidity, and water sensors connected to a Firebase database and visualized through a web application.
- **Technologies used:** ESP8266 microcontroller, Firebase real-time database, DHT11, MQ-2 smoke sensor, water sensor, Arduino IDE, HTML/CSS.
- **Challenges faced:** Network stability in forested areas, calibration of sensors, ensuring reliable connectivity for real-time data transfer.
- **Future improvements:** Expand scalability to cover larger areas, integrate advanced analytics and predictive models, optimize energy usage through solar power.

## **Table of Contents**
1. [Introduction](#introduction)
2. [Project Description](#project-description)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Additional Documentation](#additional-documentation)
6. [Testing](#testing)
7. [License](#license)

## **Installation**
1. **Prerequisites**:
   - **ESP8266WiFi** - [Installation](https://esp8266-arduino-spanish.readthedocs.io/es/latest/)
   - **Firebase Arduino Library** - [Firebase Docs](https://firebase.google.com/docs)
   - **DHT Library** - [Adafruit DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
   
2. **Clone the repository:**
   ```bash
   git clone https://github.com/ivmg5/Spring-Fireward.git
   cd Spring-Fireward
   ```

3. **Upload Code to ESP8266**:
   - Open `main.ino` in Arduino IDE.
   - Configure Wi-Fi credentials and Firebase API details in `main.ino`.
   - Select ESP8266 as the board and upload.

4. **Run the system:**
   - Connect the sensors as specified and start the ESP8266.

### **Configuration Options**
- **Firebase Configuration**: Enter `API_KEY`, `DATABASE_URL`, `USER_EMAIL`, and `USER_PASSWORD` in `main.ino` to establish database connectivity.
- **Debugging Options**: Use `Serial.begin(9600);` to monitor debug messages via the serial console.

## **Usage**
To monitor environmental conditions and receive alerts:
1. Connect the device to the network specified in `main.ino`.
2. Access the ESP8266's IP address in a web browser for real-time monitoring.

**Example usage:**
```arduino
float temperature = dht.readTemperature();
Firebase.setFloat("/readings/temperature", temperature);
```

## **Additional Documentation**
Refer to `Documentation.pdf` in the repository for in-depth project details, architecture, and component specifications.

## **Testing**
Run tests to validate system functionality:
```bash
// Example to check temperature reading
Serial.println(dht.readTemperature());
```

## **License**
This project is licensed under the MIT License.

[![Build Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![Firebase Connection](https://img.shields.io/badge/firebase-connected-blue)](#)
