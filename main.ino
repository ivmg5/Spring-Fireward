// Specific library configuration for ESP32 and ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WifiUDP.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#endif

// Pin definitions and sensor configuration
#define PIN_SENSOR_DHT 05
#include <DHT.h>
#define DHTTYPE DHT11 // DHT 11
DHT dht(PIN_SENSOR_DHT, DHTTYPE);

// Time and date
#include <RTClib.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

// Information for generating tokens and payloads for Firebase
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// WiFi credentials
const char* WIFI_SSID = "Diego";
const char* WIFI_PASSWORD = "12345678";

// API information and Firebase credentials
#define API_KEY "AIzaSyDK1j9W3CmFYRXXfmwoxa0gWj2ykM4Ztys"
#define DATABASE_URL "https://spring-fireward-a153a-default-rtdb.firebaseio.com"
#define USER_EMAIL "a01643382@tec.mx"
#define USER_PASSWORD "123456"

// Firebase object configuration
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// NTP client configuration
#define NTP_OFFSET 60 * 60  // In seconds
#define NTP_INTERVAL 60 * 1000  // In milliseconds
#define NTP_ADDRESS "pool.ntp.org"  // NTP URL
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
TimeChangeRule usMST = {"CST", Second, Sun, Mar, 2, -360};
Timezone usAZ(usMST, usMST);
time_t local, utc;

// Set day and month names
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// Sensor variables
int water;
int LED = 16; // Water LED
int LED_YELLOW = 04; // Temperature LED
int LED_RED = 13; // Fire LED
int LED_GREEN = 02; // All good LED
int smoke = A0;
int sensorThres = 100;

// HTML page for web server
void handleRoot() {
    String html = "<html><head>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<style>";
    html += "body {margin-bottom: 20px; text-align: center; background-image: url('https://blogger.googleusercontent.com/img/a/AVvXsEiiJ1WpRdAioWw3tWFhkyd'); background-size: cover;}";
    html += "img.logo {width: 200px; height: 200px; object-fit: cover;}";
    html += "</style>";
    html += "</head><body>";
    html += "<img class='logo' src='https://i.pinimg.com/originals/a4/87/36/a487368f6fc337d6ff1815608b7fb0c6.jpg' >";

    // STATUS
    html += "<h2>";
    if (digitalRead(LED_YELLOW) == HIGH) {
        html += "<span style='color: orange;'>STATUS</span><br>";
        html += "<img src='https://th.bing.com/th/id/OIP.SNItimAzc2y2Cf_rlE0zMgHaGi?rs=1&pid=ImgDetMain'>";
        html += "<p style='font-size:24px; color:orange;'>RISK, HIGH TEMPERATURES</p>";
    } else if (digitalRead(LED_RED) == HIGH) {
        html += "<span style='color: red;'>STATUS</span><br>";
        html += "<img src='https://i.pinimg.com/originals/55/d5/93/55d593ae9c1ed4cd83dfa5cc0afe5636.jpg'>";
        html += "<p style='font-size:24px; color:red;'>DANGER, CALL EMERGENCY SERVICES</p>";
    } else if (digitalRead(LED) == HIGH) {
        html += "<span style='color: blue;'>STATUS</span><br>";
        html += "<img src='https://i.pinimg.com/originals/7d/05/8c/7d058cbd006585847423b758bc03aede.png'>";
        html += "<p style='font-size:24px; color:blue;'>FIRE UNDER TREATMENT</p>";
    } else if (digitalRead(LED_GREEN) == HIGH) {
        html += "<span style='color: green;'>STATUS</span><br>";
        html += "<img src='https://images.emojiterra.com/twitter/v13.0/512px/2705.png'>";
        html += "<p style='font-size:24px; color:green;'>NO RISK</p>";
    }
    html += "</h2>";

    // Sensor data
    html += "<h2 style='color:#007BFF;'>SENSOR DATA</h2>";
    html += "<img src='https://c8.alamy.com/compes/rp4c60/wifi-conexion-de-senal-de-sonido-el-sonido-de-las-ondas-de-radio-symbol-logo-ilustracion-vectorial-aislado-en-blanco-rp4c60.jpg'>";
    html += "<p><b>Temperature Sensor:</b> " + String(dht.readTemperature()) + " &deg;C</p>";
    html += "<p><b>Smoke Sensor:</b> " + String(analogRead(smoke)) + "</p>";
    html += "<p><b>Water Sensor:</b> " + String(water) + "</p>";

    server.send(200, "text/html", html);
}

void setup() {
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(smoke, INPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);

    Serial.begin(9600);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connecting WiFi to ");
    Serial.print(WiFi.localIP());

    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);

    server.on("/", HTTP_GET, handleRoot);
    server.begin();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        timeClient.update();
        unsigned long utc = timeClient.getEpochTime() - 3600;
        local = usAZ.toLocal(utc);
        // Send data to Firebase
        if (Firebase.set(fbdo, "/test", "successful")) {
            Serial.println("Successful test sent to Firebase!");
        } else {
            Serial.println("Error sending test to Firebase");
            Serial.println("Reason: " + fbdo.errorReason());
        }
    } else {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(1000);
    }

    delay(20000);
    water = analogRead(15);
    delay(500);
    float temperature = dht.readTemperature();
    Serial.println(temperature);
    if (temperature >= 31) {
        digitalWrite(LED_YELLOW, HIGH);
    }
    if (temperature <= 0 || digitalRead(LED_RED) == HIGH) {
        digitalWrite(LED_YELLOW, LOW);
    }

    int analogSensor = analogRead(smoke);
    if (analogSensor > 430) {
        digitalWrite(LED_RED, HIGH);
        delay(1000);
    } else {
        digitalWrite(LED_RED, LOW);
    }

    if (digitalRead(LED_RED) == HIGH && water >= 1023) {
        digitalWrite(LED, HIGH);
        digitalWrite(LED_RED, LOW);
    }
    if (water == 0) {
        digitalWrite(LED, LOW);
    }
    if (analogSensor >= 430 || digitalRead(LED_YELLOW) == HIGH || digitalRead(LED_RED) == HIGH || digitalRead(LED) == HIGH) {
        digitalWrite(LED_GREEN, LOW);
    } else {
        digitalWrite(LED_GREEN, HIGH);
        delay(3000);
    }

    server.handleClient();
    delay(10);
}