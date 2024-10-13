/*
   -------------------------------------------------------------------------------------
   WEIGHT-SENSORS
   Arduino code for HX711 24-Bit Analog-to-Digital Converter for Weight Scales and displaying
   Prash and Rishi Oct 2024
   -------------------------------------------------------------------------------------

*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;

// Define sound speed in cm/uS
const float soundSpeed = 0.034;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
void setup() {
  Serial.begin(57600); delay(10);
  // Initialize the alphanumeric display
  alpha4.begin(0x70); // Default I2C address
  alpha4.clear();
  alpha4.writeDisplay();
  alpha4.setBrightness(4);


  LoadCell.begin();
  // Retrieve calibration factor from EEPROM
  float calibrationValue = -8.1;
  LoadCell.setCalFactor(calibrationValue);

  unsigned long stabilizingtime = 2000;
  boolean _tare = true;
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  } else {
    Serial.println("Startup complete");
  }

  while (!LoadCell.update());

    pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  static boolean newDataReady = 0;
  const int displayInterval = 100; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin and calculate the distance
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * soundSpeed / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);


  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + displayInterval) {
      float weight = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.print(weight);
      // displayWeightOnDisplay(900);
      if (weight > 500 || distance < 10) {
        tone(buzzerPin, 1000);
      }
      else {
    noTone(buzzerPin);  // Turn the tone off
  }
      newDataReady = 0;
      t = millis();
    }
  }
   delay(100); // Short delay before next measurement
}

void displayWeightOnDisplay(float weight) {
  alpha4.clear();

  if (weight < 1000) {
    // Weight in grams, show 3 figures and "g"
    alpha4.writeDigitAscii(0, (int)(weight / 100) % 10); // Hundreds place
    alpha4.writeDigitAscii(1, (int)(weight / 10) % 10 );  // Tens place
    alpha4.writeDigitAscii(2, (int)(weight) % 10);       // Units place
    alpha4.writeDigitAscii(3, 'g');                            // Show "g" for grams
  } else {
    // Weight in kilograms, show 2 figures and "kg"
    float kgWeight = weight / 1000;
    alpha4.writeDigitAscii(0, (int)(kgWeight / 10) % 10 + '0');  // Tens place of kg
    alpha4.writeDigitAscii(1, (int)(kgWeight) % 10 + '0');       // Units place of kg
    alpha4.writeDigitAscii(2, 'k');                              // Show "k"
    alpha4.writeDigitAscii(3, 'g');                              // Show "g"
  }

  alpha4.writeDisplay();
}