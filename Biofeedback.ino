#include <Wire.h>
#include <WiFi.h>
#include "MAX30105.h" 
#include <ESP8266WiFi.h>

// WiFi Credentials
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// Initialize sensors
MAX30105 particleSensor;
int gsrPin = A0;  // GSR sensor pin
int breathPin = A1;  // Respiratory sensor pin
int buzzer = 5;  
int led = 6;  
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(gsrPin, INPUT);
  pinMode(breathPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  
  // Initialize Heart Rate Sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30105 sensor not found!");
    while (1);
  }
}

void loop() {
  int gsrValue = analogRead(gsrPin);
  int breathValue = analogRead(breathPin);
  float heartRate = particleSensor.getHeartRate();
  
  Serial.print("GSR: "); Serial.print(gsrValue);
  Serial.print(" | Respiratory: "); Serial.print(breathValue);
  Serial.print(" | Heart Rate: "); Serial.println(heartRate);

  if (gsrValue > 800 || breathValue < 200 || heartRate > 120) { 
    Serial.println("Anxiety Detected!");
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    
    WiFiClient client = server.available();
    if (client) {
      client.println("ALERT: Anxiety Levels High! Take deep breaths.");
      delay(2000);
      client.stop();
    }
  }
  delay(1000);
}