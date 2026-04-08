#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// 1. Network & Server Settings
const char* ssid = "Airtel_ZeroTouch";
const char* password = "New393002";
const char* serverUrl = "http://192.168.X.X:3000/api/vitals"; // CHANGE X.X to your laptop IP

// 2. Tactical Identification
String myID = "PARA-01-05";

// 3. GPS Configuration
static const int RXPin = 12; // NodeMCU D6 (Connect to GPS TX)
static const int TXPin = 13; // NodeMCU D7 (Connect to GPS RX)
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// Timer for sending data
unsigned long lastTime = 0;
unsigned long timerDelay = 2000; // Send payload every 2 seconds

void setup() {
  // Start PC Serial Monitor
  Serial.begin(9600);
  
  // Start GPS Serial
  ss.begin(GPSBaud);

  Serial.println("\n--- BOOTING SOLDIER MAIN ---");

  // Connect to HQ Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Establishing Comm Link");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[UPLINK SECURE]");
}

void loop() {
  // 1. Constantly feed the GPS data to the TinyGPS object
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // 2. Transmit data every 'timerDelay' (2 seconds)
  if ((millis() - lastTime) > timerDelay) {
    
    // Check if we are still connected to Wi-Fi
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Prepare the connection
      http.begin(client, serverUrl);
      http.addHeader("Content-Type", "application/json");

      // Extract GPS Coordinates
      float latitude = 0.0;
      float longitude = 0.0;

      // Verify the GPS has a lock on satellites
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      }

      // Simulated Vitals (Until you wire up the real sensors)
      int simulatedBPM = random(75, 95);

      // 3. Construct the JSON Payload
      String jsonPayload = "{\"service_number\":\"" + myID + "\",";
      jsonPayload += "\"heart_rate\":" + String(simulatedBPM) + ",";
      jsonPayload += "\"spo2\":98,";
      jsonPayload += "\"status\":\"GREEN\",";
      jsonPayload += "\"latitude\":" + String(latitude, 6) + ","; // Send 6 decimal places
      jsonPayload += "\"longitude\":" + String(longitude, 6) + "}";

      // 4. FIRE THE PACKET
      int httpResponseCode = http.POST(jsonPayload);

      // Log the result to the Serial Monitor
      if (httpResponseCode > 0) {
        Serial.print("[SENT] BPM: "); Serial.print(simulatedBPM);
        if (latitude != 0.0) {
          Serial.print(" | LOC: "); Serial.print(latitude, 6); Serial.print(", "); Serial.println(longitude, 6);
        } else {
          Serial.println(" | LOC: [SEARCHING FOR SATELLITES...]");
        }
      } else {
        Serial.print("[ERROR] Transmission Failed: ");
        Serial.println(httpResponseCode);
      }
      http.end(); // Free up resources
    }
    lastTime = millis(); // Reset timer
  }
}