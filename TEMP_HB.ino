#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);


// Constants
const int PULSE_SENSOR_PIN = A0;  // Analog PIN where the PulseSensor is connected
const int LED_PIN = 13;          // On-board LED PIN
const int THRESHOLD = 550;       // Threshold for detecting a heartbeat
 
// Create PulseSensorPlayground object
PulseSensorPlayground pulseSensor;
 void body_temp(void);
void setup()
{
  // Initialize Serial Monitor
  Serial.begin(9600);
 lcd.begin(16,2);
      lcd.clear();
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BIOFEEDBACK");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM");
  delay(500);
  // Configure PulseSensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.blinkOnPulse(LED_PIN);
  pulseSensor.setThreshold(THRESHOLD);
 
  // Check if PulseSensor is initialized
  if (pulseSensor.begin())
  {
    //Serial.println("PulseSensor object created successfully!");
  }
}
 
void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate");
  
  // Get the current Beats Per Minute (BPM)
  int currentBPM = pulseSensor.getBeatsPerMinute();
 
  // Check if a heartbeat is detected
  if (pulseSensor.sawStartOfBeat())
  {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(currentBPM);
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    lcd.setCursor(5, 1);
    lcd.print(currentBPM);
  }
 
  // Add a small delay to reduce CPU usage
  delay(1000);

  body_temp();
}
 void body_temp()
{
   // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.println(sensors.getTempCByIndex(0));
 // Serial.print((char)176);//shows degrees character
 // Serial.print("C  |  ");
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMPEARTURE         ");
  lcd.setCursor(0,1);
  lcd.print(sensors.getTempCByIndex(0));
    delay(2000);
/*if(sensors.getTempCByIndex(0)>45)
 {
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMPEARTURE MORE        ");
  lcd.setCursor(0,1);
  lcd.print("DONT GO FOR WORK...    ");
  Serial.println("TEMPEARTURE MORE DONT GO FOR WORK...");
  
 
 }
 else
 {
  
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMPEARTURE         ");
  lcd.setCursor(0,1);
  lcd.print("NORMAL...    ");
  Serial.println("TEMPEARTURE NORMAL YOU CAN GO FOR WORK...");
;
 }
  //print the temperature in Fahrenheit
 // Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
//  Serial.print((char)176);//shows degrees character
//  Serial.println("F");
  
  delay(3000);*/
  
  
  
  
  }
