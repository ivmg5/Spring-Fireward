# Spring-Fireward Project

## Overview

The **Spring-Fireward** project is an IoT-based system designed to prevent, detect, and manage forest fires in real-time. It uses a set of sensors, including smoke, temperature/humidity, and water sensors, which are connected to an ESP8266 microcontroller. Data from these sensors is continuously monitored and transmitted to a Firebase real-time database, where it is visualized and analyzed using a web application.

This system aims to enhance the detection of potential fire threats in the **Bosque de La Primavera** in Jalisco, Mexico, which has faced significant ecological damage from frequent forest fires.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [System Overview](#system-overview)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Project Management](#project-management)
- [License](#license)

## Introduction

The **Spring-Fireward** project aims to address the frequent occurrence of forest fires in Bosque de La Primavera by providing a system capable of:

- **Real-time Monitoring**: Using IoT sensors to gather data about smoke, temperature, humidity, and water levels.
- **Early Detection**: Alerting users to potential fire risks before ignition or in the early stages.
- **Data Analysis**: Collecting data over time to understand and predict fire patterns.

## Features

- **Smoke Detection**: An MQ-2 smoke sensor to monitor smoke levels in the environment.
- **Temperature and Humidity Monitoring**: Using DHT11/DHT22 sensors to track environmental conditions.
- **Water Detection**: A water sensor to detect moisture from rainfall or firefighting efforts.
- **Web Application**: Provides a user-friendly interface for visualizing real-time data and system alerts.
- **Firebase Integration**: Sensor data is stored in Firebase, allowing real-time synchronization and alerting.

## System Overview

The system consists of:

- **ESP8266 Microcontroller**: Handles sensor data collection, processing, and transmission to Firebase.
- **Sensor Network**:
  - **MQ-2 Smoke Sensor**: Detects smoke and gases.
  - **DHT11 Temperature and Humidity Sensor**: Measures temperature and humidity.
  - **Water Sensor**: Indicates moisture, useful for detecting firefighting activities.
- **Web Interface**: Displays live data from the sensors and indicates alert statuses with visual cues.

The system architecture includes sensors connected to the ESP8266, which communicates with a Firebase real-time database. A web application then retrieves data from Firebase to provide a comprehensive dashboard for monitoring.

## Hardware Components

- **ESP8266 NodeMCU Microcontroller**
- **MQ-2 Smoke Sensor**
- **DHT11/DHT22 Temperature and Humidity Sensor**
- **Water Detection Sensor**
- **Breadboard and Jumper Wires**
- **LED Indicators (Red, Yellow, Green, Blue)**
- **Protective Enclosure (e.g., Acrylic Box)**

## Software Components

- **Arduino IDE**: Used for programming the ESP8266.
- **Firebase**: Real-time database used for data storage.
- **Web Application**: HTML and JavaScript for data visualization.
- **Libraries Used**:
  - `FirebaseESP8266.h` for Firebase connectivity.
  - `DHT.h` for sensor readings.
  - `ESP8266WiFi.h` for Wi-Fi connection.
  - `ESP8266WebServer.h` for the local web server.

## Installation and Setup

### Hardware Setup
1. Connect the smoke sensor (MQ-2), temperature/humidity sensor (DHT11), and water sensor to the ESP8266.
2. Assemble the components on a breadboard and connect the LEDs as specified in the circuit schematic.
3. Ensure all connections are properly made to avoid malfunction.

### Software Setup
1. **Clone the Repository**:
    ```bash
    git clone https://github.com/yourusername/spring-fireward.git
    ```
2. **Open the Project in Arduino IDE**:
    - Make sure to select the appropriate board (NodeMCU 1.0 (ESP-12E Module)).
3. **Install Required Libraries**:
    - `FirebaseESP8266`
    - `DHT`
    - `ESP8266WiFi`
4. **Configure Firebase and Wi-Fi Credentials**:
    - Update `WIFI_SSID`, `WIFI_PASSWORD`, `API_KEY`, and `DATABASE_URL` in the `main.ino` file to match your configuration.
5. **Upload the Code**:
    - Upload `main.ino` to the ESP8266 microcontroller.

## Usage

1. **Power the System**: Connect the ESP8266 to a power source.
2. **Monitor via Web Application**: Access the web application by entering the IP address assigned to the ESP8266 on your local network.
    - The page will display real-time sensor data and alert statuses.
3. **Alerts**:
    - **Green LED**: Normal conditions, no fire risk.
    - **Yellow LED**: High temperature detected, increased fire risk.
    - **Red LED**: Smoke detected, indicating potential fire.
    - **Blue LED**: Water detected, indicating firefighting efforts underway.

## Project Management

This project was developed using agile methodologies, specifically the Scrum framework, with user stories and sprints designed to guide development. The primary goal was to create a functional IoT prototype capable of detecting and managing fire risks.

### Potential Future Improvements
- **Mobile App Integration**: Develop a mobile application for alerts and remote monitoring.
- **Machine Learning**: Implement machine learning models for predicting fire risks based on historical data.
- **Energy Efficiency**: Incorporate solar panels for sustainable power.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
